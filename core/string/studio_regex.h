
#ifndef STUDIO_REGEX_H
#define STUDIO_REGEX_H

#include "studio_macros.h"


bool matchRegex(const std::string& regexPattern, const std::string& text)
{
    std::regex pattern(regexPattern);
    bool result = std::regex_match(text, pattern);
    return result;
}

bool isValidChinesePhoneNumber(const std::string& phoneNumber)
{
    // 匹配中国手机号码的正则表达式
    //std::regex pattern("^(?:(?:\\+|00)86)?1[3-9]\\d{9}$");
    std::string chinesePhoneNumberPattern = R"(^(?:(?:\+|00)86)?1[3-9]\d{9}$)";
    std::regex pattern(chinesePhoneNumberPattern);
    bool result = std::regex_match(phoneNumber, pattern);
    return result;
}


bool isValidQQ(const std::string& QQ)
{
    // 匹配中国手机号码的正则表达式
    std::string ppMate = R"(^[1-9]{1}[0-9]{4,14}$)";
    std::regex pattern(ppMate);
    bool result = std::regex_match(QQ, pattern);
    return result;
}

bool isValidEmail(const std::string& email)
{
    std::string emailPattern = R"(^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$)";
    std::regex pattern(emailPattern);
    bool result = std::regex_match(email, pattern);
    return result;
}





#endif // STUDIO_REGEX_H