

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include "studio_macros.h"

#ifndef __studio_TIME_H__
#define __studio_TIME_H__

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

static boost::posix_time::ptime NowPosixTime()
{
    return boost::posix_time::second_clock::local_time();
}
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

// 转换时间格式的函数
static std::string convertTmFormat(const std::string& inputDate, const std::string& inputFormat, const std::string& outputFormat)
{
    std::istringstream ss(inputDate);
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











}  // namespace simple_time

#endif
