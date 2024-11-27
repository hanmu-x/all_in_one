
#ifndef DISK_SPACE_H
#define DISK_SPACE_H

#include "studio_macros.h"

class studio_diskspace
{
  private:
    double total{0.0};
    double free{0.0};
    double available{0.0};
    double used_rate{0.0};
    double available_rate{0.0};

  public:
    /// <summary>
    /// 检测磁盘空间
    /// </summary>
    /// <param name="path"></param>
    void checkDiskSpace(const std::string& path);

    double getTotal() const
    {
        return total;
    }
    double getFree() const
    {
        return free;
    }
    double getAvailable() const
    {
        return available;
    }
    double getUsedRate() const
    {
        return used_rate;
    }
    double getAvailableRate() const
    {
        return available_rate;
    }
};

#endif  // DISK_SPACE_H