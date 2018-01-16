/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_FORM_H
#define CXXURL_FORM_H

#include "UrlEncode.h"

namespace CXXUrl {

class Form {

    public:
        enum FORM_TYPE{
            SIMPLE = 0,
            MULTIPART,
            RAW
        };

    public:
        explicit Form(FORM_TYPE type);

    public:
        FORM_TYPE type;

};

}


#endif //CXXURL_FORM_H
