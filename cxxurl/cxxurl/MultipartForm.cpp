/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "MultipartForm.h"

namespace CXXUrl {

MultipartForm::MultipartForm() :
        Form(Form::MULTIPART),
        formpost(NULL),
        lastptr(NULL) {

}

MultipartForm::~MultipartForm() {
    if(formpost!=NULL) curl_formfree(formpost);
    if(lastptr!=NULL) curl_formfree(lastptr);
}

MultipartForm &MultipartForm::add(string key, string value) {
    formDataValueMap[key] = value;
    return *this;
}

MultipartForm &MultipartForm::addFile(string key, string filePath) {
    formDataFileMap[key] = filePath;
    return *this;
}

struct curl_httppost* MultipartForm::getData() {

    if(formpost!=NULL) curl_formfree(formpost);
    if(lastptr!=NULL) curl_formfree(lastptr);

    map<string, string>::iterator itv;
    for (itv = formDataValueMap.begin(); itv != formDataValueMap.end(); itv++) {
        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, itv->first.c_str(),
                     CURLFORM_COPYCONTENTS, itv->second.c_str(),
                     CURLFORM_END);
    }

    map<string, string>::iterator itf;
    for (itf = formDataFileMap.begin(); itf != formDataFileMap.end(); itf++) {
        curl_formadd(&formpost,
                     &lastptr,
                     CURLFORM_COPYNAME, itf->first.c_str(),
                     CURLFORM_FILE, itf->second.c_str(),
                     CURLFORM_END);
    }

    return formpost;

}

void MultipartForm::clear() {
    formDataValueMap.erase(formDataValueMap.begin(), formDataValueMap.end());
    formDataFileMap.erase(formDataFileMap.begin(), formDataFileMap.end());
}

}