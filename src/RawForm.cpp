/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "../include/RawForm.h"

namespace CXXUrl {

RawForm::RawForm() :
        Form(Form::RAW),
        rawData(NULL) {

}

void RawForm::setRawText(string text) {
    this->setRawData(text.data(), text.length());

}

void RawForm::setRawData(const char *data, size_t len) {
    if(rawData!=NULL) free(rawData);
    rawData = (char*)malloc(len);
    memcpy(rawData, data, len);
    _len = len;
}

char* RawForm::getData() {
    return rawData;
}

size_t RawForm::length() {
    return _len;
}

}