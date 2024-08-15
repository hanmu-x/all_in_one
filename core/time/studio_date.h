#include "studio_macros.h"

namespace simple_date
{

// 获取一天的开始时间
std::tm startOfDay(const std::tm& t)
{
    std::tm start = t;
    start.tm_hour = 0;
    start.tm_min = 0;
    start.tm_sec = 0;
    return start;
}

// 获取一天的结束时间
std::tm endOfDay(const std::tm& t)
{
    std::tm end = t;
    end.tm_hour = 23;
    end.tm_min = 59;
    end.tm_sec = 59;
    return end;
}

// 获取一周的开始时间（周一）
std::tm startOfWeek(const std::tm& t)
{
    std::tm start = t;
    // 调整到周一
    int days_to_monday = (start.tm_wday + 6) % 7;
    start.tm_mday -= days_to_monday;
    start.tm_hour = 0;
    start.tm_min = 0;
    start.tm_sec = 0;
    return start;
}

// 获取一周的结束时间（周日）
std::tm endOfWeek(const std::tm& t)
{
    std::tm end = t;
    // 计算到周日的天数差
    int days_to_sunday = (7 - end.tm_wday) % 7;  // `% 7` 确保处理周日的情况
    // 增加到达周日
    end.tm_mday += days_to_sunday;
    // 处理可能的月份溢出
    std::mktime(&end);  // `mktime` 将日期归一化，处理月份和年份的溢出
    // 设置时间到当天的最后一秒
    end.tm_hour = 23;
    end.tm_min = 59;
    end.tm_sec = 59;

    return end;
}

// 获取一个月的开始时间
std::tm startOfMonth(const std::tm& t)
{
    std::tm start = t;
    start.tm_mday = 1;
    start.tm_hour = 0;
    start.tm_min = 0;
    start.tm_sec = 0;
    return start;
}

// 获取一个月的结束时间
std::tm endOfMonth(const std::tm& t)
{
    std::tm end = t;
    end.tm_mon += 1;  // 移动到下一个月
    end.tm_mday = 0;  // 设置为0以自动调整到上一个月的最后一天

    end.tm_hour = 23;  // 设置时间到当天的最后一秒
    end.tm_min = 59;
    end.tm_sec = 59;

    // 归一化时间
    std::mktime(&end);

    return end;
}

}  // namespace simple_date