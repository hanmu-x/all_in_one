
#include "common_file.h"

std::vector<std::string> common_file::collectFileOrDirEntries(const std::string& directoryPath, bool isFile, bool returnFullPath, bool recursive)
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
