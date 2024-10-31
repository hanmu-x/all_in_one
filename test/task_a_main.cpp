

#include "studio_macros.h"
#include "file/studio_dir.h"
#include "time/studio_time.h"
#include "string/studio_str_algo.h"
#include "string/studio_regex.h"
#include "time/studio_timer.h"

int main(int argc, char* argv[])
{
    studio_timer timer;
    std::string dataDir = DEFAULT_AO_DATA_DIR;
    std::string input_txt = dataDir + "/txt/2003003.txt";

    std::ifstream inFile;
    inFile.open(input_txt);
    if (!inFile.is_open())
    {
        std::cout << "Failed to open TXT file." << std::endl;
        return false;
    }

    // 记录当前文件指针位置
    std::streampos originalPos = inFile.tellg();
    std::vector<float> data;
    // 检测文件是否包含元数据头部
    std::string firstLine;
    while (std::getline(inFile, firstLine))
    {
        std::cout << "firstLine: " << firstLine << std::endl;
        std::vector<std::string> onceLine = studio_str_algo::separate(firstLine, "     ");

        int b = 0;
    }
    inFile.close();


    timer.timed_print();


    return 0;

    //std::string inputDate1 = "2023-07-24 14:30:00";
    //std::string outputDate1 = simple_time::convertTmFormat(inputDate1, simple_time::TM_FORMAT_1, simple_time::TM_FORMAT_2);
    //std::cout << "Converted date 1: " << outputDate1 << std::endl;


    //std::string inputDate2 = "202307241430";
    //std::string outputDate2 = simple_time::convertTmFormat(inputDate2, simple_time::TM_FORMAT_4, simple_time::TM_FORMAT_5);
    //std::cout << "Converted date 2: " << outputDate2 << std::endl;
    //// Output: Converted date 2: 2023-07-24 14:30


    //std::string inputDate3 = "2023-07-24 14:00";
    //std::string outputDate3 = simple_time::convertTmFormat(inputDate3, simple_time::TM_FORMAT_8, simple_time::TM_FORMAT_6);
    //std::cout << "Converted date 3: " << outputDate3 << std::endl;
    //// Output: Converted date 3: 20230724


    //std::string inputDate4 = "2023-07-24-14-30-00";
    //std::string outputDate4 = simple_time::convertTmFormat(inputDate4, simple_time::TM_FORMAT_7, simple_time::TM_FORMAT_3);
    //std::cout << "Converted date 4: " << outputDate4 << std::endl;
    //// Output: Converted date 4: 14


    //return 0;


    //std::string path = "D:/1_wangyingjie/readfile/daily snow depth_AMSRE_full/2007_tif";
    //std::vector<std::string> all_path = studio_file::collectFileOrDirEntries(path);

    //std::string tm = "2024-07-15 10:11";
    //boost::posix_time::ptime boostTm = simple_time::TimeFromString(tm);

    //std::string format_tm = simple_time::TimeToFormatString(boostTm);

    //return 0;
}



