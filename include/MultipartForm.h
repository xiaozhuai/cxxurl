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
        MultipartForm();
        ~MultipartForm();

    public:
        void add(string key, string value);
        void addFile(string key, string filePath);
        struct curl_httppost* generateMultipartFormData();

    protected:
        struct curl_httppost* formpost;
        struct curl_httppost* lastptr;
        map<string, string> formDataValueMap;
        map<string, string> formDataFileMap;
};

}

#endif //CXXURL_MULTIPARTFORM_H
