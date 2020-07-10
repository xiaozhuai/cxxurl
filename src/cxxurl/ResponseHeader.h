/**
 * @author : xiaozhuai
 * @date   : 18/1/18
 */

#ifndef CXXURL_RESPONSEHEADER_H
#define CXXURL_RESPONSEHEADER_H

#include <exception>
#include "StringUtils.h"
#include <map>
#include <sstream>

namespace CXXUrl{

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

class ResponseHeader : public std::map<std::string, std::vector<std::string>>{
    public:
        static ResponseHeader parse(std::string content){
            return ResponseHeader(content);
        }
        ResponseHeader() = default;
        ResponseHeader(std::string content){
            parse_string(content);
        }

        void parse_string(std::string content){
            content = StringUtils::trim(content);
            std::vector<std::string> lines = StringUtils::explode("\r\n", content);
            if (lines.empty()) throw ParseResponseHeaderException(1, "parse header err");
            std::vector<std::string> tokens = StringUtils::explode(" ", lines[0], 3);
            if (tokens.size() != 3) throw ParseResponseHeaderException(2, "parse header err");

            http_version = tokens[0];
            code = std::stoi(tokens[1]);
            status = tokens[2];

            for (int i = 1; i < lines.size(); i++) {
                tokens = StringUtils::explode(":", lines[i], 2);
                if (tokens.size() != 2) continue;
                std::string key = StringUtils::trim(tokens[0]);
                std::string value = StringUtils::trim(tokens[1]);
                if (this->find(key) == this->end())
                    (*this)[key] = std::vector<std::string>();
                (*this)[key].push_back(value);
            }
        }

        friend void operator>> (std::stringstream& ss, ResponseHeader& header)
        {
            header.parse_string(ss.str());
        }

        std::string dump() {
            std::stringstream result;
            result << "code: " << code << std::endl;
            result << "http_version: " << http_version << std::endl;
            result << "status: " << status << std::endl;
            for(auto& i : (*this)){
                std::string key = i.first;
                std::vector<std::string> values = i.second;
                for(auto& value : values){
                    result << key << ": " << value << std::endl;
                }
            }
            return result.str();
        }
    public:
        std::string http_version;
        int code;
        std::string status;
};

}

#endif //CXXURL_RESPONSEHEADER_H
