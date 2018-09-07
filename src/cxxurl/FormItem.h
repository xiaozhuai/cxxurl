/**
 * @author : xiaozhuai
 * @date   : 18/1/23
 */

#ifndef CXXURL_FORMITEM_H
#define CXXURL_FORMITEM_H

#include <string>

class FormItem{
    public:
        enum ITEM_TYPE{
            KEY_VALUE = 0,
            FILE
        };

        FormItem() : type(KEY_VALUE) {};

        ITEM_TYPE type;

        std::string key;

        std::string value;

        std::string filePath;
        std::string fileName;
};

#endif //CXXURL_FORMITEM_H
