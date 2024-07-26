
#include "studio_str_algo.h"


std::vector<std::string> studio_str_algo::separate(const std::string &str, const char &c)
{
    // 初始化分割后的字符串数组
    std::vector<std::string> results;
    // 初始化字符串的起始位置
    size_t pos1 = 0;
    // 初始化字符串的结束位置
    size_t pos0 = 0;
    // 获取字符串的长度
    size_t total = str.size();
    // 拷贝字符串
    std::string n_str = str;

    // 遍历字符串
    while (pos1 < total)
    {
        // 如果当前字符等于指定的字符c
        if (n_str[pos1] == c)
        {
            // 截取字符串从pos0到pos1的位置
            std::string tmp = n_str.substr(pos0, pos1 - pos0);
            // 将截取的字符串添加到结果数组中
            results.push_back(tmp);
            // 更新pos0的位置
            pos0 = pos1 + 1;
        }
        // 遍历字符串的下一个字符
        pos1++;
    }
    // 如果pos0的位置不等于字符串的长度，将剩余的字符串添加到结果数组中
    if (pos0 != total)
    {
        results.push_back(str.substr(pos0, total - pos0));
    }

    return results;
}


std::vector<std::string> studio_str_algo::separate(const std::string &str, const std::string &s)
{
    std::vector<std::string> results;
    size_t pos_s = s.size();
    size_t pos_s0 = 0;
    size_t post_se = 0;
    size_t pos1 = 0;
    size_t pos0 = 0;
    size_t total = str.size() - pos_s;

    // 当pos1小于total时，循环执行
    while (pos1 < total)
    {
        // 将pos_s0置为0，然后遍历字符串s，直到完全匹配上
        pos_s0 = 0;
        while (pos_s0 < pos_s && str[pos1 + pos_s0] == s[pos_s0])
        {
            pos_s0++;
        }
        // 如果完全匹配上，将str的substr存入results中，并将pos1和pos0分别加pos_s
        if (pos_s0 == pos_s)  // 完全匹配上
        {
            std::string tmp = str.substr(pos0, pos1 - pos0);
            results.push_back(tmp);
            pos1 = pos1 + pos_s;
            pos0 = pos1;
        }
        // 将pos1加1
        pos1++;
    }
    // 将pos_s0置为0，然后遍历字符串s，直到完全匹配上
    pos_s0 = 0;
    while (pos_s0 < pos_s && str[pos1 + pos_s0] == s[pos_s0])
    {
        pos_s0++;
    }
    // 如果完全匹配上，将str的substr存入results中，并将pos1和pos0分别加pos_s
    if (pos_s0 == pos_s)  // 完全匹配上
    {
        std::string tmp = str.substr(pos0, pos1 - pos0);
        results.push_back(tmp);
        pos1 = pos1 + pos_s;
        pos0 = pos1;
    }
    // 如果pos0不等于pos1，将str的substr存入results中
    else
    {
        if (pos0 != pos1)
        {
            results.push_back(str.substr(pos0, str.size() - pos0));
        }
    }

    return results;
}



std::string studio_str_algo::replace(const std::string &src, const std::string &find, const std::string rep)
{
    std::string result = src;
    // 定义一个变量pos，用于存储查找字符串在结果字符串中的位置
    size_t pos = 0;
    // 当pos不等于std::string::npos时，执行循环
    while ((pos = result.find(find, pos)) != std::string::npos)
    {
        // 将结果字符串中pos位置的find字符串替换为rep字符串
        result.replace(pos, find.length(), rep);
        // 将pos的值增加rep字符串的长度
        pos += rep.length();  
    }

    return result;
}















