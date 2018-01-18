/**
 * @author : xiaozhuai
 * @date   : 18/1/16
 */

#ifndef CXXURL_PARSEABLEOSTREAM_H
#define CXXURL_PARSEABLEOSTREAM_H

#include <sstream>
#include <string>

using namespace std;

namespace CXXUrl {

class ParseableOutputStringStream : public ostringstream {
    public:
        ParseableOutputStringStream() {};

        virtual ~ParseableOutputStringStream() {};

        bool parse() {
            this->flush();
            return parse_func(this->str());
        }

    protected:
        virtual bool parse_func(string content) = 0;

};

}


#endif //CXXURL_PARSEABLEOSTREAM_H
