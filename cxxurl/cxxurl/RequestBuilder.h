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

using namespace std;

class RequestBuilder {

    public:
        RequestBuilder &url(string url);

        RequestBuilder &followLocation(bool followLocation);

        RequestBuilder &contentOutput(ostream *stream);

        RequestBuilder &headerOutput(ostream *stream);

        RequestBuilder &maxRedirs(int maxRedirs);

        RequestBuilder &form(Form *form);

        RequestBuilder &userAgent(string userAgent);

        RequestBuilder &referer(string referer);

        RequestBuilder &contentType(string contentType);

        RequestBuilder &header(Header *header);

        RequestBuilder &timeout(long milliSeconds);

        RequestBuilder &proxy(string proxy);

        RequestBuilder &importCookie(string filePath);

        RequestBuilder &exportCookie(string filePath);

        RequestBuilder &verifySSL(bool enable);

        RequestBuilder &cacert(string pemFile);

        RequestBuilder &noBody(bool noBody);

        RequestBuilder &verbose(bool enable);

        RequestBuilder &setCurlOptionLong(CURLoption option, long value);
        RequestBuilder &setCurlOptionString(CURLoption option, string value);

    public:
        Request build();


    public:
        RequestBuilder();

        ~RequestBuilder();

    protected:
        Request request;




};

}

#endif //CXXURL_REQUESTBUILDER_H
