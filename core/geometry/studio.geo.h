/*
   几何数据结构
*/

#ifndef STUDIO_GEO_H
#define STUDIO_GEO_H

#include "studio_macros.h"

// geometry types
// 点
#define GEOJSON_GEOMETRY_POINT "Point"
// 线
#define GEOJSON_GEOMETRY_LINE_STRING "LineString"
// 面
#define GEOJSON_GEOMETRY_POLYGON "Polygon"
// 多点
#define GEOJSON_GEOMETRY_MULTI_POINT "MultiPoint"
// 多线
#define GEOJSON_GEOMETRY_MULTI_LINE_STRING "MultiLineString"
// 多面
#define GEOJSON_GEOMETRY_MULTI_POLYGON "MultiPolygon"
// 复合类型
#define GEOJSON_GEOMETRY_COLLECTION "GeometryCollection"

// 参照GDAL

enum class enum_geometry_type
{
    egtInvalid = 0,          // 无效
    egtPoint = 1,            // 单点
    egtLineString = 2,       // 单线
    egtPolygon = 3,          // 单面
    egtMultiPoint = 4,       // 多点
    egtMultiLineString = 5,  // 多线
    egtMultiPolygon = 6,     // 多面
    egtCompositeType = 7,    // 复合数据类型

};


/****************************************/
/// 点
/****************************************/
class studio_point
{
  public:
    studio_point() = default;
    ~studio_point() = default;

    studio_point(double xx, double yy)
    {
        x = xx;
        y = yy;
    }

    studio_point& operator=(const studio_point& point)
    {
        x = point.x;
        y = point.y;
        return *this;
    }

    studio_point operator+(const studio_point& point) const
    {
        studio_point ret(x + point.x, y + point.y);
        return ret;
    }
    studio_point operator+=(const studio_point& point)
    {
        this->x += point.x;
        this->y += point.y;
        return *this;
    }

    studio_point operator-(const studio_point& point) const
    {
        studio_point ret(x - point.x, y - point.y);
        return ret;
    }
    studio_point operator-=(const studio_point& point)
    {
        this->x -= point.x;
        this->y -= point.y;
        return *this;
    }

    studio_point operator*(double scale) const
    {
        studio_point ret(x * scale, y * scale);
        return ret;
    }

    studio_point operator*(const studio_point& point) const
    {
        studio_point ret(x * point.x, y * point.y);
        return ret;
    }

    studio_point operator*=(double scale)
    {
        this->x *= scale;
        this->y *= scale;
        return *this;
    }

    studio_point operator*=(const studio_point& point)
    {
        this->y *= point.y;
        this->x *= point.x;
        return *this;
    }

    studio_point operator/(double scale) const
    {
        return studio_point(x / scale, y / scale);
    }

    studio_point operator/(const studio_point& point) const
    {
        return studio_point(x / point.x, y / point.y);
    }

    studio_point operator/=(double scale)
    {
        this->x /= scale;
        this->y /= scale;
        return *this;
    }

    studio_point operator/=(const studio_point& point)
    {
        this->y /= point.y;
        this->x /= point.x;
        return *this;
    }

    bool operator==(const studio_point& point) const
    {
        return std::abs(point.x - this->x) <= AO_EPSILON && std::abs(point.y - this->y) <= AO_EPSILON;
    }

    bool operator<(const studio_point& point) const
    {
        return point.y < y || (point.y == y && point.x < x);
    }

    bool operator>(const studio_point& point) const
    {
        return point.y > y || (point.y == y && point.x > x);
    }

    bool operator!=(const studio_point& point) const
    {
        return std::abs(point.x - this->x) > AO_EPSILON || std::abs(point.y - this->y) > AO_EPSILON;
    }

  public:
    double x{0.};
    double y{0.};
};

/****************************************/
/// 多点
/****************************************/
class studio_multi_point : public std::vector<studio_point>
{
  public:
    studio_multi_point() = default;
    ~studio_multi_point() = default;
    studio_multi_point(std::vector<studio_point> points) : std::vector<studio_point>(std::move(points))
    {
    }
};


/****************************************/
/// 线
/****************************************/
class studio_line : public std::vector<studio_point>
{
  public:
    studio_line() = default;
    ~studio_line() = default;
    studio_line(std::vector<studio_point> points) : std::vector<studio_point>(std::move(points))
    {
    }
};

/****************************************/
/// 多线
/****************************************/
class studio_multi_studio_line : public std::vector<studio_line>
{
  public:
    studio_multi_studio_line() = default;
    ~studio_multi_studio_line() = default;

  public:
};

/****************************************/
/// 环, 首尾相连的一条线
/****************************************/
class studio_ring
{
  public:
    studio_ring() = default;
    ~studio_ring() = default;

  public:
    std::vector<studio_point> points;
    int is_outer{1};
};

/****************************************/
/// 面
/****************************************/
class studio_poly
{
  public:
    studio_poly() = default;
    ~studio_poly() = default;

  public:
    studio_ring outer_ring;                // 外环
    std::vector<studio_ring> inner_rings;  // 内环
};

/****************************************/
/// 多面
/****************************************/
class studio_multi_poly : public std::vector<studio_poly>
{
  public:
    studio_multi_poly() = default;
    ~studio_multi_poly() = default;

  public:
};


