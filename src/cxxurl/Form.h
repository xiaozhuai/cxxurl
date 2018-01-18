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
        explicit Form(FORM_TYPE type) : m_Type(type) { }

    public:
        FORM_TYPE m_Type;

};

}


#endif //CXXURL_FORM_H
