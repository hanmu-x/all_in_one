
#ifndef STUDIO_JSON_H
#define STUDIO_JSON_H


#include "studio_macros.h"
#include <json/json.h>


class studio_json_opt
{
  public:
    bool utf8{true};
    size_t precision{0};  // 小数精度, 为0则不处理
};

class studio_json
{
  public:
    /// <summary>
    /// 从文件加载json内容
    /// </summary>
    /// <param name="file"></param>
    /// <returns></returns>
    static Json::Value loadJsonOfFile(const std::string& file);

    /// <summary>
    /// 从字符串加载json内容
    /// </summary>
    /// <param name="content"></param>
    /// <returns></returns>
    static Json::Value loadJsonOfString(const std::string& content);
    
    /// <summary>
    /// 将json内容解析到字符串中
    /// </summary>
    /// <param name="root"></param>
    /// <param name="opt">格式化方式</param>
    static std::string dumpsJsonToString(const Json::Value& root, const studio_json_opt& opt = {true, 0});


    /// <summary>
    /// 将json内容写入文件(覆盖写入,自动缩进,编码设置为UTF-8)
    /// </summary>
    /// <param name="root"></param>
    /// <param name="file"></param>
    /// <returns></returns>
    static bool writeJsonToFile(const Json::Value& root, const std::string& file);


    static std::string to_string(const Json::Value root, const studio_json_opt& opt = {true, 0});

    static void find_by_key(const std::string& json, const std::string& key, const std::string& filter, std::vector<std::string>& arr);

    static void find_by_key(const Json::Value& root, const std::string& key, const std::string& filter, std::vector<std::string>& arr);

    /// 检查json中指定key的数据类型,如果正确,则赋值,并且返回true,否则返回false
    static bool check_member_object(const Json::Value& root, const std::string& key, Json::Value& jv_obj);
    static bool check_member_array(const Json::Value& root, const std::string& key, Json::Value& jv_arr);
    static bool check_member_string(const Json::Value& root, const std::string& key, std::string& val);
    static bool check_member_int(const Json::Value& root, const std::string& key, int& val);
    static bool check_member_double(const Json::Value& root, const std::string& key, double& val);
    static bool check_member_bool(const Json::Value& root, const std::string& key, bool& val);
    static bool check_member_uint(const Json::Value& root, const std::string& key, int32_t& val);
    static bool check_member_long(const Json::Value& root, const std::string& key, int64_t& val);
    static bool check_member_ulong(const Json::Value& root, const std::string& key, uint64_t& val);
};












#endif // STUDIO_JSON_H
