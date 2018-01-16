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
    HeaderParserStream headerOutput;
    ostringstream contentOutput;

    Request request = RequestBuilder()
            .url("http://localhost:3000/get")
            .followLocation(true)
            .headerOutput(&headerOutput)
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.get();

    headerOutput.parse();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "---------- HTTP Code ---------" << endl
         << headerOutput.code << endl
         << "-------- Header Parsed -------" << endl
         << headerOutput.dump() << endl
//         << "----------- Content ----------" << endl
//         << contentOutput.str() << endl
         << flush;
}