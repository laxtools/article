
#include "preheader.h"
#include "NavMeshResourceManager.h"
#include "NavMeshManager.h"
#include <boost/filesystem.hpp>
#include <LibBase/cpp/Random.h>


struct rcnNavMeshSetHeader
{
	long version;
	int tileCount;
	dtNavMeshParams params;
};

struct rcnNavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

NavMeshManager::NavMeshManager()
{
	m_initialize_result.SetFail();
}

NavMeshManager::~NavMeshManager()
{
	for (auto crowd_manager : m_crowd_manager_set)
	{
		_SAFE_DELETE(crowd_manager);
	}
	
	dtFreeNavMesh(m_nav_mesh);
	m_nav_mesh = nullptr;
}


dtStatus NavMeshManager::nearestPoint(glm::vec3 searchPoint, glm::vec3 extents, const dtQueryFilter* filter, rcnNavmeshPoint* point)
{
	return m_navmesh_query->findNearestPoly(glm::value_ptr(searchPoint), glm::value_ptr(extents), filter, &point->polyRef, &point->point[0]);
}

dtStatus NavMeshManager::nearestPoint(glm::vec3 searchPoint, rcnNavmeshPoint* point)
{
	if (m_crowd_manager)
	{
		return nearestPoint(searchPoint, m_extents, m_crowd_manager->queryFilter(), point);
	}
	return DT_FAILURE;
}

dtStatus NavMeshManager::buildNavMeshFromRaw(const unsigned char* data, int dataSize, bool safeStorage, dtNavMesh** ppNavMesh)
{
	m_nav_mesh = nullptr;
	if (!data || dataSize < sizeof(rcnNavMeshSetHeader) || !ppNavMesh)
	{
		return DT_FAILURE + DT_INVALID_PARAM;
	}

	int pos = 0;
	int size = sizeof(rcnNavMeshSetHeader);

	rcnNavMeshSetHeader header;
	memcpy(&header, data, size);
	pos += size;

	if (header.version != RCN_NAVMESH_VERSION)
	{
		*ppNavMesh = 0;
		return DT_FAILURE + DT_WRONG_VERSION;
	}

	m_nav_mesh = dtAllocNavMesh();
	if (!m_nav_mesh)
	{
		*ppNavMesh = 0;
		return DT_FAILURE + DT_OUT_OF_MEMORY;
	}

	dtStatus status = m_nav_mesh->init(&header.params);
	if (dtStatusFailed(status))
	{
		*ppNavMesh = 0;
		return status;
	}

	// Read tiles.
	bool success = true;
	for (int i = 0; i < header.tileCount; ++i)
	{
		rcnNavMeshTileHeader tileHeader;
		size = sizeof(rcnNavMeshTileHeader);
		memcpy(&tileHeader, &data[pos], size);
		pos += size;

		size = tileHeader.dataSize;
		if (!tileHeader.tileRef || !tileHeader.dataSize)
		{
			success = false;
			status = DT_FAILURE + DT_INVALID_PARAM;
			break;
		}
		unsigned char* tileData = (unsigned char*)dtAlloc(size, DT_ALLOC_PERM);
		if (!tileData)
		{
			success = false;
			status = DT_FAILURE + DT_OUT_OF_MEMORY;
			break;
		}
		memcpy(tileData, &data[pos], size);
		pos += size;

		status = m_nav_mesh->addTile(tileData
			, size
			, (safeStorage ? DT_TILE_FREE_DATA : 0)
			, tileHeader.tileRef
			, 0);

		if (dtStatusFailed(status))
		{
			success = false;
			break;
		}
	}

	if (!success)
	{
		dtFreeNavMesh(m_nav_mesh);
		*ppNavMesh = 0;
		return status;
	}

	*ppNavMesh = m_nav_mesh;
	return DT_SUCCESS;
}

glm::vec3 NavMeshManager::takeRandomPosition(glm::vec3& unit_position, float radius)
{
	glm::vec3 output_position;

	rcnNavmeshPoint nearest_point;
	nearestPoint(unit_position, _out &nearest_point);

	// get random point 
	rcnNavmeshPoint output_point;
 	randomPoint(nearest_point, radius, _out &output_point);

	output_position.x = output_point.point[0];
	output_position.y = output_point.point[1];
	output_position.z = output_point.point[2];

	//LOG_INFO("random position : {}, {}, {}", output_position.x, output_position.y, output_position.z);

	return output_position;
}

void NavMeshManager::randomPoint(rcnNavmeshPoint start_point, float radius, _out rcnNavmeshPoint* output_point)
{
	m_navmesh_query->findRandomPointAroundCircle(start_point.polyRef, &start_point.point[0], radius, m_crowd_manager->queryFilter(), frand, _out &output_point->polyRef, _out &output_point->point[0]);
}


