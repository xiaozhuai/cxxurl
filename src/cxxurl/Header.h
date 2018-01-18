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
        Header() : m_CurlSlist(nullptr) { }
        ~Header() {
            if(m_CurlSlist!=nullptr) curl_slist_free_all(m_CurlSlist);
        }

    public:
        void add(string key, string value) {
            m_HeadList.push_back(key + ": " + value);
        }
        void add(string line) {
            m_HeadList.push_back(line);
        }
        struct curl_slist *getHeaders() {
            if(m_CurlSlist!=nullptr) curl_slist_free_all(m_CurlSlist);

            for (auto &i : m_HeadList) {
                m_CurlSlist = curl_slist_append(m_CurlSlist, i.c_str());
            }
            return m_CurlSlist;
        }

    protected:
        vector<string> m_HeadList;
        struct curl_slist *m_CurlSlist;

};

}


#endif //CXXURL_HEADER_H
