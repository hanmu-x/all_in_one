
/// 后台程序

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "studio_macros.h"

struct prj_info
{
    std::string name;
    std::string path;
    unsigned int pid;
    bool status;
};

class studio_background
{
  public:
    /// <summary>
    /// 获取所有进程
    /// </summary>
    /// <returns></returns>
    bool getAllPrj();

    /// <summary>
    /// 关闭进程
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool stopPrj(const std::string& name);

  public:
    std::unordered_map<std::string, std::vector<prj_info>> prj_list;
};

#endif  // BACKGROUND_H