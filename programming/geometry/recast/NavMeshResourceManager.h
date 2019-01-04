#pragma once

#pragma warning (disable: 4244)
#include <fstream>
#include <libzippp.h>
#include <boost/filesystem.hpp>
#include <boost/shared_array.hpp>
#include <DetourNavMesh.h>

struct NavMeshInfo
{
public:
	~NavMeshInfo()
	{
	}

public:
	boost::filesystem::path m_file_path;
	boost::shared_array<char> m_raw_nav_mesh; // 변환하지 않은 파일 내용 
	uint32_t m_raw_nav_mesh_size{ 0 };
};

class NavMeshResourceManager
{
public:
	typedef std::map<string_t, boost::shared_ptr<NavMeshInfo>> nav_mesh_info_hash_t;

	bool loadFromFileSystem(string_t root_path);
	bool iterateDirectory(const boost::filesystem::path &path, int32_t depth = 0);
	epic::Result loadMeshFromFileSystem(string_t file_path);

	bool insertNavMeshInfo(boost::shared_ptr<NavMeshInfo> nav_mesh_info);

public:
	epic::Result loadFromZipFile(const string_t& zipfile_path);
	epic::Result loadMeshFromZipFile(const libzippp::ZipEntry& entry);
	boost::shared_ptr<NavMeshInfo> takeNavMeshInfo(string_t nav_mesh_file_name);

private:
	boost::filesystem::path m_root_path;
	bool m_load_completed{ false };
	nav_mesh_info_hash_t m_nav_mesh_info_hash;
};