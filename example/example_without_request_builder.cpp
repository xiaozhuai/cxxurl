/**
 * @author : xiaozhuai
 * @date   : 17/1/5
 */

#include <iostream>
#include <sstream>
#include "cxxurl_all.h"

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream contentOutput;

    Request request;
    request.setUrl("http://xiaozhuai.github.io");
    request.setFollowLocation(true);
    request.setContentOutput(&contentOutput);

    CURLcode res = request.get();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}