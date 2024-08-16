

#ifndef STUDIO_STR_ALGO_H
#define STUDIO_STR_ALGO_H


#include "studio_macros.h"



class studio_str_algo
{
public:
    /// <summary>
    /// 将字符串str按指定的字符c（可以是空格、制表符、换行符等）进行分割
    /// </summary>
    /// <param name="str"></param>
    /// <param name="c"></param>
    /// <returns></returns>
    static std::vector<std::string> separate(const std::string &str, const char &c);

    /// <summary>
    /// 将字符串str按照字符串s进行分割
    /// </summary>
    /// <param name="str"></param>
    /// <param name="s"></param>
    /// <returns></returns>
    static std::vector<std::string> separate(const std::string &str, const std::string &s);

    /// <summary>
    /// 字符串的替换
    /// </summary>
    /// <param name="src">源字符串</param>
    /// <param name="find">要查找的字符串</param>
    /// <param name="rep">要替换的字符串</param>
    /// <returns></returns>
    static std::string replace(const std::string &src, const std::string &find, const std::string rep);

    studio_str_algo() = default;
    ~studio_str_algo() = default;

private:
    
};


#endif   // STUDIO_STR_ALGO_H


