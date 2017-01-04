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

        RequestBuilder &header(Header *header);

        RequestBuilder &timeout(long milliSeconds);

    public:
        Request &build();


    public:
        RequestBuilder();

        ~RequestBuilder();

    protected:
        Request request;




};

}

#endif //CXXURL_REQUESTBUILDER_H
