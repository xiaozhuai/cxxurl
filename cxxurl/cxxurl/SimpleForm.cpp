/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "SimpleForm.h"

namespace CXXUrl {

SimpleForm::SimpleForm() :
        Form(Form::SIMPLE) {

}

char* SimpleForm::getData() {
    string queryStr = "";
    map<string, string>::iterator it;
    for (it = formDataMap.begin(); it != formDataMap.end(); it++) {
        queryStr += "&" + UrlEncode::encode(it->first) + "=" + UrlEncode::encode(it->second);
    }
    data = queryStr;
    return (char*)data.data();
}

size_t SimpleForm::length() {
    return data.length();
}

SimpleForm &SimpleForm::add(string key, string value) {
    formDataMap[key] = value;
    return *this;
}

void SimpleForm::clear() {
    formDataMap.erase(formDataMap.begin(), formDataMap.end());
}

}