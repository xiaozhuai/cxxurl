/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <sstream>
#include "cxxurl_all.h"

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream contentOutput;

    RequestBuilder builder;
    builder.url("https://github.com/xiaozhuai/cxxurl")
            .followLocation(true)
            .verifySSL(false)
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.get();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}