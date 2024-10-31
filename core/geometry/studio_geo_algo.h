
/*
   几何算法库
   包含：扫描线算法, 射线算法判断点是否在多边形内
*/

#ifndef STUDIO_GEO_ALGO_H
#define STUDIO_GEO_ALGO_H

#include "studio_macros.h"
#include "studio.geo.h"

struct raster_point
{
    raster_point() = default;
    raster_point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    int x{0}, y{0};
};
struct cover_pair
{
    int beg;
    int end;
};

/// 射线算法判断点是否在多边形内
class ray_algo
{
    /// <summary>
    /// 点是否与矢量面相交(射线算法),点的相交在面内或者在边界上都算是相交
    /// </summary>
    /// <param name="mpoly"></param>
    /// <param name="point"></param>
    /// <returns></returns>
    static bool intersect(const studio_poly& mpoly, const studio_point& point);
    static bool intersect(const studio_point& point, const std::vector<studio_point>& points);
};


/// 扫描线算法
class scan_line_algo
{
  public:

    void set(const studio_geo_rect& rect, const double& cell_size);
    int width() const;
    int height() const;
    double cell_size() const;

    /// <summary>
    /// 扫描单点
    /// </summary>
    /// <param name="line"></param>
    /// <returns></returns>
    bool scanning(const studio_point& point);

    /// <summary>
    /// 扫描多点
    /// </summary>
    /// <param name="points">多点</param>
    /// <returns></returns>
    bool scanning(const studio_multi_point& points);

    /// <summary>
    /// 扫描单线的算法
    /// </summary>
    /// <param name="line"></param>
    /// <returns></returns>
    bool scanning(const studio_line& line);

    /// <summary>
    /// 扫描多条线
    /// </summary>
    /// <param name="lines">多线</param>
    /// <returns></returns>
    bool scanning(const studio_multi_studio_line& lines);

    
    bool scanning(const std::vector<std::vector<raster_point>> vertices_arr);

    /// <summary>
    /// 扫描一个单点矢量
    /// </summary>
    /// <param name="poly"></param>
    /// <returns></returns>
    bool scanning(const studio_poly& poly);

    /// <summary>
    /// 扫描一个多面矢量
    /// </summary>
    /// <param name="m_polys"></param>
    /// <returns></returns>
    bool scanning(const studio_multi_poly& m_polys);

    void check_line_point(studio_point point, std::vector<raster_point>& vct, int& last_x, int& last_y);


        /// <summary>
    /// 点 线 不会闭合, 可能会存在一些点重合
    /// </summary>
    /// <returns></returns>
    void slim();

  private:
    // 数据记录以经纬度左上角为原点, 向东为col的正方向,向下为row的正方向
    int m_width{0};
    int m_height{0};
    studio_geo_rect m_rect;
    // 经纬度小数点后6位能精确到1米,更加精确意义不大
    double m_cell_size{0.000001};
    // 记录每一行在矢量内的多对起始列号
    std::map<int, std::vector<cover_pair>> m_row_pairs;
};






#endif // STUDIO_GEO_ALGO_H





