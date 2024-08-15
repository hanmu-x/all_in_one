
#include "studio_file.h"

bool studio_file::writeLineString(const std::string& logFilePath, const std::string& data)
{
    std::ofstream logFile(logFilePath, std::ios::out | std::ios::trunc);  // 确保文件被截断
    if (logFile.is_open())
    {
        logFile << data << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}


// 从文件中读取处理时间
std::string studio_file::readLineString(const std::string& logFilePath)
{
    std::string date;
    if (std::filesystem::exists(logFilePath))
    {
        std::ifstream logFile(logFilePath);
        if (logFile.is_open())
        {
            std::getline(logFile, date);
            return date;
        }
        else
        {
            return date;
        }
    }
    else
    {
        return date;
    }
}








