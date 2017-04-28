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
#include <stdlib.h>
#include "Version.h"
#include "Form.h"
#include "SimpleForm.h"
#include "MultipartForm.h"
#include "RawForm.h"
#include "Header.h"

#define SET_CURL_OPT(opt,value)          curl_easy_setopt((this->curl),(opt),(value))

namespace CXXUrl {

using namespace std;

class Request {

    public:
        enum METHOD_TYPE{
            NONE = 0,
            GET = 1,
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

    protected:
        static size_t writeContent(char* buffer, size_t size, size_t count, void* stream);
        static size_t writeHeader(char* buffer, size_t size, size_t count, void* stream);

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
        Header* header;
        void setHeader(Header* header);
        Header* getHeader();

    public:
        long timeout;
        void setTimeout(long milliSeconds);
        long getTimeout();

    public:
        string proxy;
        void setProxy(string proxy);
        string getProxy();

    public:
        string cookieImportFile;
        string cookieExportFile;
        void setCookieImportFile(string filePath);
        void setCookieExportFile(string filePath);
        string getCookieImportFile();
        string getCookieExportFile();

    public:
        bool verifySSL;
        void setVerifySSL(bool enable);
        bool getVerifySSL();
        string cacert;
        void setCacert(string pemFile);
        string getCacert();

    public:
        bool noBody;
        void setNoBody(bool noBody);
        bool getNoBody();

    public:
        bool verbose;
        void setVerbose(bool enable);
        bool getVerbose();

    public:
        void setCurlOptionLong(CURLoption option, long value);
        void setCurlOptionString(CURLoption option, string value);

    public:
        map<CURLoption, long>   longOptionMap;
        map<CURLoption, string> stringOptionMap;


    public:
        CURLcode get();
        CURLcode post();
        CURLcode exec(METHOD_TYPE method = NONE);

};

}

#endif //CXXURL_REQUEST_H
