#include "preheader.h"
#include <DetourEx.h>

#include "NavMeshResourceManager.h"
#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>



boost::shared_ptr<NavMeshInfo> NavMeshResourceManager::takeNavMeshInfo(string_t nav_mesh_name)
{
	LOG_DEBUG("try find `{}`", nav_mesh_name)
	auto it = m_nav_mesh_info_hash.find(nav_mesh_name);
	if (m_nav_mesh_info_hash.end() == it)
	{
		return boost::shared_ptr<NavMeshInfo>();
	}
	return it->second;
}

bool NavMeshResourceManager::loadFromFileSystem(string_t root_path)
{
	m_root_path = epic::replace_all_copy(root_path, "/", "\\");
	try
	{
		if (!boost::filesystem::exists(m_root_path))
		{
			return false;
		}
		iterateDirectory(m_root_path);
	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		LOG_ERROR(ex.what());
		return false;
	}
	m_load_completed = true;
	return true;
}

bool NavMeshResourceManager::iterateDirectory(const boost::filesystem::path &path, int32_t depth /*= 0*/)
{
	if (!boost::filesystem::is_directory(path))
	{
		return false;
	}
	for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator(path))
	{
		if (boost::filesystem::is_directory(entry.path()))
		{
			bool success = iterateDirectory(entry.path(), depth + 1);
		}
		else
		{
			auto epic_result = loadMeshFromFileSystem(entry.path().string());
			if (epic_result.Fail())
			{
				LOG_ERROR(epic_result.ToString());
			}
		}
	}
	return true;
}

bool NavMeshResourceManager::insertNavMeshInfo(boost::shared_ptr<NavMeshInfo> nav_mesh_info)
{
	m_nav_mesh_info_hash.insert({ nav_mesh_info->m_file_path.stem().string(), nav_mesh_info });
	LOG_DEBUG("`{}` navmesh inserted.", nav_mesh_info->m_file_path.stem().string());
	return true;
}

epic::Result NavMeshResourceManager::loadMeshFromFileSystem(string_t file_path)
{
	epic::Result epic_result; 
	auto nav_mesh_info = boost::make_shared<NavMeshInfo>();
	nav_mesh_info->m_file_path = file_path;

	std::ifstream fin(file_path, (std::ios::in | std::ios::ate | std::ios::binary));
	if (false == fin.is_open())
	{
		return epic_result.SetFail(sformat("file {} not found", file_path));
	}

	fin.seekg(0, std::ios::end);
	long file_size = fin.tellg();
	fin.seekg(0, std::ios::beg);

	nav_mesh_info->m_raw_nav_mesh_size = file_size;
	nav_mesh_info->m_raw_nav_mesh.reset(new char[file_size]);
	fin.read(nav_mesh_info->m_raw_nav_mesh.get(), file_size);
	fin.close();

	insertNavMeshInfo(nav_mesh_info);

	return epic_result.SetOk();
}


epic::Result NavMeshResourceManager::loadFromZipFile(const string_t& zipfile_path)
{
	libzippp::ZipArchive zf(zipfile_path);
	zf.open(libzippp::ZipArchive::READ_ONLY);

	std::vector<libzippp::ZipEntry> entries = zf.getEntries();
	std::vector<libzippp::ZipEntry>::iterator it;
	for (it = entries.begin(); it != entries.end(); ++it)
	{
		loadMeshFromZipFile(*it);
	}
	zf.close();
	LOG_DEBUG("complete load tree from {}", zipfile_path);
	return true;
}

epic::Result NavMeshResourceManager::loadMeshFromZipFile(const libzippp::ZipEntry& entry)
{
	epic::Result epic_result;
	dtNavMesh* new_nav_mesh = nullptr;

	if (entry.isDirectory())
	{
		return epic_result.SetOk(sformat("{} is not a file", entry.getName()));
	}

	boost::filesystem::path file_path = entry.getName();
	string_t ext = file_path.extension().string();
	if (ext != ".navmesh")
	{
		return epic_result.SetOk(sformat("{} is not a .navmesh", entry.getName()));
	}

	void* binary_data = entry.readAsBinary();
	auto data_size = static_cast<uint32_t>(entry.getSize());
	if (data_size == 0)
	{
		return epic_result.SetFail("data size is zero");
	}

	auto nav_mesh_info = boost::make_shared<NavMeshInfo>();
	nav_mesh_info->m_file_path = file_path;
	nav_mesh_info->m_raw_nav_mesh_size = data_size;
	nav_mesh_info->m_raw_nav_mesh.reset(new char[data_size]);
	memcpy(nav_mesh_info->m_raw_nav_mesh.get(), reinterpret_cast<unsigned char*>(binary_data), data_size);

	insertNavMeshInfo(nav_mesh_info);
	return epic_result.SetOk();
}

