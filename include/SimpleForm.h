/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_SIMPLEFORM_H
#define CXXURL_SIMPLEFORM_H

#include <string>
#include <map>
#include "Form.h"

namespace CXXUrl {

using namespace std;

class SimpleForm : public Form{
    public:
        SimpleForm();

    public:
        void add(string key, string value);
        string generateSimpleFormQueryString();

    protected:
        map<string, string> formDataMap;



};

}


#endif //CXXURL_SIMPLEFORM_H
