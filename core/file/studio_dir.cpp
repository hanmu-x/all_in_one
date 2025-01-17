
#include "studio_dir.h"

std::vector<std::string> studio_dir::collectFileOrDirEntries(const std::string& directoryPath, bool isFile, bool returnFullPath, bool recursive)
{
    std::vector<std::string> entries;
    try
    {
        std::filesystem::path dirPath(directoryPath);
        if (recursive)  // 递归
        {
            for (auto& entry : std::filesystem::recursive_directory_iterator(dirPath))
            {
                if ((isFile && entry.is_regular_file()) || (!isFile && entry.is_directory()))
                {
                    if (returnFullPath)
                    {
                        entries.push_back(entry.path().string());
                    }
                    else
                    {
                        entries.push_back(entry.path().filename().make_preferred().string());
                    }
                }
            }
        }
        else  // 非递归
        {
            for (auto& entry : std::filesystem::directory_iterator(dirPath))
            {
                if ((isFile && entry.is_regular_file()) || (!isFile && entry.is_directory()))
                {
                    if (returnFullPath)
                    {
                        entries.push_back(entry.path().string());
                    }
                    else
                    {
                        entries.push_back(entry.path().filename().make_preferred().string());
                    }
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cout << "Error accessing directory: " << e.what() << std::endl;
    }

    return entries;
}

bool studio_dir::createDirectoryIfNotExists(const std::string& directoryPath)
{
    std::filesystem::path path(directoryPath);

    if (!std::filesystem::exists(path))
    {
        try
        {
            std::filesystem::create_directories(path);
            if (std::filesystem::exists(path))
            {
                return true;  // 创建目录成功
            }
            else
            {
                return false;
            }
        }
        catch (const std::filesystem::filesystem_error& ex)
        {
            std::cout << "Error creating directory: " << ex.what() << std::endl;
            return false;  // 创建目录失败
        }
    }
    else
    {
        return true;  // 目录已存在
    }
}

int studio_dir::count_files(const std::string& directory_path)
{
    int file_count = 0;

    // 检查目录是否存在
    if (std::filesystem::exists(directory_path) && std::filesystem::is_directory(directory_path))
    {
        // 遍历目录下的所有条目
        for (const auto& entry : std::filesystem::directory_iterator(directory_path))
        {
            // 检查是否为文件
            if (std::filesystem::is_regular_file(entry.status()))
            {
                ++file_count;
            }
        }
    }
    else
    {
        std::cout << "指定目录不存在或不是一个目录。" << std::endl;
    }
    return file_count;
}

std::map<std::string, std::string> studio_dir::getLastModifiedTimesInDirectory(const std::string& path)
{
    std::map<std::string, std::string> path_tm;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            std::filesystem::file_time_type modificationTime = entry.last_write_time();
            auto sys_time = std::chrono::system_clock::now() + (modificationTime - std::filesystem::file_time_type::clock::now());
            std::time_t t = std::chrono::system_clock::to_time_t(sys_time);
            std::tm* ptm = std::localtime(&t);  // 创建 tm 结构体

            // 定义一个足够大的字符数组来保存时间字符串
            char buffer[20];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ptm);  // 19个字节的格式
            path_tm[entry.path().string()] = buffer;
            std::cout << "File: " << entry.path().string() << ", Last modified: " << buffer << '\n';
        }
    }
    return path_tm;
}

bool studio_dir::remove(const std::string& path)
{
    bool status = false;
    try
    {
        // 首先检查路径是否存在
        if (!std::filesystem::exists(path))
        {
            std::cout << "Error: Path does not exist: " << path << std::endl;
            return false;  // 文件不存在，直接返回 false
        }

        // 判断是否为普通文件
        if (!std::filesystem::is_regular_file(path))
        {
            std::cout << "Error: Path is not a regular file: " << path << std::endl;
            return false;  // 路径不是普通文件，直接返回 false
        }
        // 尝试删除文件
        std::filesystem::remove(path);
        std::cout << "Successfully removed file: " << path << std::endl;
        status = true;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cout << "Error removing file: " << e.what() << std::endl;
    }
    return status;
}

bool studio_dir::removeAll(const std::string& path)
{
    bool status = false;
    try
    {
        // 尝试递归删除目录及其内容
        std::filesystem::remove_all(path);
        status = true;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cout << "Error removing directory: " << e.what() << std::endl;
    }
    return status;
}
