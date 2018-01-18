/**
 * @author : xiaozhuai
 * @date   : 18/1/18
 */

#ifndef CXXURL_RESPONSEHEADER_H
#define CXXURL_RESPONSEHEADER_H

#endif //CXXURL_RESPONSEHEADER_H

#include <exception>
#include "StringUtils.h"
#include <map>
#include <sstream>

namespace CXXUrl{

typedef map<string, StringList> HeaderStruct;

class ParseResponseHeaderException : public std::exception
{
    public:
        const char* what() const noexcept override
        {
            return m.what();
        }

        const int id;

    public:
        ParseResponseHeaderException(int id_, const char* what_arg) : id(id_), m(what_arg) {}
    protected:
        static std::string name(const std::string& ename, int id_)
        {
            return "[ParseResponseHeaderException." + ename + "." + std::to_string(id_) + "] ";
        }

    private:
        std::runtime_error m;
};

class ResponseHeader : public HeaderStruct{
    public:
        static ResponseHeader parse(string content){
            return ResponseHeader(content);
        }
        ResponseHeader() = default;
        ResponseHeader(string content){
            parse_string(content);
        }

        void parse_string(string content){
            content = StringUtils::trim(content);
            StringList lines = StringUtils::explode("\r\n", content);
            if (lines.empty()) throw ParseResponseHeaderException(1, "parse header err");
            StringList tokens = StringUtils::explode(" ", lines[0], 3);
            if (tokens.size() != 3) throw ParseResponseHeaderException(2, "parse header err");

            http_version = tokens[0];
            code = stoi(tokens[1]);
            status = tokens[2];

            for (int i = 1; i < lines.size(); i++) {
                tokens = StringUtils::explode(":", lines[i], 2);
                if (tokens.size() != 2) continue;
                string key = StringUtils::trim(tokens[0]);
                string value = StringUtils::trim(tokens[1]);
                if (this->find(key) == this->end())
                    (*this)[key] = StringList();
                (*this)[key].push_back(value);
            }
        }

        friend void operator>> (stringstream& ss, ResponseHeader& header)
        {
            header.parse_string(ss.str());
        }

        string dump() {
            stringstream result;
            result << "code: " << code << endl;
            result << "http_version: " << http_version << endl;
            result << "status: " << status << endl;
            for(auto& i : (*this)){
                string key = i.first;
                StringList values = i.second;
                for(auto& value : values){
                    result << key << ": " << value << endl;
                }
            }
            return result.str();
        }
    public:
        string http_version;
        int code;
        string status;
};

}