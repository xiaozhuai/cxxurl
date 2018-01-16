/**
 * @author : xiaozhuai
 * @date   : 17/1/5
 */

#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream contentOutput;

    Request request;
    request.setUrl("http://localhost:3000/get");
    request.setFollowLocation(true);
    request.setContentOutput(&contentOutput);

    CURLcode res = request.get();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}