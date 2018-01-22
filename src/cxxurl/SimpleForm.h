/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_SIMPLEFORM_H
#define CXXURL_SIMPLEFORM_H

#include <string>
#include <map>
#include "RequestBody.h"

namespace CXXUrl {

class SimpleForm : public RequestBody{
    public:
        SimpleForm() : RequestBody(RequestBody::X_WWW_FORM_URLENCODED) { }

    public:
        SimpleForm &add(std::string key, std::string value) {
            m_FormDataMap[key] = value;
            return *this;
        }

        char* getData() {
            std::string queryStr;
            for (auto i : m_FormDataMap) {
                queryStr += "&" + UrlEncoder::encode(i.first) + "=" + UrlEncoder::encode(i.second);
            }
            m_Data = queryStr.substr(1);
            return (char*)m_Data.data();
        }

        size_t length() {
            return m_Data.length();
        }

        void clear() {
            m_FormDataMap.erase(m_FormDataMap.begin(), m_FormDataMap.end());
        }

    protected:
        std::map<std::string, std::string> m_FormDataMap;
        std::string m_Data;



};

}


#endif //CXXURL_SIMPLEFORM_H
