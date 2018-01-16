/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <cxxurl/cxxurl_all.h>

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ofstream downloadFile("./tao.png");

    Request request = RequestBuilder()
            .url("http://localhost:3000/download")
            .followLocation(true)
            .contentOutput(&downloadFile)
            .build();
    CURLcode res = request.get();

    downloadFile.flush();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << "Content has wrote to ./tao.png" << endl
         << flush;
}