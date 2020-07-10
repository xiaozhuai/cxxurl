/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_REQUEST_H
#define CXXURL_REQUEST_H

#include <curl/curl.h>
#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
#include "Version.h"
#include "RequestBody.h"
#include "SimpleForm.h"
#include "MultipartForm.h"
#include "RawRequestBody.h"
#include "RequestHeader.h"
#include "StringUtils.h"


namespace CXXUrl {

#define DEFINE_PROP_GETTER_SETTER(type, prop) \
    protected: \
        type m_##prop; \
    public: \
        void set##prop(type val){ m_##prop = val; } \
        type get##prop() const { return m_##prop; }

#define DEFINE_MAP_PUSHER_GETTER(type1, type2, prop) \
    protected: \
        std::map<type1, type2> m_##prop; \
    public: \
        void set##prop(type1 key, type2 val){ m_##prop[key] = val; } \
        type2 get##prop(type1 key) const { return m_##prop.at(key); }

#define DEFINE_METHOD(func_name, method) ExecResult func_name(){ return exec(method); }

#define SET_CURL_OPT(opt,value) curl_easy_setopt(m_Curl,(CURLoption)(opt),(value))

class ExecResult {
public:
    ExecResult()
            : ExecResult(CURLE_GOT_NOTHING, 0) {

    }

    /**
     *
     * @param curl_code CURL code.
     * @param http_code HTTP Code related to the result.
     */
    ExecResult(CURLcode curl_code, long http_code)
            : m_Code(curl_code), m_HTTPCode(http_code) {

    }

    explicit operator bool() const {
        return getCode() == CURLE_OK;
    }

    DEFINE_PROP_GETTER_SETTER(CURLcode, Code)

    DEFINE_PROP_GETTER_SETTER(long, HTTPCode)
};

class Request {
    public:
        Request() :
                m_Curl(nullptr),
                m_FollowLocation(true),
                m_ContentOutput(nullptr),
                m_HeaderOutput(nullptr),
                m_MaxRedirs(-1),
                m_RequestBody(nullptr),
                m_RequestHeader(nullptr),
                m_Timeout(0L),
                m_VerifySSL(false),
                m_NoBody(false),
                m_Verbose(false) {
            m_UserAgent = "CXXUrl/" + CXX_URL_VERSION + " " + curl_version();
        }
        ~Request() = default;

    protected:
        CURL* m_Curl;

    protected:
        static size_t writeContent(char* buffer, size_t size, size_t count, void* stream);
        static size_t writeHeader(char* buffer, size_t size, size_t count, void* stream);

        DEFINE_PROP_GETTER_SETTER(std::string, Url)
        DEFINE_PROP_GETTER_SETTER(bool, FollowLocation)
        DEFINE_PROP_GETTER_SETTER(int, MaxRedirs)
        DEFINE_PROP_GETTER_SETTER(RequestBody*, RequestBody)
        DEFINE_PROP_GETTER_SETTER(std::string, UserAgent)
        DEFINE_PROP_GETTER_SETTER(std::string, Referer)
        DEFINE_PROP_GETTER_SETTER(std::string, ContentType)
        DEFINE_PROP_GETTER_SETTER(RequestHeader*, RequestHeader)
        DEFINE_PROP_GETTER_SETTER(long, Timeout)
        DEFINE_PROP_GETTER_SETTER(std::string, Proxy)
        DEFINE_PROP_GETTER_SETTER(std::string, CookieImportFile)
        DEFINE_PROP_GETTER_SETTER(std::string, CookieExportFile)
        DEFINE_PROP_GETTER_SETTER(bool, VerifySSL)
        DEFINE_PROP_GETTER_SETTER(std::string, Cacert)
        DEFINE_PROP_GETTER_SETTER(bool, NoBody)
        DEFINE_PROP_GETTER_SETTER(bool, Verbose)
        DEFINE_PROP_GETTER_SETTER(std::ostream*, ContentOutput)
        DEFINE_PROP_GETTER_SETTER(std::ostream*, HeaderOutput)
        DEFINE_MAP_PUSHER_GETTER(int, long, CurlOptionLong)
        DEFINE_MAP_PUSHER_GETTER(int, std::string, CurlOptionString)

    public:
        DEFINE_METHOD(get,      "GET")
        DEFINE_METHOD(post,     "POST")
        DEFINE_METHOD(put,      "PUT")
        DEFINE_METHOD(head,     "HEAD")
        DEFINE_METHOD(options,  "OPTIONS")
        DEFINE_METHOD(del,      "DELETE")
        DEFINE_METHOD(connect,  "CONNECT")

