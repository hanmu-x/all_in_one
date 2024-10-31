/*
   计时器
*/

#ifndef SILLY_UTILS_SILLY_TIMER_H
#define SILLY_UTILS_SILLY_TIMER_H

#include "studio_macros.h"

class studio_timer
{
  public:
    /// <summary>
    /// 构造函数,初始化start,并且开始计时
    /// </summary>
    studio_timer()
    {
        m_start = std::chrono::system_clock::now();
    }

    /// <summary>
    /// 重新开始计时
    /// </summary>
    void restart()
    {
        m_start = std::chrono::system_clock::now();
    }

    /// <summary>
    /// 获取经过从开始计时经过的毫秒数
    /// </summary>
    /// <returns></returns>
    double elapsed_ms()
    {
        auto tmp = std::chrono::system_clock::now();
        return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(tmp - m_start).count());
    }

    /// <summary>
    /// 打印从初始化或者从上一次restart开始经过的时间
    /// </summary>
    void timed_print()
    {
        std::cout << "time cost: " << elapsed_ms() << " ms  "
            << elapsed_ms() / 1000 << " s  " 
            << elapsed_ms() / 1000 / 60 << " min  " << std::endl;
    }


  private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::chrono::time_point<std::chrono::system_clock> m_end;
};

#define STUDIO_TIMER_COST_MS(timer) std::cout << SU_FILE_NAME << ":" << __LINE__ << "\t" << timer.elapsed_ms() << " ms" << std::endl;
#define STUDIO_TIMER_COST_SEC(timer) std::cout << SU_FILE_NAME << ":" << __LINE__ << "\t" << timer.elapsed_ms() / 1000 << " sec" << std::endl;

#endif  // STUDIO_TIMER_H
