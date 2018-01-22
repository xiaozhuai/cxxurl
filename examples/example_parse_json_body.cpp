/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <cxxurl/cxxurl_all.h>
#include <json.hpp>

using namespace std;
using namespace CXXUrl;
using nlohmann::json;


int main(int argc, char** argv){
    stringstream ss;
    json json;

    Request request = RequestBuilder()
            .url("http://localhost:3000/json")
            .followLocation(true)
            .contentOutput(&ss)
            .build();
    CURLcode res = request.get();

    ss >> json;

    cout << "------------ Code ------------" << endl
         << res << endl
         << "--------- Body Parsed --------" << endl
         << "project :  " << json["project"].get<string>() << endl
         << "author  :  " << json["author"].get<string>()  << endl
         << "repos   :  " << json["repos"].get<string>()   << endl
         << flush;
}