

#include "studio_macros.h"
#include "file/studio_file.h"
#include "time/studio_time.h"

int main(int argc, char* argv[])
{
    
    std::string inputDate1 = "2023-07-24 14:30:00";
    std::string outputDate1 = simple_time::convertTmFormat(inputDate1, simple_time::DATE_FORMAT_1, simple_time::DATE_FORMAT_2);
    std::cout << "Converted date 1: " << outputDate1 << std::endl;


    std::string inputDate2 = "202307241430";
    std::string outputDate2 = simple_time::convertTmFormat(inputDate2, simple_time::DATE_FORMAT_4, simple_time::DATE_FORMAT_5);
    std::cout << "Converted date 2: " << outputDate2 << std::endl;
    // Output: Converted date 2: 2023-07-24 14:30


    std::string inputDate3 = "2023-07-24 14:00";
    std::string outputDate3 = simple_time::convertTmFormat(inputDate3, simple_time::DATE_FORMAT_8, simple_time::DATE_FORMAT_6);
    std::cout << "Converted date 3: " << outputDate3 << std::endl;
    // Output: Converted date 3: 20230724


    std::string inputDate4 = "2023-07-24-14-30-00";
    std::string outputDate4 = simple_time::convertTmFormat(inputDate4, simple_time::DATE_FORMAT_7, simple_time::DATE_FORMAT_3);
    std::cout << "Converted date 4: " << outputDate4 << std::endl;
    // Output: Converted date 4: 14


    return 0;


    std::string path = "D:/1_wangyingjie/readfile/daily snow depth_AMSRE_full/2007_tif";
    std::vector<std::string> all_path = studio_file::collectFileOrDirEntries(path);

    std::string tm = "2024-07-15 10:11";
    boost::posix_time::ptime boostTm = simple_time::TimeFromString(tm);

    std::string format_tm = simple_time::TimeToFormatString(boostTm);

    return 0;
}



