/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_SIMPLEFORM_H
#define CXXURL_SIMPLEFORM_H

#include <string>
#include <map>
#include "Form.h"

namespace CXXUrl {

using namespace std;

class SimpleForm : public Form{
    public:
        SimpleForm() : Form(Form::SIMPLE) { }

    public:
        SimpleForm &add(string key, string value) {
            m_FormDataMap[key] = value;
            return *this;
        }

        char* getData() {
            string queryStr;
            for (auto i : m_FormDataMap) {
                queryStr += "&" + UrlEncode::encode(i.first) + "=" + UrlEncode::encode(i.second);
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
        map<string, string> m_FormDataMap;
        string m_Data;



};

}


#endif //CXXURL_SIMPLEFORM_H
