
#pragma once

#ifndef OTL_TOOLS_H
#define OTL_TOOLS_H

#include "database/otl/studio_otl.h"
#include <json/studio_json.h>


class studio_db_tools
{
  public:
    static otl_datetime otl_time_from_string(const std::string &str);
    static std::string otl_time_to_string(const otl_datetime &tm);

    //static silly::db::otl otl_from_json(const Json::Value &root);
    //static silly::db::otl otl_from_json(const std::string &jstr);

    //static bool otl_from_json(const std::string &str, silly::db::otl &ret);
    //static bool otl_from_json(const Json::Value &root, silly::db::otl &ret);
};




#endif  // OTL_TOOLS_H
