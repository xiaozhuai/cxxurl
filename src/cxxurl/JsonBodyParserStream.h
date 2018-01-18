/**
 * @author : xiaozhuai
 * @date   : 18/1/18
 */

#ifndef CXXURL_JSONBODYPARSERSTREAM_H
#define CXXURL_JSONBODYPARSERSTREAM_H

#include "ParseableOutputStringStream.h"
#include "json.hpp"

using nlohmann::json;

namespace CXXUrl {

class JsonBodyParserStream : public ParseableOutputStringStream {
    protected:
        bool parse_func(string content){
            try{
                json = json::parse(content);
                return true;
            }catch (json::exception& e){
                return false;
            }
        };

    public:
        json json;

};

}

#endif //CXXURL_JSONBODYPARSERSTREAM_H
