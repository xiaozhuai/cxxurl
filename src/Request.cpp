/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "../include/Request.h"

namespace CXXUrl {

Request::Request() :
        followLocation(true),
        contentOutput(NULL),
        headerOutput(NULL),
        maxRedirs(-1),
        form(NULL),
        referer(""),
        header(NULL),
        timeout(0L),
        proxy("") {

    userAgent = string("") + "CXXUrl/" + CXX_URL_VERSION + " " + curl_version();
}

Request::~Request() {

}

size_t Request::writeContent(char *buffer, size_t size, size_t count, void *stream) {
    ((ostream *) stream)->write(buffer, size * count);
//    printf("data recieved: %d,%s\n", size*count, buffer);
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

CURLcode Request::get() {
    return exec(GET);
}

CURLcode Request::post() {
    return exec(POST);
}

CURLcode Request::exec(METHOD_TYPE method) {
    curl = curl_easy_init();

    SET_CURL_OPT(CURLOPT_URL, url.c_str());
//    SET_CURL_OPT(CURLOPT_VERBOSE, 1);


    switch (method){
        case GET: {
            SET_CURL_OPT(CURLOPT_HTTPGET, 1);
            break;
        }
        case POST: {
            SET_CURL_OPT(CURLOPT_POST, 1);
            if (form == NULL) {
                SET_CURL_OPT(CURLOPT_POSTFIELDS, "");
                SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, 0);
            } else {
                switch (form->type){
                    case Form::SIMPLE: {
                        SimpleForm *simpleForm = (SimpleForm *) form;
                        SET_CURL_OPT(CURLOPT_POSTFIELDS, simpleForm->getData());
                        SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, simpleForm->length());
                        break;
                    }
                    case Form::MULTIPART: {
                        MultipartForm *multipartForm = (MultipartForm *) form;
                        SET_CURL_OPT(CURLOPT_HTTPPOST, multipartForm->getData());
                        break;
                    }
                    case Form::RAW: {
                        RawForm *rawForm = (RawForm *) form;
                        SET_CURL_OPT(CURLOPT_POSTFIELDS, rawForm->getData());
                        SET_CURL_OPT(CURLOPT_POSTFIELDSIZE, rawForm->length());
                        break;
                    }
                    default:
                        cerr << "form type unknown" << endl;
                        break;
                }
            }
            break;
        }
        default:
            cerr << "unknown method" << endl;
    }



    SET_CURL_OPT(CURLOPT_FOLLOWLOCATION, followLocation);
    SET_CURL_OPT(CURLOPT_USERAGENT, userAgent.c_str());

    if(referer!=""){
        SET_CURL_OPT(CURLOPT_REFERER, referer.c_str());
    }

    if(header!=NULL){
        SET_CURL_OPT(CURLOPT_HTTPHEADER, header->getHeaders());
    }

    if(timeout>0L){
        SET_CURL_OPT(CURLOPT_TIMEOUT_MS, timeout);
    }


    if(proxy.empty()) proxy = getenv("http_proxy");
    if(proxy.empty()) proxy = getenv("HTTP_PROXY");
    if(!proxy.empty()){
        SET_CURL_OPT(CURLOPT_PROXY, proxy.c_str());
    }

    if (maxRedirs != -1)
        SET_CURL_OPT(CURLOPT_MAXREDIRS, maxRedirs);

    if (contentOutput != NULL) {
        SET_CURL_OPT(CURLOPT_WRITEFUNCTION, writeContent);
        SET_CURL_OPT(CURLOPT_WRITEDATA, contentOutput);
    }
    if (headerOutput != NULL) {
        SET_CURL_OPT(CURLOPT_HEADERFUNCTION, writeHeader);
        SET_CURL_OPT(CURLOPT_HEADERDATA, headerOutput);
    }




    CURLcode res;
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}


}