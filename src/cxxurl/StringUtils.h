/**
 * @author : xiaozhuai
 * @date   : 18/1/16
 */

#ifndef CXXURL_STRINGUTILS_H
#define CXXURL_STRINGUTILS_H

#include <string>
#include <vector>

namespace CXXUrl {

class StringUtils {
    public:

        static std::vector<std::string> explode(std::string delimiter, std::string text, std::string::size_type limit = std::string::npos, std::string escape = "") {
            std::vector<std::string> result;
            std::string::size_type searchFrom = 0;
            std::string::size_type delimiterIndex = getDelimiterIndex(text, delimiter, escape, searchFrom);
            while (delimiterIndex != std::string::npos) {
                std::string token = text.substr(searchFrom, delimiterIndex - searchFrom);
                result.push_back(token);
                searchFrom = delimiterIndex + delimiter.length();
                if (result.size() + 1 == limit) {
                    break;
                }
                delimiterIndex = getDelimiterIndex(text, delimiter, escape, searchFrom);
            }
            result.push_back(text.substr(searchFrom));
            return result;
        }

        static std::string replace(std::string text, std::string search, std::string replace) {
            if (search == replace) {
                return text;
            }
            std::string result = text;
            std::string::size_type index = result.find(search, 0);
            std::string::size_type searchLength = search.length();
            std::string::size_type replaceLength = replace.length();

            while (std::string::npos != index) {
                result.replace(index, searchLength, replace);
                index = result.find(search, index - searchLength + replaceLength + 1);
            }
            return result;
        }

        static std::string trim(std::string str, const char* characters = " \t\r\n"){
            str = ltrim(str, characters);
            str = rtrim(str, characters);
            return str;
        }

        static std::string ltrim(std::string str, const char* characters = " \t\r\n"){
            str = str.erase(0, str.find_first_not_of(characters));
            return str;
        }

        static std::string rtrim(std::string str, const char* characters = " \t\r\n"){
            str = str.erase(str.find_last_not_of(characters) + 1);
            return str;
        }

        static std::string tolower(std::string str){
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
            return str;
        }

        static std::string toupper(std::string str){
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
            return str;
        }

    private:
        StringUtils() = default;

        static std::string::size_type getDelimiterIndex(std::string &text, std::string &delimiter, std::string &escape, std::string::size_type searchFrom) {
            if (escape.length() == 0) {
                return (int) text.find(delimiter, searchFrom);
            } else {
                while (searchFrom < text.length()) {
                    std::string::size_type draft = text.find(delimiter, searchFrom);
                    if (draft == std::string::npos) {
                        return std::string::npos;
                    }
                    auto expectedEscapeIndex = (long)(draft - escape.length());
                    if (0 <= expectedEscapeIndex) {
                        if (text.substr((std::string::size_type)expectedEscapeIndex, escape.length()) == escape) {
                            searchFrom = draft + 1;
                        } else {
                            return draft;
                        }
                    } else {
                        return draft;
                    }
                }
                return std::string::npos;
            }
        }
};

}

#endif //CXXURL_STRINGUTILS_H
