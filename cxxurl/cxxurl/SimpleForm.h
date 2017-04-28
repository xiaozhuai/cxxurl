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
        SimpleForm &add(string key, string value);
        char* getData();
        size_t length();
        void clear();

    protected:
        map<string, string> formDataMap;
        string data;



};

}


#endif //CXXURL_SIMPLEFORM_H
