/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include "cxxurl_all.h"

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ofstream downloadFile("./tao.png");

    RequestBuilder builder;
    builder.url("http://115.159.31.66/cxxurl/tao.png")
            .followLocation(true)
            .contentOutput(&downloadFile);

    Request& request = builder.build();
    CURLcode res = request.get();

    downloadFile.flush();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT HAS WRITE TO FILE *****************"               << endl
         << flush;
}