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
    request.setUrl(url);
    return *this;
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

RequestBuilder& RequestBuilder::header(Header *header) {
    request.setHeader(header);
    return *this;
}

Request& RequestBuilder::build() {
    return request;
}

}