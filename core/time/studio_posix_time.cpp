
#include "studio_posix_time.h"

studio_time_duration::studio_time_duration(int hours, int minutes, int seconds)
{
    m_total_seconds = hours * 3600 + minutes * 60 + seconds;
}

studio_time_duration::studio_time_duration(studio_time_stamp secs)
{
    m_total_seconds = secs;
}

int studio_time_duration::total_days() const
{
    return m_total_seconds / SEC_IN_DAY;
}

int studio_time_duration::hours() const
{
    return m_total_seconds % SEC_IN_DAY / SEC_IN_HOUR;
}

int studio_time_duration::minutes() const
{
    return m_total_seconds % SEC_IN_HOUR / SEC_IN_MIN;
}

int studio_time_duration::seconds() const
{
    return m_total_seconds % SEC_IN_MIN;
}

studio_time_stamp studio_time_duration::total_seconds() const
{
    return m_total_seconds;
}

int studio_time_duration::total_minutes() const
{
    return m_total_seconds / SEC_IN_MIN;
}

int studio_time_duration::total_hours() const
{
    return m_total_seconds / SEC_IN_HOUR;
}

void check_std_tm(std::tm stm)
{
    if (stm.tm_sec < 0 || stm.tm_sec > 59)
        throw std::runtime_error(std::string("秒(sec) ").append(std::to_string(stm.tm_sec)).append(" 需要 0 - 59"));
    if (stm.tm_min < 0 || stm.tm_min > 59)
        throw std::runtime_error(std::string("分(min) ").append(std::to_string(stm.tm_min)).append(" 需要 0 - 59"));
    if (stm.tm_hour < 0 || stm.tm_hour > 23)
        throw std::runtime_error(std::string("时(hour) ").append(std::to_string(stm.tm_hour)).append(" 需要 0 - 24"));
    if (stm.tm_mday < 1 || stm.tm_mday > 31)
        throw std::runtime_error(std::string("日(day) ").append(std::to_string(stm.tm_mday)).append(" 需要 1 - 31"));
    if (stm.tm_mon < 0 || stm.tm_mon > 11)
        throw std::runtime_error(std::string("月(mon) ").append(std::to_string(stm.tm_mon)).append(" 需要 0 - 11"));
    if (stm.tm_year <= 0)
        throw std::runtime_error(std::string("年(year) ").append(std::to_string(stm.tm_year)).append(" + 1900"));
}

studio_posix_time::studio_posix_time()
{
    std::scoped_lock lock(m_mutex);
    std::time_t stt = 8 * SEC_IN_HOUR;
    m_tm = *std::gmtime(&stt);
    m_time_point = std::chrono::system_clock::from_time_t(0);
}

