/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <cxxurl/cxxurl_all.h>
#include <cxxurl/JsonBodyParserStream.h>

using namespace std;
using namespace CXXUrl;

void example1();
void example2();


int main(int argc, char** argv){
    // these two sample do the same thing
    example1();
    example2();
}

void example1(){
    JsonBodyParserStream jsonBodyParserStream;

    Request request = RequestBuilder()
            .url("http://localhost:3000/json")
            .followLocation(true)
            .contentOutput(&jsonBodyParserStream)
            .build();
    CURLcode res = request.get();

    jsonBodyParserStream.parse();
    json json = jsonBodyParserStream.json;

    cout << "------------ Code ------------" << endl
         << res << endl
         << "--------- Body Parsed --------" << endl
         << "project :  " << json["project"].get<string>() << endl
         << "author  :  " << json["author"].get<string>()  << endl
         << "repos   :  " << json["repos"].get<string>()   << endl
         << flush;
}

void example2(){
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