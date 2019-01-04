
#pragma once

#include <DetourEx.h>
#include <DetourNavMeshQuery.h>

#include <glm/glm.hpp> 
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

class NavmeshQuery
{
public:
	static dtStatus create(dtNavMesh* mesh, int max_nodes, dtNavMeshQuery** nav_query);
	void dtnQFree(dtNavMeshQuery** navQuery)
	{
		dtFreeNavMeshQuery(*navQuery);
	}
	NavmeshQuery();
	NavmeshQuery(dtNavMeshQuery* query, bool isConstant);
	virtual ~NavmeshQuery();
	dtStatus nearestPoint(glm::vec3 search_point, glm::vec3 extents, dtQueryFilter filter, rcnNavmeshPoint* point);
public:
	dtNavMeshQuery* root;
	bool m_is_restricted{ false };
};