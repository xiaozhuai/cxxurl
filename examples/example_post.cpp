/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

using namespace std;
using namespace CXXUrl;

void example_simple_form();
void example_multipart_form();
void example_raw_body_text();
void example_raw_body_binary();

int main(int argc, char** argv){
    example_simple_form();
    example_multipart_form();
    example_raw_body_text();
    example_raw_body_binary();
}

void example_simple_form(){
    ostringstream contentOutput;
    // simple form, you can only set key-value (x-www-form-urlencoded)
    SimpleForm form;
    form.add("name", "xiaozhuai");
    form.add("sex",  "male");
    Request request = RequestBuilder()
            .url("http://localhost:3000/post")
            .followLocation(true)
            .requestBody(&form)
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.post();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}

void example_multipart_form(){
    ostringstream contentOutput;
    // multipart form, you can upload a file, or key-value
    MultipartForm form;
    form.add("name", "xiaozhuai");
    form.addFile("avatar", "../example_server/tao.png");
    form.addFile("avatar2", "../example_server/tao.png", "tao2.png");
    Request request = RequestBuilder()
            .url("http://localhost:3000/post")
            .followLocation(true)
            .requestBody(&form)
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.post();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}

void example_raw_body_text(){
    ostringstream contentOutput;
    // raw form, you can set request body with text
    RawRequestBody form;
    form.setRawText("{ \"name\": \"xiaozhuai\" }");
    Request request = RequestBuilder()
            .url("http://localhost:3000/post")
            .followLocation(true)
            .requestBody(&form)
            .contentType("application/json")
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.post();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}

void example_raw_body_binary(){
    ostringstream contentOutput;
    // raw form, you can set request body with raw bytes
    char buffer[100];
    RawRequestBody form;
    form.setRawData(buffer, 100);
    Request request = RequestBuilder()
            .url("http://localhost:3000/post")
            .followLocation(true)
            .requestBody(&form)
            .contentType("application/octet-stream")
            .contentOutput(&contentOutput)
            .build();
    CURLcode res = request.post();

    cout << "------------ Code ------------" << endl
         << res << endl
         << "----------- Content ----------" << endl
         << contentOutput.str() << endl
         << flush;
}