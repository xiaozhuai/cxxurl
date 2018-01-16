/**
 * @author : xiaozhuai
 * @date   : 18/1/16
 */

#ifndef CXXURL_STRINGUTILS_H
#define CXXURL_STRINGUTILS_H

#include <string>
#include <vector>

using namespace std;

typedef vector<string> StringList;

namespace CXXUrl {

class StringUtils {
    public:

        static StringList explode(string delimiter, string text, string::size_type limit = string::npos, string escape = "") {
            StringList result;
            string::size_type searchFrom = 0;
            string::size_type delimiterIndex = getDelimiterIndex(text, delimiter, escape, searchFrom);
            while (delimiterIndex != string::npos) {
                string token = text.substr(searchFrom, delimiterIndex - searchFrom);
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

        static string replace(string text, string search, string replace) {
            if (search == replace) {
                return text;
            }
            string result = text;
            string::size_type index = result.find(search, 0);
            int searchLength = search.length();
            int replaceLength = replace.length();

            while (string::npos != index) {
                result.replace(index, searchLength, replace);
                index = result.find(search, index - searchLength + replaceLength + 1);
            }
            return result;
        }

        static string trim(string str, const char* characters = " \t\r\n"){
            str = ltrim(str, characters);
            str = rtrim(str, characters);
            return str;
        }

        static string ltrim(string str, const char* characters = " \t\r\n"){
            str = str.erase(0, str.find_first_not_of(characters));
            return str;
        }

        static string rtrim(string str, const char* characters = " \t\r\n"){
            str = str.erase(str.find_last_not_of(characters) + 1);
            return str;
        }

    private:
        StringUtils() {}

        static string::size_type getDelimiterIndex(string &text, string &delimiter, string &escape, string::size_type searchFrom) {
            if (escape.length() == 0) {
                return (int) text.find(delimiter, searchFrom);
            } else {
                while (searchFrom < text.length()) {
                    int draft = (int) text.find(delimiter, searchFrom);
                    if (draft == string::npos) {
                        return string::npos;
                    }
                    int expectedEscapeIndex = draft - escape.length();
                    if (0 <= expectedEscapeIndex) {
                        if (text.substr(expectedEscapeIndex, escape.length()) == escape) {
                            searchFrom = draft + 1;
                        } else {
                            return draft;
                        }
                    } else {
                        return draft;
                    }
                }
                return string::npos;
            }
        }
};

}

#endif //CXXURL_STRINGUTILS_H
