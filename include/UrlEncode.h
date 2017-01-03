/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_URLENCODE_H
#define CXXURL_URLENCODE_H

#include <assert.h>
#include <string>

namespace CXXUrl {

class UrlEncode {

    protected:
        static inline unsigned char ToHex(unsigned char x);
        static inline unsigned char FromHex(unsigned char x);

    public:
        static std::string encode(const std::string& str);
        static std::string decode(const std::string& str);

};

}


#endif //CXXURL_URLENCODE_H
