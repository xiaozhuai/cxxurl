/**
 * @author : xiaozhuai
 * @date   : 18/1/16
 */

#ifndef CXXURL_HEADERPARSERSTREAM_H
#define CXXURL_HEADERPARSERSTREAM_H

#include "ParseableOutputStringStream.h"
#include "StringUtils.h"
#include <map>



namespace CXXUrl {

class HeaderParserStream : public ParseableOutputStringStream {
    protected:
        bool parse_func(string content) override;

    public:
        string http_version;
        int code;
        string status;

    public:
        map<string, StringList> headers;
        string dump() override;

};

}

#endif //CXXURL_HEADERPARSERSTREAM_H
