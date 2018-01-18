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
    stringstream ss;
    CURLcode res;
    Request request = RequestBuilder()
            .url("http://localhost:3000/method")
            .followLocation(true)
            .contentOutput(&ss)
            .build();


    ss.str("");
    res = request.get();
    /*
     * or
     *
     * res = request.exec("GET");
     */
    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << ss.str() << endl
         << flush;

    ss.str("");
    res = request.post();
    /*
     * or
     *
     * res = request.exec("POST");
     */
    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << ss.str() << endl
         << flush;
}
