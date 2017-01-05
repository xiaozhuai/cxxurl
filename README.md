# CXXCurl

[[English README](README.md)] [[中文说明](README_CN.md)]

CXXUrl is base on libcurl, but it's not only an object-oriented C++ wrapper for cURL.

By the way, if you want to known more about libcurl, you should go [http://curl.haxx.se/](http://curl.haxx.se/)

Under [MIT LICENSE](LICENSE.md)

author: xiaozhuai - [xiaozhuai7@gmail.com](xiaozhuai7@gmail.com)

# Run Example

```bash
$ cd /path/to/cxxurl
$ mkdir build
$ cmake ..
$ make
```

Then you can run example, such as 

```bash
$ ./example_get
```



# Compile and Link

It's so easy to use this lib, it's lite and you don't need to compile it to a static or shared library.

All you need to do with cmake just like this:

```
find_package(CURL REQUIRED)                                    #find curl, of cource, you need curl installed
set(CXXURL_SRC cxxurl/cxxurl_all.cpp)                          #define the path of cxxurl_all.cpp
add_executable(target ${CXXURL_SRC} ${ALL_YOUR_SOURCE})        #add cxxurl_all.cpp to your target
target_link_libraries(target ${CURL_LIBRARY})                  #link curl library
include_directories(cxxurl ${CURL_INCLUDE_DIR})                #set curl include dir and cxxurl include dir, the "cxxurl" is the dir path of cxxurl_all.h
```

Easy enough ?



# Examples & Usages

You can find all example source in example dir.

## Get

```c++
#include <iostream>
#include <sstream>
#include "cxxurl_all.h"

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream contentOutput;

    RequestBuilder builder;
    builder.url("http://xiaozhuai.github.io")
            .followLocation(true)
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.get();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}
```

That's all you need to perform a get request.

You can simplely download a file just change the `contentOutput` to a `ofstream` instance.

like this

```c++
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
```

And if you need header output, just set it

```c++
#include <iostream>
#include <sstream>
#include "cxxurl_all.h"

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream headerOutput;
    ostringstream contentOutput;

    RequestBuilder builder;
    builder.url("http://xiaozhuai.github.io")
            .followLocation(true)
            .headerOutput(&headerOutput)
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.get();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** HEADER *****************"  << endl << headerOutput.str()   << endl
//         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}
```

## Post

Do a post request maybe something more than get request, but it's still easy

```c++
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
```

CXXUrl provide three form type, `SimpleForm`, `MultipartForm` and `RawForm`.
* SimpleForm ---- just key-values
* MultipartForm ---- key-values and files
* RawForm ---- raw data of request body

## Https

```c++
#include <iostream>
#include <sstream>
#include "cxxurl_all.h"

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream contentOutput;

    RequestBuilder builder;
    builder.url("https://curl.haxx.se")
            .followLocation(true)
            .verifySSL(true)
            .cacert("../cacert.pem")
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.get();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}
```

And you can disable ssl verify on a https website by `.verifySSL(false)`

## Set Headers

Headers usage look like post form

```c++
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
```

Some frequently used headers, such as userAgent and referer, you can simplely set by `.userAgent(...)`, `.referer(...)`

## Cookies

Let's talk about cookies. 

First, we need export cookies to a file when login some website, and then import it if we need visit it after.

Something like this

```c++
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
```

## Plain CURL Api

Yes, if you want to use plain CURL api, here CXXurl provide a method.

look this

```c++
#include <iostream>
#include <sstream>
#include "cxxurl_all.h"

using namespace std;
using namespace CXXUrl;

int main(int argc, char** argv){
    ostringstream contentOutput;

    RequestBuilder builder;
    builder.setCurlOptionString(CURLOPT_URL, "http://xiaozhuai.github.io")
            .followLocation(true)
            .contentOutput(&contentOutput);

    Request& request = builder.build();
    CURLcode res = request.get();

    cout << "***************** CODE *****************"    << endl << res                  << endl
         << "***************** CONTENT *****************" << endl << contentOutput.str()  << endl
         << flush;
}
```

This example is just the same with simple get example.
The deference is use `.setCurlOptionString(CURLOPT_URL, "http://xiaozhuai.github.io")` to take place of `.url("http://xiaozhuai.github.io")`

## RequestBuilder

This just a builder to simplify code. Yes, you can use CXXurl without builder, it's just fine.

```c++
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
```

So, which one do you prefer?

# At last
Thank cURL
