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

        RequestBuilder &query(string key, string value);

        RequestBuilder &followLocation(bool followLocation);

        RequestBuilder &contentOutput(ostream *stream);

        RequestBuilder &headerOutput(ostream *stream);

        RequestBuilder &maxRedirs(int maxRedirs);

        RequestBuilder &form(Form *form);

        RequestBuilder &userAgent(string userAgent);

        RequestBuilder &referer(string referer);

    public:
        Request &build();


    public:
        RequestBuilder();

        ~RequestBuilder();

    protected:
        Request request;
        string _url;
        map<string, string> queryMap;

        string generateRealUrl();




};

}

#endif //CXXURL_REQUESTBUILDER_H
