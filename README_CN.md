# CXXCurl

[[English README](README.md)] [[中文说明](README_CN.md)]

CXXUrl 是基于libcurl的c++库，但它不仅仅只是一个curl的面向对象的c++封装

如果你想了解更多关于curl的信息，访问 [http://curl.haxx.se/](http://curl.haxx.se/)

Under [MIT LICENSE](LICENSE)

作者：xiaozhuai - [xiaozhuai7@gmail.com](xiaozhuai7@gmail.com)

# 构建

执行下面的命令

```bash
$ cd /path/to/cxxurl
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE = Release # or Debug
$ make
```

# 运行示例

构建完成后，你就可以运行一些示例了

```bash
$ ./example_get
```

# 安装

```bash
$ make install # or with sudo
```

# 例子和用法

你可以在example目录下找到所有例子的源码

## Get

```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

要发起一个get请求并获取输出，这是所有你需要做的事情

你可以简单的将 `contentOutput` 改为一个 `ofstream` 类的实例就可以完成下载的功能.

像这样

```c++
#include <iostream>
#include <sstream>
#include <fstream>
#include <cxxurl/cxxurl_all.h>

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

如果你需要响应头的输出，可以这样

```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

发起一个post请求或许比get要复杂一些，但仍然是一件非常简单的事情

```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

CXXUrl 提供了三者form类型 `SimpleForm`, `MultipartForm` 和 `RawForm`.
* SimpleForm ---- 仅仅是键值对 (x-www-form-urlencoded)
* MultipartForm ---- 文件和键值对 (multipart form data)
* RawForm ---- 二进制数据 (raw request body)

## Https

```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

对于某些网站，你也可以关闭ssl验证，像这样 `.verifySSL(false)`

## 设置Request Headers

设置Request Headers用法类似于form

```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

对于一些常用的header, 例如userAgent、 referer等，你可以通过这些方法设置 `.userAgent(...)`, `.referer(...)`

## Cookies

再来说说cookie

假设一种情景，我们需要登录一个网站，把登录成功的cookie保存到一个文件，然后下次访问的时候带上这个cookie

完成这个过程，只需要这样

```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

## 原生CURL选项

如果你想要使用原生的CURL选项，看这里


```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

这个例子和第一个例子(get)是完全等效的，
不同之处是使用了 `.setCurlOptionString(CURLOPT_URL, "http://xiaozhuai.github.io")` 来替代 `.url("http://xiaozhuai.github.io")`

## RequestBuilder

RequestBuilder正如它的名字，仅仅是个builder，它只是为了简化代码，你完全可以不使用它，就像这样

```c++
#include <iostream>
#include <sstream>
#include <cxxurl/cxxurl_all.h>

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

那么你喜欢哪种方式呢？

# 最后
感谢cURL
