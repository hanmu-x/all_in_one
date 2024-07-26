
#include "studio_macros.h"

#ifndef __STUDIO_DIR_H__
#define __STUDIO_DIR_H__

class studio_dir
{
  public:
    /// <summary>
    /// (递归,非递归) 的获取指定目录下所有的(文件或者目录)的(绝对路径或者文件名称)
    /// </summary>
    /// <param name="directoryPath">指定目录</param>
    /// <param name="isFile">true:文件，false:目录</param>
    /// <param name="returnFullPath">true表示完整路径，false仅表示名称</param>
    /// <param name="recursive">false:非递归,true:地推</param>
    /// <returns></returns>
    static std::vector<std::string> collectFileOrDirEntries(const std::string& directoryPath, bool isFile = true, bool returnFullPath = true, bool recursive = false);

    /// <summary>
    /// 判断目录是否存在,若不存在创建
    /// </summary>
    /// <param name="directoryPath"></param>
    /// <returns></returns>
    static bool createDirectoryIfNotExists(const std::string& directoryPath);

    /// <summary>
    /// 统计给定目录下的文件数量
    /// </summary>
    /// <param name="directory_path"></param>
    /// <returns></returns>
    static int count_files(const std::string& directory_path);

    /// <summary>
    /// 获取指定目录下所有文件最后修改时间
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    static std::map<std::string, std::string> getLastModifiedTimesInDirectory(const std::string& path);
    

    studio_dir() = default;
    ~studio_dir() = default;
};

#endif