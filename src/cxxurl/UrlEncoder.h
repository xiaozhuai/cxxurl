/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_URLENCODE_H
#define CXXURL_URLENCODE_H

#include <cassert>
#include <string>

namespace CXXUrl {

class UrlEncoder {

    protected:
        static inline unsigned char ToHex(unsigned char x);
        static inline unsigned char FromHex(unsigned char x);

    public:
        static std::string encode(const std::string& str);
        static std::string decode(const std::string& str);

};

unsigned char UrlEncoder::ToHex(unsigned char x) {
    return  x > 9 ? x + 55 : x + 48;
}

unsigned char UrlEncoder::FromHex(unsigned char x) {
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}

std::string UrlEncoder::encode(const std::string &str) {
    std::string strTemp;
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}

std::string UrlEncoder::decode(const std::string &str) {
    std::string strTemp;
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high*16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}

}


#endif //CXXURL_URLENCODE_H
