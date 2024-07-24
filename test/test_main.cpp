

#include "studio_macros.h"
#include "file/studio_file.h"
#include "time/studio_time.h"

int main(int argc, char* argv[])
{
    std::string path = "D:/1_wangyingjie/readfile/daily snow depth_AMSRE_full/2007_tif";
    std::vector<std::string> all_path = studio_file::collectFileOrDirEntries(path);

    std::string tm = "2024-07-15 10:11";
    boost::posix_time::ptime boostTm = simple_time::TimeFromString(tm);

    std::string format_tm = simple_time::TimeToFormatString(boostTm);

    return 0;
}



