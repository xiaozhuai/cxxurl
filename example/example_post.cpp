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

//    simple form, you can only set key-value
    SimpleForm form;
    form.add("name", "xiaozhuai");
    form.add("sex",  "male");

////    multipart form, you can upload a file, or key-value
//    MultipartForm multipartForm;
//    multipartForm.add("name", "xiaozhuai");
//    multipartForm.addFile("avatar", "./tao.png");

////    raw form, you can set request body with raw text
//    RawForm rawFormText;
//    rawFormText.setRawText("{ \"name\": \"xiaozhuai\" }");

////    raw form, you can set request body with raw bytes
//    char buffer[100];
//    RawForm rawFormBytes;
//    rawFormBytes.setRawData(buffer, 100);

    RequestBuilder builder;
    builder.url("http://115.159.31.66/cxxurl/test_post.php")
            .followLocation(true)
            .form(&form)
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.post();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}