/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "MultipartForm.h"

namespace CXXUrl {

MultipartForm::MultipartForm() :
        Form(Form::MULTIPART),
        formpost(nullptr),
        lastptr(nullptr) {

}

MultipartForm::~MultipartForm() {
    if(formpost!=nullptr) curl_formfree(formpost);
}

MultipartForm &MultipartForm::add(string key, string value) {
    formDataValueMap[key] = value;
    return *this;
}

MultipartForm &MultipartForm::addFile(string key, string filePath) {
    formDataFileMap[key] = filePath;
    return *this;
}

MultipartForm &MultipartForm::addFile(string key, string filePath, string fileName) {
    formDataFileMap[key] = filePath;
    formDataFileNameMap[key] = fileName;
    return *this;
}

struct curl_httppost* MultipartForm::getData() {

    if(formpost!=nullptr){
        curl_formfree(formpost);
        formpost = nullptr;
        lastptr = nullptr;
    }

    for (auto i : formDataValueMap) {
        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, i.first.c_str(),
                     CURLFORM_COPYCONTENTS, i.second.c_str(),
                     CURLFORM_END);
    }

    for (auto i : formDataFileMap) {
        if (formDataFileNameMap.find(i.first) == formDataFileNameMap.end()) {
            curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, i.first.c_str(),
                         CURLFORM_FILE, i.second.c_str(),
                         CURLFORM_END);
        } else {
            curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, i.first.c_str(),
                         CURLFORM_FILE, i.second.c_str(),
                         CURLFORM_FILENAME, formDataFileNameMap[i.first].c_str(),
                         CURLFORM_END);
        }
    }

    return formpost;

}

void MultipartForm::clear() {
    formDataValueMap.erase(formDataValueMap.begin(), formDataValueMap.end());
    formDataFileMap.erase(formDataFileMap.begin(), formDataFileMap.end());
    formDataFileNameMap.erase(formDataFileNameMap.begin(), formDataFileNameMap.end());
}

}