/****************************************/
/// 矩形框
/****************************************/
class studio_rect  // 普通坐标点
{
  public:
    studio_rect() = default;
    ~studio_rect() = default;

    studio_rect(double l, double t, double r, double b)
    {
        min.x = l;
        max.y = t;
        max.x = r;
        min.y = b;
    }

    void correct()
    {
        if (min.x > max.x)
        {
            std::swap(min.x, max.x);  // 使用 std::swap 简化交换操作
        }
        if (max.y > max.y)
        {
            std::swap(max.y, max.y);  // 使用 std::swap 简化交换操作
        }
    }

    studio_rect& operator=(const studio_rect& rect) = default;

    bool operator==(const studio_rect& rect) const
    {
        bool result = true;
        result &= std::abs(rect.min.x - this->min.x) <= AO_EPSILON;
        result &= std::abs(rect.max.y - this->max.y) <= AO_EPSILON;
        result &= std::abs(rect.max.x - this->max.x) <= AO_EPSILON;
        result &= std::abs(rect.max.y - this->max.y) <= AO_EPSILON;
        return result;
    }

    bool operator!=(const studio_rect& rect) const
    {
        bool result = true;
        result &= std::abs(rect.min.x - this->min.x) > AO_EPSILON;
        result &= std::abs(rect.max.y - this->max.y) > AO_EPSILON;
        result &= std::abs(rect.max.x - this->max.x) > AO_EPSILON;
        result &= std::abs(rect.max.y - this->max.y) > AO_EPSILON;
        return result;
    }

    /// 两个矩形框是否相交
    bool intersect(const studio_rect& rect) const
    {
        double zx = std::abs(rect.min.x + rect.max.x - min.x - max.x);
        double x = std::abs(rect.min.x - rect.max.x) + std::abs(min.x - max.x);
        double zy = std::abs(rect.max.y + rect.max.y - max.y - max.y);
        double y = std::abs(rect.max.y - rect.max.y) + std::abs(max.y - max.y);
        if (zx <= x && zy <= y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

  public:
    studio_point min;
    studio_point max;
};
using studio_geo_rect = studio_rect;


/****************************************/
/// 圆
/****************************************/
class studio_circle
{
  public:
    studio_circle() = default;
    ~studio_circle() = default;
    studio_circle(studio_point center, double radius) : center(center), radius(radius)
    {
    }

    double area() const
    {
        return M_PI * radius * radius;
    }

  public:
    studio_point center;
    double radius;
};


/****************************************/
/// 三角形
/****************************************/
class studio_triangle
{
  public:
    studio_triangle() = default;
    ~studio_triangle() = default;
    studio_triangle(studio_point a, studio_point b, studio_point c) : a(a), b(b), c(c)
    {
    }

    /// 有向面积
    double oriented_area()
    {
        return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2;
    }

    double area()
    {
        return std::abs(oriented_area());
    }

    /// 外接圆
    studio_circle circumscribed_circle()
    {
        // 计算外接圆的中心
        double A = a.x * a.x + a.y * a.y;
        double B = b.x * b.x + b.y * b.y;
        double C = c.x * c.x + c.y * c.y;
        double D = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

        studio_circle circle;
        if (D == 0)
        {
            // 如果D为0，则无法计算外接圆
            throw std::runtime_error("无法计算外接圆");
        }

        circle.center.x = (a.x * (B - C) + b.x * (C - A) + c.x * (A - B)) / (2 * D);
        circle.center.y = (a.y * (B - C) + b.y * (C - A) + c.y * (A - B)) / (2 * D);

        // 计算半径
        circle.radius = sqrt((circle.center.x - a.x) * (circle.center.x - a.x) + (circle.center.y - a.y) * (circle.center.y - a.y));

        return circle;
    }

    /// 顶点a的角度
    double angle_a() const
    {
        return std::acos((b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y)) * 180 / M_PI;
    }

    /// 顶点b的角度
    double angle_b() const
    {
        return std::acos((a.x - b.x) * (c.x - b.x) + (a.y - b.y) * (c.y - b.y)) * 180 / M_PI;
    }

    /// 顶点c的角度
    double angle_c() const
    {
        return std::acos((a.x - c.x) * (b.x - c.x) + (a.y - c.y) * (b.y - c.y)) * 180 / M_PI;
    }

  public:
    studio_point a;
    studio_point b;
    studio_point c;
};


/****************************************/
/// 椭圆
/****************************************/
class studio_ellipse
{
  public:
    studio_ellipse() = default;
    ~studio_ellipse() = default;
    studio_ellipse(studio_point p, double x, double y) : center(p), rx(x), ry(y)
    {
    }

    double area() const
    {
        return M_PI * rx * ry;
    }

    /// 周长
    /// Srinivasa Ramanujan 提出的两个近似公式, 1会更准确
    double circumference(const int& Ramanujan = 1) const
    {
        if (Ramanujan == 1)
        {
            return M_PI * (3 * (rx + ry) - sqrt((3 * rx + ry) * (rx + 3 * ry)));
        }

        return 2 * M_PI * sqrt((rx * rx + ry * ry) / 2);
    }

  public:
    studio_point center;  // 中心点
    // 长半轴 和 短半轴, 不分
    double rx;
    double ry;
};



#endif  // STUDIO_GEO_H