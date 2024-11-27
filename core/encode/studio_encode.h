
#ifndef STUDIO_ENCODE_H
#define STUDIO_ENCODE_H

#include "studio_macros.h"

#ifdef _WIN32
#include <windows.h>

class studio_char_conv
{
  public:
    /// <summary>
    /// 宽字符转窄字符
    /// </summary>
    /// <param name="wideStr"></param>
    /// <param name="str"></param>
    /// <returns></returns>
    static bool WcharToChar(const wchar_t* wideStr, std::string& str);

    /// <summary>
    /// 窄字符转宽字符
    /// </summary>
    /// <param name="multiByteStr"></param>
    /// <param name="wstr"></param>
    /// <returns></returns>
    static bool CharToWchar(const char* multiByteStr, std::wstring& wstr);

    /// <summary>
    /// 宽字符转窄字符
    /// 注意 ：需要手动释放内存, delete[] wideStr;
    /// </summary>
    /// <param name="multiByteStr"></param>
    /// <param name="wideStr">宽字符指针, 需要手动释放 delete[] wideStr</param>
    /// <returns></returns>
    static bool CharToWchar(const char* multiByteStr, wchar_t*& wideStr);
};

#endif // _WIN32

class studio_encode
{
};

#endif  // STUDIO_ENCODE_H
