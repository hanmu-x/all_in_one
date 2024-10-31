
#include "studio_geo_algo.h"

/////////////// 射线算法 //////////////////

bool ray_algo::intersect(const studio_point& point, const std::vector<studio_point>& points)
{
    int i, j;
    double d;
    int num = points.size();
    bool c = false;
    for (i = 0, j = num - 1; i < num; j = i++)
    {
        d = (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x;
        if (point.x == d)
        {
            return false;
        }

        if ((((points[i].y <= point.y) && (point.y < points[j].y) || ((points[j].y <= point.y) && (point.y < points[i].y))) && (point.x < d)))
        {
            c = !c;
        }
    }
    return c;
}

bool ray_algo::intersect(const studio_poly& mpoly, const studio_point& point)
{
    int intersections = 0;
    studio_point ray_end(point.x + 1000, point.y);  // 向右引一条射线 1000单位

    // 外环
    bool is_in_outer_ring = intersect(point, mpoly.outer_ring.points);
    if (is_in_outer_ring)
    {
        // 内环
        for (const auto& inner : mpoly.inner_rings)
        {
            if (intersect(point, inner.points))  // 在内环内
            {
                return false;  // 如果这个点在一个内环内就属于在面外
            }
        }
        return true;  // 点在外环内,且不在任何一个内环内
    }
    else
    {
        return false;
    }
}

//////////// 扫描线算法 ///////////

void scan_line_algo::set(const studio_geo_rect& rect, const double& cell_size)
{
    m_rect = rect;
    m_rect.correct();
    m_cell_size = cell_size;
    m_width = static_cast<int>(std::ceil((m_rect.right_bottom.x - m_rect.left_top.x) / m_cell_size));
    m_height = static_cast<int>(std::ceil((m_rect.right_bottom.y - m_rect.left_top.y) / m_cell_size));
}

int scan_line_algo::width() const
{
    return m_width;
}
int scan_line_algo::height() const
{
    return m_height;
}

double scan_line_algo::cell_size() const
{
    return m_cell_size;
}

bool scan_line_algo::scanning(const studio_point& point)
{
    int raster_x = std::round((point.x - m_rect.left_top.x) / m_cell_size);
    int raster_y = std::round((m_rect.right_bottom.y - point.y) / m_cell_size);
    if (raster_x >= 0 && raster_x <= m_width && raster_y >= 0 && raster_y <= m_height)
    {
        m_row_pairs[raster_y].push_back({raster_x, raster_x});
        return true;
    }
    return false;
}

bool scan_line_algo::scanning(const studio_multi_point& points)
{
    // m_row_pairs.clear();
    for (const auto& point : points)
    {
        scanning(point);
    }
    slim();
    return true;
}

bool scan_line_algo::scanning(const studio_line& line)
{
    double cel_size = m_cell_size;
    if (line.size() < 2)
    {
        return false;  // 如果线段小于两个点，则无法处理
    }
    // 遍历线段中的每对点
    for (size_t i = 0; i < line.size() - 1; ++i)
    {
        const studio_point& p1 = line[i];
        const studio_point& p2 = line[i + 1];

        // 将经纬度转换为栅格列和行
        int col1 = std::round((p1.x - m_rect.left_top.x) / cel_size);
        int row1 = std::round((m_rect.left_top.y - p1.y) / cel_size);
        int col2 = std::round((p2.x - m_rect.left_top.x) / cel_size);
        int row2 = std::round((m_rect.left_top.y - p2.y) / cel_size);

        // 处理垂直线段
        if (col1 == col2)
        {
            int start_row = std::min(row1, row2);
            int end_row = std::max(row1, row2);
            for (int row = start_row; row <= end_row; ++row)
            {
                if (row >= 0 && row < height())
                {
                    m_row_pairs[row].push_back({col1, col1});
                }
            }
            continue;
        }

        // 处理水平线段
        if (row1 == row2)
        {
            int beg = std::min(col1, col2);
            int end = std::max(col1, col2);
            if (beg >= 0 && beg < width() && end >= 0 && end < width())
            {
                m_row_pairs[row1].push_back({beg, end});
            }
            continue;
        }

        // 计算斜率和截距
        float slope = (p2.y - p1.y) / (p2.x - p1.x);
        float intercept = p1.y - slope * p1.x;

        int min_col = std::min(col1, col2);  // 最小x
        int max_col = std::max(col1, col2);  // 最大x

        int min_row = std::min(row1, row2);  // 最小y
        int max_row = std::max(row1, row2);  // 最大y

        // 对于每一列，找到对应的行
        for (int col = min_col; col <= max_col; ++col)
        {
            // 使用斜率和截距计算该列对应的行
            float y = slope * ((col + 0.5) * cel_size + m_rect.left_top.x) + intercept;  // 使用0.5是为了确保点在栅格中心
            int row = std::round((m_rect.left_top.y - y) / cel_size);
            // 确保行在范围内
            if (row >= min_row && row <= max_row && row >= 0 && row < height() && col >= 0 && col < width())
            {
                // 添加该点到对应行的列表中
                m_row_pairs[row].push_back({col, col});
            }
        }
    }

    slim();
    return true;
}

bool scan_line_algo::scanning(const studio_multi_studio_line& lines)
{
    // m_row_pairs.clear();
    for (const auto& line : lines)
    {
        scanning(line);
    }
    slim();

    return true;
}

bool scan_line_algo::scanning(const std::vector<std::vector<raster_point>> vertices_arr)
{
    int minY = INT_MAX, maxY = 0;
    int minX = INT_MAX, maxX = 0;

    for (const auto& part : vertices_arr)
    {
        for (const auto& point : part)
        {
            minY = AO_MAX(0, AO_MIN(minY, point.y));
            maxY = AO_MAX(0, AO_MAX(maxY, point.y));
            minX = AO_MAX(0, AO_MIN(minX, point.x));
            maxX = AO_MAX(0, AO_MAX(maxX, point.x));
        }
    }

    // 对每一条扫描线进行处理
    for (int scanY = minY; scanY <= maxY; ++scanY)
    {
        // 构建边缘列表
        std::vector<int> edges;
        for (int part = 0; part < vertices_arr.size(); ++part)
        {
            auto vertices = vertices_arr[part];
            int numVertices = vertices.size();
            for (int i = 0; i < numVertices; ++i)
            {
                raster_point v1 = vertices[i];
                raster_point v2 = vertices[(i + 1) % numVertices];
                if ((scanY >= v1.y && scanY < v2.y) || (scanY >= v2.y && scanY < v1.y))  // v1 v2 不在同一行
                {
                    float slope = (v2.x - v1.x) / (v2.y - v1.y);
                    float x = (scanY - v1.y) * slope + v1.x;
                    edges.push_back(static_cast<int>(x));
                }
                else if (v1.y == v2.y && scanY == v1.y)  // v1 v2 在同一行
                {
                    edges.push_back(v1.x);
                    edges.push_back(v2.x);
                }
            }
        }
        // 根据X值对边缘进行排序
        std::sort(edges.begin(), edges.end());
        for (int i = 0; i < edges.size(); i += 2)
        {
            cover_pair tmp_pair;
            tmp_pair.beg = edges[i];
            tmp_pair.end = edges[i + 1];
            m_row_pairs[scanY].push_back(tmp_pair);
        }
    }
    return true;
}

bool scan_line_algo::scanning(const studio_poly& poly)
{
    // m_row_pairs.clear();
    std::vector<std::vector<raster_point>> vertices_arr;

    // 将点转换为光栅坐标并合并连续的相同点
    int last_x = 0 - m_width;
    int last_y = 0 - m_height;
    std::vector<raster_point> tmp_vertices;

    for (const auto& point : poly.outer_ring.points)
    {
        check_line_point(point, tmp_vertices, last_x, last_y);
    }
    vertices_arr.push_back(tmp_vertices);

    for (const auto& ring : poly.inner_rings)
    {
        tmp_vertices.clear();
        last_x = 0 - m_width;
        last_y = 0 - m_height;
        for (const auto& point : ring.points)
        {
            check_line_point(point, tmp_vertices, last_x, last_y);
        }
        vertices_arr.push_back(tmp_vertices);
    }

    return scanning(vertices_arr);
}

bool scan_line_algo::scanning(const studio_multi_poly& m_polys)
{
    // m_row_pairs.clear();
    std::vector<std::vector<raster_point>> vertices_arr;

    for (const auto& poly : m_polys)
    {
        // 由于精度(m_cell_size)问题,可能会导致一个矢量中有大量重复的连续栅格点,将这部分连续栅格点归并为一个
        int last_x = 0 - m_width;
        int last_y = 0 - m_height;
        for (const auto& ring : poly.inner_rings)
        {
            std::vector<raster_point> tmp_vertices;
            for (const auto& point : ring.points)
            {
                check_line_point(point, tmp_vertices, last_x, last_y);
            }
            vertices_arr.push_back(tmp_vertices);
        }
        std::vector<raster_point> tmp_vertices;

        for (const auto& point : poly.outer_ring.points)
        {
            check_line_point(point, tmp_vertices, last_x, last_y);
        }
        vertices_arr.push_back(tmp_vertices);
    }

    return scanning(vertices_arr);
}

void scan_line_algo::check_line_point(studio_point point, std::vector<raster_point>& vct, int& last_x, int& last_y)
{
    // m_row_pairs.clear();
    int tmp_x = std::round((point.x - m_rect.left_top.x) / m_cell_size);
    int tmp_y = std::round((m_rect.right_bottom.y - point.y) / m_cell_size);
    if (last_x != tmp_x || last_y != tmp_y)
    {
        vct.push_back(raster_point(tmp_x, tmp_y));
        last_x = tmp_x;
        last_y = tmp_y;
    }
}
void scan_line_algo::slim()
{
    std::map<int, std::map<int, int>> r_c_i;
    for (auto [r, cs] : m_row_pairs)
    {
        if (r < 0 || r >= m_height)
        {
            continue;
        }
        for (auto c : cs)
        {
            if (c.beg < 0 || c.beg >= m_width)
            {
                continue;
            }

            r_c_i[r][c.beg] = 0;
        }
    }
    m_row_pairs.clear();
    for (auto [r, c_i] : r_c_i)
    {
        for (auto [c, i] : c_i)
        {
            m_row_pairs[r].push_back({c, c});
        }
    }
}

