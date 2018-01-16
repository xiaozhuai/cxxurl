/**
 * @author : xiaozhuai
 * @date   : 18/1/16
 */

#include "HeaderParserStream.h"

namespace CXXUrl {

bool HeaderParserStream::parse_func(string content) {
    content = StringUtils::trim(content);
    StringList lines = StringUtils::explode("\r\n", content);
    if (lines.empty()) return false;
    StringList tokens = StringUtils::explode(" ", lines[0], 3);
    if (tokens.size() != 3) return false;

    http_version = tokens[0];
    code = stoi(tokens[1]);
    status = tokens[2];

    for (int i = 1; i < lines.size(); i++) {
        tokens = StringUtils::explode(":", lines[i], 2);
        if (tokens.size() != 2) continue;
        string key = StringUtils::trim(tokens[0]);
        string value = StringUtils::trim(tokens[1]);
        if (headers.find(key) == headers.end())
            headers[key] = StringList();
        headers[key].push_back(value);
    }

    return true;
}

string HeaderParserStream::dump() {
    stringstream result;
    for(auto& i : headers){
        string key = i.first;
        StringList values = i.second;
        result << " -- " << key << endl;
        for(auto& value : values){
            result << "   -- " << value << endl;
        }
    }
    return result.str();
}

}