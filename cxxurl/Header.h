/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#ifndef CXXURL_HEADER_H
#define CXXURL_HEADER_H

#include <string>
#include <vector>
#include <curl/curl.h>

namespace CXXUrl {

using namespace std;

class Header {

    public:
        Header();
        ~Header();

    public:
        void add(string key, string value);
        void add(string line);
        struct curl_slist *getHeaders();

    protected:
        vector<string> headList;
        struct curl_slist *curlSlist;

};

}


#endif //CXXURL_HEADER_H
