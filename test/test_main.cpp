/*
 * @Author: yingjie_wang 2778809626@qq.com
 * @Date: 2024-07-23 15:43:50
 * @LastEditors: yingjie_wang 2778809626@qq.com
 * @LastEditTime: 2024-07-23 15:53:16
 * @FilePath: /all_in_one/test/test_main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "common_macros.h"
#include "file/common_file.h"
#include "time/common_time.h"

int main(int argc, char* argv[])
{
    std::string path = "D:/1_wangyingjie/readfile/daily snow depth_AMSRE_full/2007_tif";
    std::vector<std::string> all_path = common_file::collectFileOrDirEntries(path);

    std::string tm = "2024-07-15 10:11";
    boost::posix_time::ptime boostTm = simple_time::TimeFromString(tm);

    std::string format_tm = simple_time::TimeToFormatString(boostTm);

    return 0;
}



