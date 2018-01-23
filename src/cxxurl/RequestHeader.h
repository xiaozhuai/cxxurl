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

class RequestHeader {

    public:
        RequestHeader() : m_CurlSlist(nullptr) { }
        ~RequestHeader() {
            if(m_CurlSlist!=nullptr) curl_slist_free_all(m_CurlSlist);
        }

    public:
        void add(std::string key, std::string value) {
            m_HeadList.push_back(key + ": " + value);
        }

        void add(std::string line) {
            m_HeadList.push_back(line);
        }

        struct curl_slist *getHeaders() {
            if(m_CurlSlist!=nullptr) curl_slist_free_all(m_CurlSlist);

            for (auto &i : m_HeadList) {
                m_CurlSlist = curl_slist_append(m_CurlSlist, i.c_str());
            }
            return m_CurlSlist;
        }

        void clear(){
            m_HeadList.erase(m_HeadList.begin(), m_HeadList.end());
        }

    protected:
        std::vector<std::string> m_HeadList;
        struct curl_slist *m_CurlSlist;

};

}


#endif //CXXURL_HEADER_H
