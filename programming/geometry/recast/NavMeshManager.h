#pragma once

#pragma warning (disable: 4244)
#include <fstream>
#include <DetourNavMeshQuery.h>
#include <libzippp.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "NavmeshQuery.h"
#include "CrowdManager.h"

const long RCN_NAVMESH_VERSION = 1;

//struct rcnNavMeshSetHeader
//{
//	long version;
//	int tileCount;
//	dtNavMeshParams params;
//};
//
//struct rcnNavMeshTileHeader
//{
//	dtTileRef tileRef;
//	int dataSize;
//};

inline static float frand()
{
	return (float)rand() / (float)RAND_MAX;
};

struct WarpArea
{
	float x;
	float y;
	float z;
	float angle;
	int zone;
};

class NavMeshManager
{
public:
	NavMeshManager();
	~NavMeshManager();
	
public:
	epic::Result init(string_t nav_mesh_name);
	void freeNavMesh();

	void requestDisposal();
	void update(float delta_time);

	dtStatus nearestPoint(glm::vec3 searchPoint, rcnNavmeshPoint* point);
	glm::vec3 takeRandomPosition(glm::vec3& unit_position, float radius);
	glm::vec3 computeRandomPosition(glm::vec3 unit_position, float radius);

	void randomPoint(rcnNavmeshPoint start_point, float radius, _out rcnNavmeshPoint* output_point);

private:
	dtStatus nearestPoint(glm::vec3 searchPoint, glm::vec3 extents, const dtQueryFilter* filter, rcnNavmeshPoint* point);

	dtStatus buildNavMeshFromRaw(const unsigned char* data, int dataSize, bool safeStorage, dtNavMesh** ppNavMesh);

public:
	int m_maxQueryNodes{ 4096 };
	//int m_max_crowd_agent{ 500 };
	//float m_max_agent_radius{ 0.5f };

	glm::vec3 m_extents;

private:
	dtNavMesh* m_nav_mesh{ nullptr };
	CrowdManager* m_crowd_manager{ nullptr };			
	dtNavMeshQuery* m_navmesh_query{ nullptr };

	epic::Result m_initialize_result;

	std::set<CrowdManager*> m_crowd_manager_set;
	CrowdManager* create_crowd_manager(int max_agents, float max_agent_radius);	
	void remove_crowd_manager(CrowdManager* crowd_manager);
public:
	dtNavMesh* nav_mesh()								
	{
		return m_nav_mesh;
	}
	CrowdAgent* add_crowd_agent(CrowdManager* crowd_manager, glm::vec3 position, dtCrowdAgentParams agent_params);
	void remove_crowd_agent(CrowdAgent* crowd_agent);
};