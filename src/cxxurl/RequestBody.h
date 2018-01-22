/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_FORM_H
#define CXXURL_FORM_H

#include "UrlEncoder.h"

namespace CXXUrl {


class RequestBody {

    public:
        enum REQUEST_BODY_TYPE{
            X_WWW_FORM_URLENCODED = 0,
            MULTIPART_FORM_DATA,
            RAW_REQUEST_BODY
        };

    public:
        explicit RequestBody(REQUEST_BODY_TYPE type) : m_Type(type) { }

    public:
        REQUEST_BODY_TYPE m_Type;

};

}


#endif //CXXURL_FORM_H