studio_posix_time::studio_posix_time(const studio_posix_time& time)
{
    m_tm = time.m_tm;
    m_time_point = time.m_time_point;
}
bool studio_posix_time::from_string(const std::string& str, const std::string& fmt)
{
    std::scoped_lock lock(m_mutex);
    bool status = false;
    try
    {
        std::istringstream ss(str);
        std::tm tmp = {};
        ss >> std::get_time(&tmp, fmt.c_str());
        check_std_tm(tmp);
        // 检查是否成功解析
        if (!ss.fail())
        {
            std::time_t stamp = std::mktime(&tmp);
            m_time_point = std::chrono::system_clock::from_time_t(stamp);
            m_tm = tmp;
            status = true;
        }
        else
        {
            m_err = "转换错误.";
        }
    }
    catch (std::exception& e)
    {
        m_err = e.what();
    }
    return status;
}
std::string studio_posix_time::to_string(const std::string& fmt) const
{
    std::string result;
    try
    {
        check_std_tm(m_tm);
        // 创建一个输出流用于格式化输出
        std::ostringstream oss;
        // 设置格式为 "YYYY-MM-DD HH:MM:SS"
        oss << std::put_time(&m_tm, fmt.c_str());

        // 返回格式化的字符串
        return oss.str();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return result;
}
studio_posix_time::studio_posix_time(const studio_time_stamp& stamp)
{
    std::scoped_lock lock(m_mutex);
    m_time_point = std::chrono::system_clock::from_time_t(stamp);
    fix_tm();
}

studio_posix_time studio_posix_time::operator+(const studio_time_duration& td) const
{
    studio_posix_time result;
    result.m_time_point = m_time_point + std::chrono::hours(td.hours()) + std::chrono::minutes(td.minutes()) + std::chrono::seconds(td.seconds());
    result.fix_tm();
    return result;
}

studio_posix_time& studio_posix_time::operator+=(const studio_time_duration& td)
{
    std::scoped_lock lock(m_mutex);
    m_time_point += std::chrono::seconds(td.total_seconds());
    fix_tm();
    return *this;
}

studio_posix_time studio_posix_time::operator-(const studio_time_duration& td) const
{
    studio_posix_time result;
    result.m_time_point = m_time_point - std::chrono::seconds(td.total_seconds());
    result.fix_tm();
    return result;
}
studio_posix_time& studio_posix_time::operator-=(const studio_time_duration& td)
{
    std::scoped_lock lock(m_mutex);
    m_time_point -= std::chrono::seconds(td.total_seconds());
    fix_tm();
    return *this;
}

studio_time_duration studio_posix_time::operator-(const studio_posix_time& other) const
{
    auto td = std::chrono::duration_cast<std::chrono::seconds>(m_time_point - other.m_time_point);
    return studio_time_duration(td.count());
}

studio_time_stamp studio_posix_time::stamp_sec() const
{
    return std::chrono::system_clock::to_time_t(m_time_point);
}

std::chrono::system_clock::time_point studio_posix_time::time_point() const
{
    return m_time_point;
}

std::tm studio_posix_time::tm() const
{
    return m_tm;
}

int studio_posix_time::year() const
{
    return m_tm.tm_year + 1900;
}

int studio_posix_time::month() const
{
    return m_tm.tm_mon + 1;
}

int studio_posix_time::day() const
{
    return m_tm.tm_mday;
}

int studio_posix_time::hour() const
{
    return m_tm.tm_hour;
}

int studio_posix_time::minute() const
{
    return m_tm.tm_min;
}

int studio_posix_time::second() const
{
    return m_tm.tm_sec;
}

int studio_posix_time::yday() const
{
    return m_tm.tm_yday;
}

int studio_posix_time::wday() const
{
    return m_tm.tm_wday;
}

void studio_posix_time::fix_tm()
{
    std::time_t stt = std::chrono::system_clock::to_time_t(m_time_point);
    stt += 8 * SEC_IN_HOUR;
    // 将 time_t 转换为 tm 结构
    m_tm = *std::gmtime(&stt);
}

bool studio_posix_time::operator>(const studio_posix_time& other) const
{
    return m_time_point > other.m_time_point;
}

bool studio_posix_time::operator==(const studio_posix_time& other) const
{
    return m_time_point == other.m_time_point;
}

bool studio_posix_time::operator<(const studio_posix_time& other) const
{
    return m_time_point < other.m_time_point;
}

bool studio_posix_time::operator>=(const studio_posix_time& other) const
{
    return m_time_point >= other.m_time_point;
}

bool studio_posix_time::operator<=(const studio_posix_time& other) const
{
    return m_time_point <= other.m_time_point;
}

studio_posix_time studio_posix_time::operator=(const studio_posix_time& other)
{
    std::scoped_lock lock(m_mutex);
    m_time_point = other.m_time_point;
    m_tm = other.m_tm;
    return *this;
}
studio_posix_time studio_posix_time::now()
{
    studio_posix_time result;
    result.m_time_point = std::chrono::system_clock::now();
    result.fix_tm();
    return result;
}
studio_posix_time studio_posix_time::time_from_string(const std::string& str, const std::string& fmt)
{
    studio_posix_time result;
    result.from_string(str, fmt);
    return result;
}
std::string studio_posix_time::time_to_string(const studio_posix_time& pt, const std::string& fmt)
{
    return pt.to_string(fmt);
}
bool studio_posix_time::is_not_a_date_time() const
{
    try
    {
        check_std_tm(m_tm);
    }
    catch (...)
    {
        return true;
    }

    return false;
}
