/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <cxxurl/cxxurl_all.h>

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
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