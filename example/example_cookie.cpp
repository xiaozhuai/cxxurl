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

    SimpleForm form;
    form.add("name", "xiaozhuai");


    RequestBuilder builder;
    builder.url("http://115.159.31.66/cxxurl/test_cookie_login.php")
            .followLocation(true)
            .form(&form)
            .exportCookie("./cookie.txt")
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.post();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;



    ostringstream contentOutput2;

    RequestBuilder builder2;
    builder2.url("http://115.159.31.66/cxxurl/test_cookie_welcome.php")
            .followLocation(true)
            .importCookie("./cookie.txt")
            .contentOutput(&contentOutput2);

    Request& request2 = builder2.build();
    CURLcode res2 = request2.get();

    cout << "***************** CODE *****************"    << endl << res2                 << endl
         << "***************** CONTENT *****************" << endl << contentOutput2.str() << endl
         << flush;


}