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
    string queryStr;
    for (auto i : formDataMap) {
        queryStr += "&" + UrlEncode::encode(i.first) + "=" + UrlEncode::encode(i.second);
    }
    data = queryStr.substr(1);
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