        ExecResult exec( std::string method="") {
            m_Curl = curl_easy_init();

            SET_CURL_OPT(CURLOPT_VERBOSE, m_Verbose);

            SET_CURL_OPT(CURLOPT_URL, m_Url.c_str());

            method = StringUtils::toupper(method);
            if(m_NoBody || (method == "HEAD"))
                SET_CURL_OPT(CURLOPT_NOBODY, 1);
            if(method!="HEAD")
                SET_CURL_OPT(CURLOPT_CUSTOMREQUEST, method.c_str());

            if (m_RequestBody != nullptr) {
                switch (m_RequestBody->m_Type){
                    case RequestBody::X_WWW_FORM_URLENCODED: {
                        auto *simpleForm = (SimpleForm *) m_RequestBody;
                        SET_CURL_OPT(CURLOPT_POSTFIELDS, simpleForm->getData());
                        SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, simpleForm->length());
                        break;
                    }
                    case RequestBody::MULTIPART_FORM_DATA: {
                        auto *multipartForm = (MultipartForm *) m_RequestBody;
                        SET_CURL_OPT(CURLOPT_HTTPPOST, multipartForm->getData());
                        break;
                    }
                    case RequestBody::RAW_REQUEST_BODY: {
                        auto *rawForm = (RawRequestBody *) m_RequestBody;
                        SET_CURL_OPT(CURLOPT_POSTFIELDS, rawForm->getData());
                        SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, rawForm->length());
                        break;
                    }
                    default:
                        std::cerr << "form type unknown" << std::endl << std::flush;
                        break;
                }
            }



            SET_CURL_OPT(CURLOPT_FOLLOWLOCATION, m_FollowLocation);
            SET_CURL_OPT(CURLOPT_USERAGENT, m_UserAgent.c_str());

            if(!m_Referer.empty()){
                SET_CURL_OPT(CURLOPT_REFERER, m_Referer.c_str());
            }

            bool need_reset_header = false;
            if(!m_ContentType.empty()){
                if(m_RequestHeader==nullptr){
                    m_RequestHeader = new RequestHeader();
                    need_reset_header = true;
                }
                m_RequestHeader->add("Content-Type", m_ContentType);
            }

            if(m_RequestHeader!=nullptr){
                SET_CURL_OPT(CURLOPT_HTTPHEADER, m_RequestHeader->getHeaders());
            }

            if(m_Timeout>0L){
                SET_CURL_OPT(CURLOPT_TIMEOUT_MS, m_Timeout);
            }


            if(!m_Proxy.empty()){
                SET_CURL_OPT(CURLOPT_PROXY, m_Proxy.c_str());
            }else{
                char* envProxy = getenv("http_proxy");
                if(envProxy==nullptr) envProxy = getenv("HTTP_PROXY");
                if(envProxy!=nullptr) SET_CURL_OPT(CURLOPT_PROXY, envProxy);
            }

            if(!m_CookieImportFile.empty()){
                SET_CURL_OPT(CURLOPT_COOKIEFILE, m_CookieImportFile.c_str());
            }
            if(!m_CookieExportFile.empty()){
                SET_CURL_OPT(CURLOPT_COOKIEJAR, m_CookieExportFile.c_str());
            }

            if(m_VerifySSL && !m_Cacert.empty()){
                SET_CURL_OPT(CURLOPT_SSL_VERIFYPEER, 1);
                SET_CURL_OPT(CURLOPT_SSL_VERIFYHOST, 1);
                SET_CURL_OPT(CURLOPT_CAINFO, m_Cacert.c_str());
            }else{
                SET_CURL_OPT(CURLOPT_SSL_VERIFYPEER, 0);
                SET_CURL_OPT(CURLOPT_SSL_VERIFYHOST, 0);
            }

            if (m_MaxRedirs != -1)
                SET_CURL_OPT(CURLOPT_MAXREDIRS, m_MaxRedirs);

            SET_CURL_OPT(CURLOPT_WRITEFUNCTION, writeContent);
            SET_CURL_OPT(CURLOPT_WRITEDATA, m_ContentOutput);
            SET_CURL_OPT(CURLOPT_HEADERFUNCTION, writeHeader);
            SET_CURL_OPT(CURLOPT_HEADERDATA, m_HeaderOutput);

            for (auto i : m_CurlOptionLong) {
                SET_CURL_OPT(i.first, i.second);
            }

            for (auto const& i : m_CurlOptionString) {
                SET_CURL_OPT(i.first, i.second.c_str());
            }

            auto const rc = curl_easy_perform(m_Curl);
            long httpCode(0);
            if ( rc == CURLE_OK ) {
              curl_easy_getinfo(m_Curl, CURLINFO_RESPONSE_CODE, &httpCode);
            }
            curl_easy_cleanup(m_Curl);

            if (need_reset_header) {
                delete m_RequestHeader;
                m_RequestHeader = nullptr;
            }
            return ExecResult{rc, httpCode};
        }
};

size_t Request::writeContent(char *buffer, size_t size, size_t count, void *stream) {
    if(stream!= nullptr)
        ((std::ostream *) stream)->write(buffer, size * count);
    return size * count;
}

size_t Request::writeHeader(char *buffer, size_t size, size_t count, void *stream) {
    if(stream!= nullptr)
        ((std::ostream *) stream)->write(buffer, size * count);
    return size * count;
}

}

#endif //CXXURL_REQUEST_H
