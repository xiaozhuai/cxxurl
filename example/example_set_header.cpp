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

    Header header;
    header.add("name", "xiaozhuai");
    header.add("sex: male");

    RequestBuilder builder;
    builder.url("http://115.159.31.66/cxxurl/test_header.php")
            .followLocation(true)
            .header(&header)
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.get();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}