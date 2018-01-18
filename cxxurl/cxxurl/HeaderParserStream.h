/**
 * @author : xiaozhuai
 * @date   : 18/1/16
 */

#ifndef CXXURL_HEADERPARSERSTREAM_H
#define CXXURL_HEADERPARSERSTREAM_H

#include "ParseableOutputStringStream.h"
#include "ResponseHeader.h"

namespace CXXUrl {

class HeaderParserStream : public ParseableOutputStringStream {
    protected:
        bool parse_func(string content){
            try{
                header = ResponseHeader::parse(content);
                return true;
            }catch (ParseResponseHeaderException& e){
                return false;
            }
        };

    public:
        ResponseHeader header;

};

}

#endif //CXXURL_HEADERPARSERSTREAM_H
