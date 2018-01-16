/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#include "RawForm.h"

namespace CXXUrl {

RawForm::RawForm() :
        Form(Form::RAW),
        rawData(nullptr) {

}

RawForm & RawForm::setRawText(string text) {
    this->setRawData(text.data(), text.length());
    return *this;
}

RawForm & RawForm::setRawData(const char *data, size_t len) {
    if(rawData!=nullptr) free(rawData);
    rawData = (char*)malloc(len);
    memcpy(rawData, data, len);
    _len = len;
    return *this;
}

void RawForm::clear() {
    rawData = nullptr;
}

char* RawForm::getData() {
    return rawData;
}

size_t RawForm::length() {
    return _len;
}

}