glm::vec3 NavMeshManager::computeRandomPosition(glm::vec3 center_position, float radius)
{
	glm::vec3 output_position;
	glm::vec3 random_position;
	rcnNavmeshPoint nearest_point;
	
	//////////////////////////////////////////////////////////////////////////
	double pi = 3.14159265359f;
	double radius_t = 2 * pi * epic::randomf(0, 1.0f);
	double random_u = epic::randomf(0, 1.0f) + epic::randomf(0, 1.0f);
	double random_r = (random_u > 1) ? 2 - random_u : random_u;
	random_position.x = center_position.x + random_r*cos(radius_t)*radius;
	random_position.y = center_position.y;
	random_position.z = center_position.z + random_r*sin(radius_t)*radius;
	//////////////////////////////////////////////////////////////////////////

	nearestPoint(random_position, _out &nearest_point);	//혹시 Y가 작을때 오류가 있는지 체크 필요
	output_position.x = nearest_point.point[0];
	output_position.y = nearest_point.point[1];
	output_position.z = nearest_point.point[2];

	float distance = 0;
	distance = glm::distance(center_position, output_position);
	if (distance > radius)
	{
		LOG_ERROR("****** random position : radius:{} < distance:{}", radius, distance);
		output_position = center_position;
	}

	return output_position;
}



epic::Result NavMeshManager::init(string_t nav_mesh_name)
{
	LOG_DEBUG("init with `{}` ", nav_mesh_name);
	//freeNavMesh();

	auto nav_mesh_info = epic::Singleton<NavMeshResourceManager>()->takeNavMeshInfo(nav_mesh_name);
	if (!nav_mesh_info)
	{
		return m_initialize_result.SetFail(sformat("nav_mesh `{}` is not exist.", nav_mesh_name));
	}

	auto load_status = buildNavMeshFromRaw(reinterpret_cast<unsigned char*>(nav_mesh_info->m_raw_nav_mesh.get()), nav_mesh_info->m_raw_nav_mesh_size, true, &m_nav_mesh);
	if (DT_SUCCESS != load_status)
	{
		return m_initialize_result.SetFail(sformat("`{}`, navmesh build failed:{}", nav_mesh_name, load_status));
	}

	m_extents = glm::vec3(1.0f, 1.0f, 1.0f);
	dtStatus staus = NavmeshQuery::create(m_nav_mesh, m_maxQueryNodes, &m_navmesh_query);
	if ((staus & DT_SUCCESS) == 0)
	{
		return m_initialize_result.SetFail(sformat("`{}` mesh query create failed.", nav_mesh_name));
	}

	m_crowd_manager = create_crowd_manager(25, 0.5);
	if (nullptr == m_crowd_manager)
	{
		return m_initialize_result.SetFail(sformat("`{}` crowd manager create failed.", nav_mesh_name));
	}

	LOG_DEBUG("setup mesh `{}` completed.", nav_mesh_name);
	return m_initialize_result.SetOk();
}

void NavMeshManager::freeNavMesh()
{
	if (!m_nav_mesh)
	{
		return;
	}
	dtFreeNavMesh(m_nav_mesh);
	m_nav_mesh = nullptr;
}

#include <libBase/cpp/ProfileObject.h>
void NavMeshManager::update(float delta_time)
{
	if (m_initialize_result.Fail())
	{
		return;
	}

	//PROFILE_BEGIN(nav_mesh_manager, 0.001);
	//if (m_crowd_manager)
	//{
	//	m_crowd_manager->update(delta_time);
	//}
	for (auto crowd_manager : m_crowd_manager_set)
	{
		crowd_manager->update(delta_time);
	}

	//PROFILE_END(nav_mesh_manager);
}

void NavMeshManager::requestDisposal()
{
	//_SAFE_DELETE(m_crowd_manager);
}


CrowdManager* NavMeshManager::create_crowd_manager( int max_agents, float max_agent_radius )
{
	if (nav_mesh() == nullptr)
	{
		return nullptr;
	}
	max_agents = glm::max(1, max_agents);
	max_agent_radius = glm::max(0.0f, max_agent_radius);

	CrowdManager* crowd_manager = new CrowdManager();
	if (nullptr != crowd_manager)
	{
		crowd_manager->init(nav_mesh(), max_agents, max_agent_radius);
		m_crowd_manager_set.insert(crowd_manager);
		return crowd_manager;
	}
	else
	{
		return nullptr;
	}
}


CrowdAgent* NavMeshManager::add_crowd_agent(CrowdManager* crowd_manager, glm::vec3 position, dtCrowdAgentParams agent_params)
{
	if (nullptr == crowd_manager || 
		crowd_manager->agentCount() >= crowd_manager->maxAgents())
	{
		crowd_manager = create_crowd_manager(25, 0.5);
		if (nullptr == crowd_manager)
		{
			return nullptr;
		}
	}
	
	return crowd_manager->addAgent(position, agent_params);
}


void NavMeshManager::remove_crowd_agent(CrowdAgent* crowd_agent)
{
	if (nullptr == crowd_agent)
	{
		return;
	}
	CrowdManager* crowd_manager = crowd_agent->m_manager;
	if (nullptr == crowd_manager)
	{
		return;
	}
	crowd_manager->removeAgent(crowd_agent);
	if (crowd_manager->agentCount() == 0)
	{
		remove_crowd_manager(crowd_manager);
	}
}


void NavMeshManager::remove_crowd_manager(CrowdManager* crowd_manager)
{
	m_crowd_manager_set.erase(crowd_manager);
	_SAFE_DELETE(crowd_manager);
}