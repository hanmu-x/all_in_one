
#include "common_macros.h"

#ifndef __COMMON_FILE_H__
#define __COMMON_FILE_H__

class common_file
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

    common_file() = default;
    ~common_file() = default;
};

#endif