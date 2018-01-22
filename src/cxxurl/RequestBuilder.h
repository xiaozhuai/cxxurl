/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_REQUESTBUILDER_H
#define CXXURL_REQUESTBUILDER_H

#include <string>
#include <map>
#include "Request.h"

namespace CXXUrl {

#define DEFINE_CHAIN_METHOD_1_ARGS(type, method, setter) \
        RequestBuilder& method(type val) { \
            request.setter(val); \
            return *this; \
        }

#define DEFINE_CHAIN_METHOD_2_ARGS(type1, type2, method, setter) \
        RequestBuilder& method(type1 val1, type2 val2) { \
            request.setter(val1, val2); \
            return *this; \
        }

class RequestBuilder {

    protected:
        Request request;

    public:
        RequestBuilder() = default;
        ~RequestBuilder() = default;

        Request build() { return request; }

        DEFINE_CHAIN_METHOD_1_ARGS(std::string, url, setUrl)
        DEFINE_CHAIN_METHOD_1_ARGS(bool, followLocation, setFollowLocation)
        DEFINE_CHAIN_METHOD_1_ARGS(std::ostream*, contentOutput, setContentOutput)
        DEFINE_CHAIN_METHOD_1_ARGS(std::ostream*, headerOutput, setHeaderOutput)
        DEFINE_CHAIN_METHOD_1_ARGS(int, maxRedirs, setMaxRedirs)
        DEFINE_CHAIN_METHOD_1_ARGS(RequestBody*, requestBody, setRequestBody)
        DEFINE_CHAIN_METHOD_1_ARGS(std::string, userAgent, setUserAgent)
        DEFINE_CHAIN_METHOD_1_ARGS(std::string, referer, setReferer)
        DEFINE_CHAIN_METHOD_1_ARGS(std::string, contentType, setContentType)
        DEFINE_CHAIN_METHOD_1_ARGS(RequestHeader*, requestHeader, setRequestHeader)
        DEFINE_CHAIN_METHOD_1_ARGS(long, timeout, setTimeout)
        DEFINE_CHAIN_METHOD_1_ARGS(std::string, proxy, setProxy)
        DEFINE_CHAIN_METHOD_1_ARGS(std::string, importCookie, setCookieImportFile)
        DEFINE_CHAIN_METHOD_1_ARGS(std::string, exportCookie, setCookieExportFile)
        DEFINE_CHAIN_METHOD_1_ARGS(bool, verifySSL, setVerifySSL)
        DEFINE_CHAIN_METHOD_1_ARGS(std::string, cacert, setCacert)
        DEFINE_CHAIN_METHOD_1_ARGS(bool, noBody, setNoBody)
        DEFINE_CHAIN_METHOD_1_ARGS(bool, verbose, setVerbose)
        DEFINE_CHAIN_METHOD_2_ARGS(CURLoption, long, curlOptionLong, setCurlOptionLong);
        DEFINE_CHAIN_METHOD_2_ARGS(CURLoption, std::string, curlOptionString, setCurlOptionString);
};

}

#endif //CXXURL_REQUESTBUILDER_H
