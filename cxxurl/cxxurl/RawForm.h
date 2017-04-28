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
        RawForm &setRawText(string text);
        RawForm &setRawData(const char* data, size_t len);
        char* getData();
        size_t length();
        void clear();

    protected:
        char* rawData;
        size_t _len;


};

}

#endif //CXXURL_RAWFORM_H
