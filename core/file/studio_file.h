
#ifndef STUDIO_FILE_H
#define STUDIO_FILE_H

#include "studio_macros.h"


class studio_file
{
  public:

    /// <summary>
    /// 写入一行字符串到文件
    /// </summary>
    /// <param name="logFilePath"></param>
    /// <param name="data"></param>
    /// <returns></returns>
    static bool writeLineString(const std::string& logFilePath, const std::string& data);

    /// <summary>
    /// 从文件读取一行字符串
    /// </summary>
    /// <param name="logFilePath"></param>
    /// <returns></returns>
    static std::string readLineString(const std::string& logFilePath);

    studio_file() = default;
    ~studio_file() = default;
};

#endif // STUDIO_FILE_H