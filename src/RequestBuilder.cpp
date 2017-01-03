/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "../include/RequestBuilder.h"

namespace CXXUrl {

RequestBuilder::RequestBuilder() {

}

RequestBuilder::~RequestBuilder() {

}

RequestBuilder& RequestBuilder::url(string url) {
    _url = url;
    return *this;
}

RequestBuilder& RequestBuilder::query(string key, string value) {
    queryMap[key] = value;
    return *this;
}

string RequestBuilder::generateRealUrl() {
    string realUrl = _url;
    string queryStr = "";
    map<string, string>::iterator it;
    for (it = queryMap.begin(); it != queryMap.end(); it++) {
        queryStr += "&" + it->first + "=" + it->second;
    }
    if (_url.find('?') != string::npos) {
        realUrl += queryStr;
    } else {
        if (queryStr != "") {
            realUrl += "?" + queryStr.substr(1);
        }
    }
    return realUrl;
}

RequestBuilder& RequestBuilder::followLocation(bool followLocation) {
    request.setFollowLocation(followLocation);
    return *this;
}

RequestBuilder& RequestBuilder::form(Form *form) {
    request.setForm(form);
    return *this;
}

RequestBuilder& RequestBuilder::contentOutput(ostream *stream) {
    request.setContentOutput(stream);
    return *this;
}

RequestBuilder& RequestBuilder::headerOutput(ostream *stream) {
    request.setHeaderOutput(stream);
    return *this;
}

RequestBuilder& RequestBuilder::maxRedirs(int maxRedirs) {
    request.setMaxRedirs(maxRedirs);
    return *this;
}

RequestBuilder& RequestBuilder::userAgent(string userAgent) {
    request.setUserAgent(userAgent);
    return *this;
}

RequestBuilder& RequestBuilder::referer(string referer) {
    request.setReferer(referer);
    return *this;
}

Request& RequestBuilder::build() {
    request.setUrl(generateRealUrl());
    return request;
}

}