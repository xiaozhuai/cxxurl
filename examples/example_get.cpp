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
    Request request = RequestBuilder()
            .url("http://localhost:3000/get")
            .followLocation(true)
            .contentOutput(&contentOutput)
            .build();

    CURLcode res = request.get();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}