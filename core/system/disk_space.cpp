
#include "disk_space.h"

void studio_diskspace::checkDiskSpace(const std::string& path)
{
    std::filesystem::space_info si = std::filesystem::space(path);

    total = static_cast<double>(si.capacity) / (1024 * 1024 * 1024);
    free = static_cast<double>(si.free) / (1024 * 1024 * 1024);
    available = static_cast<double>(si.available) / (1024 * 1024 * 1024);

    used_rate = (total - available) / total;
    available_rate = available / total;
}


