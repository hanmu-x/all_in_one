
#include "studio_encode.h"

#ifdef _WIN32

bool studio_char_conv::WcharToChar(const wchar_t* wideStr, std::string& str)
{
    // 获取转换后的多字节字符所需的缓冲区大小
    str.clear();
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
    if (bufferSize == 0)
    {
        std::cerr << "Error in WideCharToMultiByte: " << GetLastError() << std::endl;
        return false;
    }

    // 为多字节字符分配缓冲区
    char* multiByteStr = new char[bufferSize];

    // 执行转换
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, multiByteStr, bufferSize, NULL, NULL);
    str.assign(multiByteStr, bufferSize - 1);

    // 清理资源
    delete[] multiByteStr;
    return true;
}

bool studio_char_conv::CharToWchar(const char* multiByteStr, std::wstring& wstr)
{
    // 获取转换后的宽字符所需的缓冲区大小
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, multiByteStr, -1, NULL, 0);
    if (bufferSize == 0)
    {
        std::cout << "Error in MultiByteToWideChar: " << GetLastError() << std::endl;
        return false;
    }

    // 为宽字符分配缓冲区
    wchar_t* wideStr = new wchar_t[bufferSize];

    // 执行转换
    MultiByteToWideChar(CP_UTF8, 0, multiByteStr, -1, wideStr, bufferSize);
    wstr.assign(wideStr, bufferSize - 1);

    //// 检验
    // std::cout << "src: " << multiByteStr << std::endl; // cout
    // std::wcout << "dst: " << wstr << std::endl;        // wcout

    // 清理资源
    delete[] wideStr;

    return true;
}

bool studio_char_conv::CharToWchar(const char* multiByteStr, wchar_t*& wideStr)
{
    // 获取转换后的宽字符所需的缓冲区大小
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, multiByteStr, -1, NULL, 0);
    if (bufferSize == 0)
    {
        std::cerr << "Error in MultiByteToWideChar: " << GetLastError() << std::endl;
        return false;
    }

    // 为宽字符分配缓冲区
    wideStr = new wchar_t[bufferSize - 1];

    // 执行转换
    MultiByteToWideChar(CP_UTF8, 0, multiByteStr, -1, wideStr, bufferSize - 1);

    std::wstring wstr(wideStr);
    // 检验
    std::cout << "src: " << multiByteStr << std::endl;
    std::wcout << L"dst: " << wideStr << std::endl;

    //// 清理资源
    // delete[] wideStr;

    return true;
}

#endif  // _WIN32
