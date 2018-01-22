/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

using namespace std;
using namespace CXXUrl;

void login();
void profile();

int main(int argc, char** argv){
    login();
    profile();
}

void login(){
    ostringstream contentOutput;

    SimpleForm form;
    form.add("name", "xiaozhuai");


    Request request = RequestBuilder()
            .url("http://localhost:3000/cookie/login")
            .followLocation(true)
            .requestBody(&form)
            .exportCookie("./cookie.txt")
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.post();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}

void profile(){
    ostringstream contentOutput;

    Request request = RequestBuilder()
            .url("http://localhost:3000/cookie/profile")
            .followLocation(true)
            .importCookie("./cookie.txt")
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.get();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}