/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_REQUEST_H
#define CXXURL_REQUEST_H

#include <curl/curl.h>
#include <string>
#include <iostream>
#include "version.h"
#include "Form.h"
#include "SimpleForm.h"
#include "MultipartForm.h"
#include "RawForm.h"

#define SET_CURL_OPT(opt,value)          curl_easy_setopt((this->curl),(opt),(value))

namespace CXXUrl {

using namespace std;

class Request {

    public:
        enum METHOD_TYPE{
            GET = 0,
            POST
        };

    public:
        Request();
        ~Request();

    protected:
        CURL* curl;

    public:
        ostream* contentOutput;
        ostream* headerOutput;
        void setContentOutput(ostream* stream);
        void setHeaderOutput(ostream* stream);
        ostream* getContentOutput();
        ostream* getHeaderOutput();

    public:
        string url;
        void setUrl(string url);
        string getUrl();

    public:
        bool followLocation;
        void setFollowLocation(bool followLocation);
        bool getFollowLocation();

    public:
        int maxRedirs;
        void setMaxRedirs(int maxRedirs);
        int getMaxRedirs();

    public:
        Form* form;
        void setForm(Form* form);
        Form* getForm();

    public:
        string userAgent;
        void setUserAgent(string userAgent);
        string getUserAgent();

    public:
        string referer;
        void setReferer(string referer);
        string getReferer();

    public:
        CURLcode get();
        CURLcode post();
        CURLcode exec(METHOD_TYPE method);

    protected:
        static size_t writeContent(char* buffer, size_t size, size_t count, void* stream);
        static size_t writeHeader(char* buffer, size_t size, size_t count, void* stream);
};

}

#endif //CXXURL_REQUEST_H
