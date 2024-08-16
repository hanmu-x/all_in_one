
#include "studio_json.h"


Json::Value studio_json::loadJsonOfFile(const std::string& file)
{
    std::fstream input;
    input.open(file, std::ios::binary | std::ios::in);
    if (!input.is_open())
    {
        return Json::nullValue;
    }
    Json::Reader reader;
    Json::Value root;

    if (reader.parse(input, root))
    {
        return root;
    }
    else
    {
        root = Json::nullValue;
    }
    input.close();
    return root;
}

Json::Value studio_json::loadJsonOfString(const std::string& content)
{
    Json::Reader reader;
    Json::Value root;

    if (reader.parse(content, root))
    {
        return root;
    }
    return Json::nullValue;
}

bool studio_json::writeJsonToFile(const Json::Value& root, const std::string& file)
{
    bool status = false;

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "    ";  // 设置有自动缩进的,若禁用缩进为""
    builder["emitUTF8"] = true;  // 显式设置为 UTF-8
    
    // 创建一个 StreamWriter
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

    std::ofstream outFile(file, std::ios::out);
    if (outFile.is_open())
    {
        writer->write(root, &outFile);
        outFile.close();
        status = true;
    }
    else
    {
        // 文件打开失败
        std::cout << "Failed to open file: " << file << std::endl;
        status = false;
    }
    return status;
}












std::string studio_json::to_string(const Json::Value root, const studio_json_opt& opt)
{
    Json::StreamWriterBuilder stream_builder;
    if (opt.utf8)
    {
        stream_builder["emitUTF8"] = true;
    }

    if (opt.precision)
    {
        stream_builder["precision"] = opt.precision;
        // decimal 仅小小数位保留    123456.789 保留 1位 是123456.7
        // significant 整个数字保留  123456.789 保留 7位 是123456.7
        stream_builder["precisionType"] = "decimal";  //
    }

    std::ostringstream stream;

    std::unique_ptr<Json::StreamWriter> writer(stream_builder.newStreamWriter());
    writer->write(root, &stream);
    return stream.str();
}
void find_object(const Json::Value jv_obj, const std::string& key, const std::string& filter, std::vector<std::string>& arr);
void find_array(const Json::Value jv_arr, const std::string& key, const std::string& filter, std::vector<std::string>& arr);

void find_array(const Json::Value jv_arr, const std::string& key, const std::string& filter, std::vector<std::string>& arr)
{
    for (auto jv_tmp : jv_arr)
    {
        if (jv_tmp.isArray())
        {
            find_array(jv_tmp, key, filter, arr);
        }
        else if (jv_tmp.isObject())
        {
            find_object(jv_tmp, key, filter, arr);
        }
    }
}

void find_object(const Json::Value jv_obj, const std::string& key, const std::string& filter, std::vector<std::string>& arr)
{
    for (auto name : jv_obj.getMemberNames())
    {
        if (name == key)
        {
            if (jv_obj[name].isString())
            {
                std::string content = jv_obj[name].asString();
                if (filter.empty())
                {
                    arr.push_back(content);
                }
                else
                {
                    if (content.find(filter) < content.size())
                    {
                        arr.push_back(content);
                    }
                }
            }
        }
        if (jv_obj[name].isArray())
        {
            find_array(jv_obj[name], key, filter, arr);
        }
        else if (jv_obj[name].isObject())
        {
            find_object(jv_obj[name], key, filter, arr);
        }
    }
}

void studio_json::find_by_key(const std::string& json, const std::string& key, const std::string& filter, std::vector<std::string>& arr)
{
    Json::Value root = loadJsonOfString(json);
    find_by_key(root, key, filter, arr);
}

void studio_json::find_by_key(const Json::Value& root, const std::string& key, const std::string& filter, std::vector<std::string>& arr)
{
    if (root.isNull())
    {
        return;
    }
    if (root.isArray())
    {
        find_array(root, key, filter, arr);
    }
    else if (root.isObject())
    {
        find_object(root, key, filter, arr);
    }
}
bool studio_json::check_member_string(const Json::Value& root, const std::string& key, std::string& val)
{
    if (root.isMember(key))
    {
        if (root[key].isString())
        {
            val = root[key].asString();
            return true;
        }
        else
        {
            AO_ERROR_PRINT("字段 {} 不是string类型", key)
        }
    }
    else
    {
        AO_ERROR_PRINT("不存在字段 {}", key)
    }
    return false;
}
bool studio_json::check_member_int(const Json::Value& root, const std::string& key, int& val)
{
    if (root.isMember(key))
    {
        if (root[key].isInt())
        {
            val = root[key].asInt();
            return true;
        }
        else
        {
            AO_ERROR_PRINT("字段 {} 不是int类型", key)
        }
    }
    else
    {
        AO_ERROR_PRINT("不存在字段 {}", key)
    }
    return false;
}
bool studio_json::check_member_double(const Json::Value& root, const std::string& key, double& val)
{
    if (root.isMember(key))
    {
        if (root[key].isDouble())
        {
            val = root[key].asDouble();
            return true;
        }
        else
        {
            AO_ERROR_PRINT("字段 {} 不是double类型", key)
        }
    }
    else
    {
        AO_ERROR_PRINT("不存在字段 {}", key)
    }
    return false;
}
bool studio_json::check_member_bool(const Json::Value& root, const std::string& key, bool& val)
{
    if (root.isMember(key))
    {
        if (root[key].isBool())
        {
            val = root[key].asBool();
            return true;
        }
        {
            AO_ERROR_PRINT("字段 {} 不是bool类型", key)
        }
    }
    else
    {
        AO_ERROR_PRINT("不存在字段 {}", key)
    }
    return false;
}
bool studio_json::check_member_array(const Json::Value& root, const std::string& key, Json::Value& jv_arr)
{
    if (root.isMember(key))
    {
        if (root[key].isArray())
        {
            jv_arr = root[key];
            return true;
        }
        else
        {
            AO_ERROR_PRINT("字段 {} 不是数组类型", key)
        }
    }
    else
    {
        AO_ERROR_PRINT("不存在字段 {}", key)
    }
    return false;
}
bool studio_json::check_member_object(const Json::Value& root, const std::string& key, Json::Value& jv_obj)
{
    if (root.isMember(key))
    {
        if (root[key].isObject())
        {
            jv_obj = root[key];
            return true;
        }
        else
        {
            AO_ERROR_PRINT("字段 {} 不是数组类型", key)
        }
    }
    else
    {
        AO_ERROR_PRINT("不存在字段 {}", key)
    }
    return false;
}
