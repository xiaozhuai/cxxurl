/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <cxxurl/cxxurl_all.h>
#include <cxxurl/HeaderParserStream.h>

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
    HeaderParserStream headerParserStream;

    Request request = RequestBuilder()
            .url("http://localhost:3000/get")
            .followLocation(true)
            .headerOutput(&headerParserStream)
            .build();
    CURLcode res = request.get();

    headerParserStream.parse();
    ResponseHeader header = headerParserStream.header;

    cout << "------------ Code ------------" << endl
         << res << endl
         << "---------- HTTP Code ---------" << endl
         << header.code << endl
         << "------------ Host ------------" << endl
         << header["Host"][0] << endl
         << "-------- Header Parsed -------" << endl
         << header.dump() << endl
         << flush;
}

void example2(){
    stringstream ss;
    ResponseHeader header;

    Request request = RequestBuilder()
            .url("http://localhost:3000/get")
            .followLocation(true)
            .headerOutput(&ss)
            .build();
    CURLcode res = request.get();

    ss >> header;

    cout << "------------ Code ------------" << endl
         << res << endl
         << "---------- HTTP Code ---------" << endl
         << header.code << endl
         << "------------ Host ------------" << endl
         << header["Host"][0] << endl
         << "-------- Header Parsed -------" << endl
         << header.dump() << endl
         << flush;
}