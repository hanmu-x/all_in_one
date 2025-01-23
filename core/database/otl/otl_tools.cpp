

#include "otl_tools.h"
#include <time/studio_posix_time.h>

//otl studio_db_tools::conn_opt_from_json(const Json::Value &root)
//{
//    otl ret;
//    conn_opt_from_json(root, ret);
//    return ret;
//}

otl_datetime studio_db_tools::otl_time_from_string(const std::string &str)
{
    otl_datetime odt;
    studio_posix_time spt;
    spt.from_string(str);
    odt.year = spt.year();
    odt.month = spt.month();
    odt.day = spt.day();
    odt.hour = spt.hour();
    odt.minute = spt.minute();
    odt.second = spt.second();
    odt.fraction = 0;
    return odt;
}

std::string studio_db_toolsotl_time_to_string(const otl_datetime &tm)
{
    char datetime_buff[32] = {};
    sprintf(datetime_buff, "%04d-%02d-%02d %02d:%02d:%02d", tm.year, tm.month, tm.day, tm.hour, tm.minute, tm.second);

    return datetime_buff;
}


//otl studio_db_toolsconn_opt_from_json(const std::string &json_str)
//{
//    otl ret_opt;
//    Json::Reader reader;
//    Json::Value root;
//    if (reader.parse(json_str, root))
//    {
//        ret_opt = studio_db_tools::conn_opt_from_json(root);
//    }
//    return ret_opt;
//}
//
//bool studio_db_tools::conn_opt_from_json(const std::string &str, otl &ret)
//{
//    Json::Value jv_root;
//    if((jv_root = silly_jsonpp::loads(str)).isNull())
//    {
//        return false;
//    }
//    return conn_opt_from_json(jv_root, ret);
//}
//bool studio_db_tools::conn_opt_from_json(const Json::Value &root, otl &ret)
//{
//    bool status = false;
//    silly_jsonpp::check_member_string(root, OPT_STR_DSN, ret.m_dsn);
//    if (ret.m_dsn.empty())  // 非DSN方式
//    {
//        // 检查类型
//        std::string type_str;
//        if (!silly_jsonpp::check_member_string(root, OPT_STR_TYPE, type_str))
//        {
//            ret.m_err = "指定链接类型";
//            return status;
//        }
//        ret.m_type = str_to_db_type(type_str);
//        if (enum_database_type::dbINVALID == ret.m_type)
//        {
//            ret.m_err = silly_format::format("不支持的数据库类型 (Unsupported database type): {}.", type_str);
//            return status;
//        }
//        if (enum_database_type::dbKingB8 == ret.m_type)
//        {
//            ret.m_err = "人大金仓请使用DSN方式(Please set DSN when using Kingbase).";
//            // SLOG_ERROR("达梦和人大金仓请使用DSN方式(Please set DSN when using Dameng or Kingbase).");
//            return status;
//        }
//
//        if (!silly_jsonpp::check_member_string(root, OPT_STR_IP, ret.m_ip))
//        {
//            ret.m_err = "未指定IP";
//            return status;
//        }
//        if (!silly_jsonpp::check_member_string(root, OPT_STR_DRIVER, ret.m_driver))
//        {
//            ret.m_err = "未指定驱动";
//            return status;
//        }
//
//        // 端口
//        if (root.isMember(OPT_STR_PORT))
//        {
//            if (root[OPT_STR_PORT].isInt())
//            {
//                ret.m_port = root[OPT_STR_PORT].asInt();
//            }
//            else if (root[OPT_STR_PORT].isString())
//            {
//                ret.m_port = std::stoi(root[OPT_STR_PORT].asString());
//            }
//        }
//        else
//        {
//            switch (ret.m_type)
//            {
//                case enum_database_type::dbSQLSERVER:
//                    ret.m_port = 1433;
//                    break;
//                case enum_database_type::dbMYSQL:
//                    ret.m_port = 3306;
//                    break;
//                case enum_database_type::dbORACLE:
//                    ret.m_port = 1521;
//                    break;
//                case enum_database_type::dbPG:
//                    ret.m_port = 5432;
//                    break;
//                case enum_database_type::dbDM8:
//                    ret.m_port = 5236;
//                    break;
//                default:
//                    break;
//            }
//        }
//
//        if (!silly_jsonpp::check_member_string(root, OPT_STR_SCHEMA, ret.m_schema) && (enum_database_type::dbDM8 != ret.m_type))
//        {
//            ret.m_err = "未指定数据库";
//            return status;
//        }
//    }
//    if (!silly_jsonpp::check_member_string(root, OPT_STR_USER, ret.m_user))
//    {
//        ret.m_err = "未指定用户名";
//        return status;
//    }
//    if (!silly_jsonpp::check_member_string(root, OPT_STR_PASSWORD, ret.m_password))
//    {
//        ret.m_err = "未指定密码";
//        return status;
//    }
//    silly_jsonpp::check_member_bool(root, OPT_STR_VERBOSE, ret.m_verbose);
//
//    return true;
//}
