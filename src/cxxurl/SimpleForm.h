/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_SIMPLEFORM_H
#define CXXURL_SIMPLEFORM_H

#include <string>
#include <map>
#include <vector>
#include "RequestBody.h"
#include "FormItem.h"

namespace CXXUrl {

class SimpleForm : public RequestBody{
    public:
        SimpleForm() : RequestBody(RequestBody::X_WWW_FORM_URLENCODED) { }

    public:
        SimpleForm &add(std::string key, std::string value) {
            FormItem item;
            item.type = FormItem::KEY_VALUE;
            item.key = key;
            item.value = value;
            m_FormDataList.push_back(item);
            return *this;
        }

        const char* getData() {
            std::string queryStr;
            for (auto& i : m_FormDataList) {
                queryStr += "&" + UrlEncoder::encode(i.key) + "=" + UrlEncoder::encode(i.value);
            }
            m_Data = queryStr.substr(1);
            return m_Data.data();
        }

        size_t length() {
            return m_Data.length();
        }

        void clear() {
            m_FormDataList.erase(m_FormDataList.begin(), m_FormDataList.end());
        }

    protected:
        std::vector<FormItem> m_FormDataList;
        std::string m_Data;



};

}


#endif //CXXURL_SIMPLEFORM_H
