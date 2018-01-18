/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_MULTIPARTFORM_H
#define CXXURL_MULTIPARTFORM_H


#include <string>
#include <map>
#include <iostream>
#include <curl/curl.h>
#include "Form.h"

namespace CXXUrl {

using namespace std;

class MultipartForm : public Form {
    public:
        MultipartForm() :
                Form(Form::MULTIPART),
                m_FormHeadPtr(nullptr),
                m_FormTailPtr(nullptr) { }

        ~MultipartForm() {
            if(m_FormHeadPtr!=nullptr) curl_formfree(m_FormHeadPtr);
        }

    public:
        MultipartForm &add(string key, string value) {
            m_FormDataValueMap[key] = value;
            return *this;
        }

        MultipartForm &addFile(string key, string filePath) {
            m_FormDataFileMap[key] = filePath;
            return *this;
        }

        MultipartForm &addFile(string key, string filePath, string fileName) {
            m_FormDataFileMap[key] = filePath;
            m_FormDataFileNameMap[key] = fileName;
            return *this;
        }

        struct curl_httppost* getData() {

            if(m_FormHeadPtr!=nullptr){
                curl_formfree(m_FormHeadPtr);
                m_FormHeadPtr = nullptr;
                m_FormTailPtr = nullptr;
            }

            for (auto i : m_FormDataValueMap) {
                curl_formadd(&m_FormHeadPtr,
                             &m_FormTailPtr,
                             CURLFORM_COPYNAME, i.first.c_str(),
                             CURLFORM_COPYCONTENTS, i.second.c_str(),
                             CURLFORM_END);
            }

            for (auto i : m_FormDataFileMap) {
                if (m_FormDataFileNameMap.find(i.first) == m_FormDataFileNameMap.end()) {
                    curl_formadd(&m_FormHeadPtr,
                                 &m_FormTailPtr,
                                 CURLFORM_COPYNAME, i.first.c_str(),
                                 CURLFORM_FILE, i.second.c_str(),
                                 CURLFORM_END);
                } else {
                    curl_formadd(&m_FormHeadPtr,
                                 &m_FormTailPtr,
                                 CURLFORM_COPYNAME, i.first.c_str(),
                                 CURLFORM_FILE, i.second.c_str(),
                                 CURLFORM_FILENAME, m_FormDataFileNameMap[i.first].c_str(),
                                 CURLFORM_END);
                }
            }

            return m_FormHeadPtr;

        }

        void clear() {
            m_FormDataValueMap.erase(m_FormDataValueMap.begin(), m_FormDataValueMap.end());
            m_FormDataFileMap.erase(m_FormDataFileMap.begin(), m_FormDataFileMap.end());
            m_FormDataFileNameMap.erase(m_FormDataFileNameMap.begin(), m_FormDataFileNameMap.end());
        }

    protected:
        struct curl_httppost* m_FormHeadPtr;
        struct curl_httppost* m_FormTailPtr;
        map<string, string> m_FormDataValueMap;
        map<string, string> m_FormDataFileMap;
        map<string, string> m_FormDataFileNameMap;
};

}

#endif //CXXURL_MULTIPARTFORM_H
