/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_RAWFORM_H
#define CXXURL_RAWFORM_H

#include <string>
#include <string.h>
#include "Form.h"

namespace CXXUrl {

using namespace std;

class RawForm : public Form{

    public:
        RawForm();

    public:
        void setRawText(string text);
        void setRawData(const char* data, size_t len);
        char* getData();
        size_t length();

    protected:
        char* rawData;
        size_t _len;


};

}

#endif //CXXURL_RAWFORM_H
