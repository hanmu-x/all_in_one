
#ifndef STUDIO_TIME_H
#define STUDIO_TIME_H

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include "studio_macros.h"

namespace simple_time
{

const static char* TM_FORMAT_1 = "%Y-%m-%d %H:%M:%S";
const static char* TM_FORMAT_2 = "%Y%m%d%H";
const static char* TM_FORMAT_3 = "%H";
const static char* TM_FORMAT_4 = "%Y%m%d%H%M";
const static char* TM_FORMAT_5 = "%Y-%m-%d %H:%M";
const static char* TM_FORMAT_6 = "%Y%m%d";
const static char* TM_FORMAT_7 = "%Y-%m-%d-%H-%M-%S";
const static char* TM_FORMAT_8 = "%Y-%m-%d %H:00";
const static char* TM_FORMAT_10 = "%Y%m%f%h00";

/// <summary>
/// 获取当前时间
/// </summary>
/// <returns></returns>
static boost::posix_time::ptime NowPosixTime()
{
    return boost::posix_time::second_clock::local_time();
}

/// <summary>
/// 字符串之间转boost::posix_time::ptime
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
static boost::posix_time::ptime TimeFromString(const std::string& str)
{
    boost::posix_time::ptime _ptime;
    try
    {
        _ptime = boost::posix_time::time_from_string(str);
    }
    catch (const std::exception& e)
    {
        AO_ERROR_PRINT("%s", e.what())
    }
    return _ptime;
}

/// <summary>
/// boost::posix_time::ptime转字符串
/// </summary>
/// <param name="time"></param>
/// <param name="format"></param>
/// <returns></returns>
static std::string TimeToFormatString(const boost::posix_time::ptime& time, const std::string& format = TM_FORMAT_5)
{
    std::string retStr;
    try
    {
        boost::posix_time::time_facet* tf = new boost::posix_time::time_facet(format.c_str());
        std::stringstream ss;
        ss.imbue(std::locale(std::cout.getloc(), tf));
        ss << time;
        retStr = ss.str();
    }
    catch (const std::exception& e)
    {
        AO_ERROR_PRINT("%s", e.what())
    }

    return retStr;
}

/// <summary>
/// 将时间字符串从一种格式转换为另一种格式
/// </summary>
/// <param name="inputTm"></param>
/// <param name="inputFormat"></param>
/// <param name="outputFormat"></param>
/// <returns></returns>
static std::string convertTmFormat(const std::string& inputTm, const std::string& inputFormat, const std::string& outputFormat)
{
    std::istringstream ss(inputTm);
    std::ostringstream oss;
    std::tm time = {};

    ss >> std::get_time(&time, inputFormat.c_str());
    if (ss.fail())
    {
        std::cout << "Error: Failed to parse input date with format " << inputFormat << std::endl;
        return "";
    }

    oss << std::put_time(&time, outputFormat.c_str());
    if (oss.fail())
    {
        std::cout << "Error: Failed to format output date with format " << outputFormat << std::endl;
        return "";
    }

    return oss.str();
}

/// <summary>
/// 将字符串时间（"YYYY-MM-DD" 格式）转换为 std::tm 结构体
/// </summary>
/// <param name="time_str"></param>
/// <param name="format"></param>
/// <returns></returns>
static std::tm stringToTm(const std::string& time_str, const std::string& format = "%Y-%m-%d")
{
    std::tm t = {};
    std::istringstream ss(time_str);
    ss >> std::get_time(&t, format.c_str());
    return t;
}

/// <summary>
/// 将 std::tm 结构体转换为字符串
/// </summary>
/// <param name="t"></param>
/// <param name="format"></param>
/// <returns></returns>
static std::string tmToString(const std::tm& t, const std::string& format = "%Y-%m-%d")
{
    char buffer[32];  // 假设日期时间字符串不会超过32个字符
    std::strftime(buffer, sizeof(buffer), format.c_str(), &t);
    return std::string(buffer);
}

}  // namespace simple_time

#endif  // STUDIO_TIME_H
