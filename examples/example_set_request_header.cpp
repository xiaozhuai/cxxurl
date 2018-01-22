/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream contentOutput;

    RequestHeader header;
    header.add("name", "xiaozhuai");
    header.add("sex: male");

    Request request = RequestBuilder()
            .url("http://localhost:3000/header")
            .followLocation(true)
            .requestHeader(&header)
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.get();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}