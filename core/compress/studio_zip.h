
#ifndef STUDIO_ZIP_H
#define STUDIO_ZIP_H

#include "studio_macros.h"

class StudioMiniZip
{
  public:
    /// <summary>
    /// 将文件或目录压缩为ZIP文件
    /// </summary>
    /// <param name="s_src">被压缩文件或目录地址</param>
    /// <param name="s_dst">生成解压文件路径</param>
    /// <param name="append">文件存在是否追加</param>
    /// <returns></returns>
    static bool compress(const std::string& s_src, const std::string& s_dst = "", const bool& append = false);

    /// <summary>
    /// 解压zip文件,解压单独文件和目录文件
    /// </summary>
    /// <param name="s_src">待解压文件路径</param>
    /// <param name="s_dst">解压输出路径</param>
    /// <returns></returns>
    static bool decompress(const std::string& s_src, const std::string& s_dst = "");

    /// <summary>
    /// 压缩内存数据
    /// </summary>
    /// <param name="c_in_val">待压缩内存数据</param>
    /// <param name="i_in_len">待压缩内存数据大小</param>
    /// <param name="c_out_val">压缩数据输出</param>
    /// <param name="i_out_len">压缩数据输出大小</param>
    /// <returns></returns>
    /// 注: 如果c_in_val是一个字符串类型的数据要考虑字符串结尾的'\0',需对字符串类型的c_in_val进行strlen(c_in_val) + 1
    static bool compress(const char* c_in_val, const size_t& i_in_len, char** c_out_val, size_t& i_out_len);

    /// <summary>
    /// 解压内存数据
    /// </summary>
    /// <param name="c_in_val">待解压内存数据</param>
    /// <param name="i_in_len">待解压内存数据大小</param>
    /// <param name="c_out_val">解压数据输出</param>
    /// <param name="i_out_len">解压数据输出大小</param>
    /// <returns></returns>
    static bool decompress(const char* c_in_val, const size_t& i_in_len, char** c_out_val, size_t& i_out_len);

    StudioMiniZip() = default;
    ~StudioMiniZip() = default;

  private:
};










#endif  // STUDIO_ZIP_H