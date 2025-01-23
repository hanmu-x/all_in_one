
#ifndef STUDIO_POSIX_TIME_H
#define STUDIO_POSIX_TIME_H

#include <studio_macros.h>

const static char* DATE_FORMAT_1 = "%Y-%m-%d %H:%M:%S";
const static char* DATE_FORMAT_2 = "%Y%m%d%H";
const static char* DATE_FORMAT_3 = "%H";
const static char* DATE_FORMAT_4 = "%Y%m%d%H%M";
const static char* DATE_FORMAT_5 = "%Y-%m-%d %H:%M";
const static char* DATE_FORMAT_6 = "%Y%m%d";
const static char* DATE_FORMAT_7 = "%Y-%m-%d-%H-%M-%S";
const static char* DATE_FORMAT_8 = "%Y-%m-%d %H:00";

using studio_time_stamp = std::time_t;  // 始终以秒为准
// using studio_time_duration = std::chrono::system_clock::duration;
class studio_time_duration
{
  public:
    studio_time_duration() = default;
    studio_time_duration(int hours, int minutes, int seconds);
    studio_time_duration(studio_time_stamp secs);

    int total_days() const;
    int hours() const;
    int total_hours() const;
    int minutes() const;
    int total_minutes() const;
    int seconds() const;
    studio_time_stamp total_seconds() const;

  private:
    studio_time_stamp m_total_seconds{0};
};

static void check_std_tm(std::tm stm);

// 时间戳为标准时间戳精确到秒;
// 时间以北京时间为准,见fix_tm的实现;
class studio_posix_time
{
  public:
    studio_posix_time();
    studio_posix_time(const studio_posix_time& time);
    // studio_posix_time(const studio_posix_time& other) = default;
    ~studio_posix_time() = default;

    static studio_posix_time now();
    static studio_posix_time time_from_string(const std::string& str, const std::string& fmt = DATE_FORMAT_1);
    static std::string time_to_string(const studio_posix_time& pt, const std::string& fmt = DATE_FORMAT_1);



    bool is_not_a_date_time() const;
    bool from_string(const std::string& str, const std::string& fmt = DATE_FORMAT_1);
    std::string to_string(const std::string& fmt = DATE_FORMAT_1) const;

    studio_posix_time(const studio_time_stamp& stamp);

    bool operator>(const studio_posix_time& other) const;
    bool operator==(const studio_posix_time& other) const;
    bool operator<(const studio_posix_time& other) const;
    bool operator>=(const studio_posix_time& other) const;
    bool operator<=(const studio_posix_time& other) const;

    studio_posix_time operator=(const studio_posix_time& other);
    studio_posix_time operator+(const studio_time_duration& other) const;
    studio_posix_time& operator+=(const studio_time_duration& other);
    studio_posix_time operator-(const studio_time_duration& other) const;
    studio_posix_time& operator-=(const studio_time_duration& other);
    studio_time_duration operator-(const studio_posix_time& other) const;

    studio_time_stamp stamp_sec() const;

    std::chrono::system_clock::time_point time_point() const;

    std::tm tm() const;

    int year() const;    // 年
    int month() const;   // 月
    int day() const;     // 日
    int yday() const;    // 一年中的第几天
    int wday() const;    // 一周中的第几天
    int hour() const;    // 小时
    int minute() const;  // 分钟
    int second() const;  // 秒

  private:
    void fix_tm();

  private:
    std::string m_err;
    std::chrono::system_clock::time_point m_time_point;  // 这个是不区分时区的时间戳
    std::tm m_tm{};
    std::mutex m_mutex;
};
#endif  // STUDIO_POSIX_TIME_H
