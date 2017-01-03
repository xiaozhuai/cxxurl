/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "../include/SimpleForm.h"

namespace CXXUrl {

SimpleForm::SimpleForm() :
        Form(Form::SIMPLE) {

}

string SimpleForm::generateSimpleFormQueryString() {
    string queryStr = "";
    map<string, string>::iterator it;
    for (it = formDataMap.begin(); it != formDataMap.end(); it++) {
        queryStr += "&" + it->first + "=" + it->second;
    }
    return UrlEncode::encode(queryStr.substr(1));
}

void SimpleForm::add(string key, string value) {
    formDataMap[key] = value;
}

}