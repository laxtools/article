
#include "preheader.h"
#include "NavmeshQuery.h"




dtStatus NavmeshQuery::create(dtNavMesh* mesh, int max_nodes, dtNavMeshQuery** nav_query)
{
	if (!mesh)
	{
		return DT_FAILURE + DT_INVALID_PARAM;
	}
	dtNavMeshQuery* new_nav_query = dtAllocNavMeshQuery();
	if (!new_nav_query)
	{
		return DT_FAILURE + DT_OUT_OF_MEMORY;
	}
	dtStatus status = new_nav_query->init(mesh, max_nodes);
	if (dtStatusFailed(status))
	{
		dtFreeNavMeshQuery(new_nav_query);
		return status;
	}
	*nav_query = new_nav_query;

	return DT_SUCCESS;
}

NavmeshQuery::NavmeshQuery()
{

}

NavmeshQuery::NavmeshQuery(dtNavMeshQuery* query, bool isConstant)
{
	m_is_restricted = isConstant;
	root = query;
}

dtStatus NavmeshQuery::nearestPoint(glm::vec3 search_point, glm::vec3 extents, dtQueryFilter filter, rcnNavmeshPoint* point)
{
	point = nullptr;

	//dtqFindNearestPoly

	return DT_SUCCESS;
}

NavmeshQuery::~NavmeshQuery()
{

}
