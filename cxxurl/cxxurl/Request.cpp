/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "Request.h"

#define SET_CURL_OPT(opt,value)          curl_easy_setopt((this->curl),(CURLoption)(opt),(value))

namespace CXXUrl {

Request::Request() :
        followLocation(true),
        contentOutput(nullptr),
        headerOutput(nullptr),
        maxRedirs(-1),
        form(nullptr),
        header(nullptr),
        timeout(0L),
        verifySSL(false),
        noBody(false),
        verbose(false) {
    string cxxurl_version = to_string(CXX_URL_VERSION);
    cxxurl_version.erase(cxxurl_version.find_last_not_of("0") + 1);
    userAgent = string("") + "CXXUrl/" + cxxurl_version + " " + curl_version();
}

Request::~Request() {

}

size_t Request::writeContent(char *buffer, size_t size, size_t count, void *stream) {
    ((ostream *) stream)->write(buffer, size * count);
    return size * count;
}

size_t Request::writeHeader(char *buffer, size_t size, size_t count, void *stream) {
    ((ostream *) stream)->write(buffer, size * count);
    return size * count;
}

void Request::setContentOutput(ostream *stream) {
    contentOutput = stream;
}

void Request::setHeaderOutput(ostream *stream) {
    headerOutput = stream;
}

ostream *Request::getContentOutput() {
    return contentOutput;
}

ostream *Request::getHeaderOutput() {
    return headerOutput;
}

void Request::setUrl(string url) {
    this->url = url;
}

string Request::getUrl() {
    return url;
}

void Request::setFollowLocation(bool followLocation) {
    this->followLocation = followLocation;
}

bool Request::getFollowLocation() {
    return followLocation;
}

void Request::setMaxRedirs(int maxRedirs) {
    this->maxRedirs = maxRedirs;
}

int Request::getMaxRedirs() {
    return maxRedirs;
}

void Request::setForm(Form *form) {
    this->form = form;
}

Form *Request::getForm() {
    return form;
}

void Request::setUserAgent(string userAgent) {
    this->userAgent = userAgent;
}

string Request::getUserAgent() {
    return userAgent;
}

void Request::setReferer(string referer) {
    this->referer = referer;
}

string Request::getReferer() {
    return referer;
}

void Request::setContentType(string contentType) {
    this->contentType = contentType;
}

string Request::getContentType() {
    return contentType;
}

void Request::setHeader(Header *header) {
    this->header = header;
}

Header* Request::getHeader() {
    return header;
}

void Request::setTimeout(long milliSeconds) {
    timeout = milliSeconds;
}

long Request::getTimeout() {
    return timeout;
}

void Request::setProxy(string proxy) {
    this->proxy = proxy;
}

string Request::getProxy() {
    return proxy;
}

void Request::setCookieImportFile(string filePath) {
    cookieImportFile = filePath;
}

void Request::setCookieExportFile(string filePath) {
    cookieExportFile = filePath;
}

string Request::getCookieImportFile() {
    return cookieImportFile;
}

string Request::getCookieExportFile() {
    return cookieExportFile;
}

void Request::setVerifySSL(bool enable) {
    this->verifySSL = enable;
}

bool Request::getVerifySSL() {
    return verifySSL;
}

void Request::setCacert(string pemFile) {
    this->cacert = pemFile;
}

string Request::getCacert() {
    return cacert;
}

void Request::setNoBody(bool noBody) {
    this->noBody = noBody;
}

bool Request::getNoBody() {
    return noBody;
}

void Request::setVerbose(bool enable) {
    verbose = enable;
}

bool Request::getVerbose() {
    return verbose;
}

void Request::setCurlOptionLong(CURLoption option, long value) {
    longOptionMap[option] = value;
}

void Request::setCurlOptionString(CURLoption option, string value) {
    stringOptionMap[option] = value;
}

CURLcode Request::get() {
    return exec(GET);
}

CURLcode Request::post() {
    return exec(POST);
}

CURLcode Request::exec(METHOD_TYPE method) {
    curl = curl_easy_init();

    SET_CURL_OPT(CURLOPT_VERBOSE, verbose);

    SET_CURL_OPT(CURLOPT_URL, url.c_str());

    switch (method){
        case GET: {
            SET_CURL_OPT(CURLOPT_HTTPGET, 1);
            break;
        }
        case POST: {
            SET_CURL_OPT(CURLOPT_POST, 1);
            if (form == nullptr) {
                SET_CURL_OPT(CURLOPT_POSTFIELDS, "");
                SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, 0);
            } else {
                switch (form->type){
                    case Form::SIMPLE: {
                        auto *simpleForm = (SimpleForm *) form;
                        SET_CURL_OPT(CURLOPT_POSTFIELDS, simpleForm->getData());
                        SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, simpleForm->length());
                        break;
                    }
                    case Form::MULTIPART: {
                        auto *multipartForm = (MultipartForm *) form;
                        SET_CURL_OPT(CURLOPT_HTTPPOST, multipartForm->getData());
                        break;
                    }
                    case Form::RAW: {
                        auto *rawForm = (RawForm *) form;
                        SET_CURL_OPT(CURLOPT_POSTFIELDS, rawForm->getData());
                        SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, rawForm->length());
                        break;
                    }
                    default:
                        cerr << "form type unknown" << endl << flush;
                        break;
                }
            }
            break;
        }
        default:
            break;
    }



    SET_CURL_OPT(CURLOPT_FOLLOWLOCATION, followLocation);
    SET_CURL_OPT(CURLOPT_USERAGENT, userAgent.c_str());
    SET_CURL_OPT(CURLOPT_NOBODY, noBody);

    if(!referer.empty()){
        SET_CURL_OPT(CURLOPT_REFERER, referer.c_str());
    }

    if(!contentType.empty()){
        if(header==nullptr){
            Header headerObj;
            header = &headerObj;
        }
        header->add("Content-Type", contentType);
    }

    if(header!=nullptr){
        SET_CURL_OPT(CURLOPT_HTTPHEADER, header->getHeaders());
    }

    if(timeout>0L){
        SET_CURL_OPT(CURLOPT_TIMEOUT_MS, timeout);
    }


    if(!proxy.empty()){
        SET_CURL_OPT(CURLOPT_PROXY, proxy.c_str());
    }else{
        char* envProxy = getenv("http_proxy");
        if(envProxy==nullptr) envProxy = getenv("HTTP_PROXY");
        if(envProxy!=nullptr) SET_CURL_OPT(CURLOPT_PROXY, envProxy);
    }

    if(!cookieImportFile.empty()){
        SET_CURL_OPT(CURLOPT_COOKIEFILE, cookieImportFile.c_str());
    }
    if(!cookieExportFile.empty()){
        SET_CURL_OPT(CURLOPT_COOKIEJAR, cookieExportFile.c_str());
    }

    if(verifySSL && !cacert.empty()){
        SET_CURL_OPT(CURLOPT_SSL_VERIFYPEER, 1);
        SET_CURL_OPT(CURLOPT_SSL_VERIFYHOST, 1);
        SET_CURL_OPT(CURLOPT_CAINFO, cacert.c_str());
    }else{
        SET_CURL_OPT(CURLOPT_SSL_VERIFYPEER, 0);
        SET_CURL_OPT(CURLOPT_SSL_VERIFYHOST, 0);
    }

    if (maxRedirs != -1)
        SET_CURL_OPT(CURLOPT_MAXREDIRS, maxRedirs);

    if (contentOutput != nullptr) {
        SET_CURL_OPT(CURLOPT_WRITEFUNCTION, writeContent);
        SET_CURL_OPT(CURLOPT_WRITEDATA, contentOutput);
    }
    if (headerOutput != nullptr) {
        SET_CURL_OPT(CURLOPT_HEADERFUNCTION, writeHeader);
        SET_CURL_OPT(CURLOPT_HEADERDATA, headerOutput);
    }

    for (auto i : longOptionMap) {
        SET_CURL_OPT(i.first, i.second);
    }

    for (auto i : stringOptionMap) {
        SET_CURL_OPT(i.first, i.second.c_str());
    }


    CURLcode res;
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}


}