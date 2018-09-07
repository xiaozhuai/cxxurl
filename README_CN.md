# CXXCurl

[[English README](README.md)] [[中文说明](README_CN.md)]

CXXUrl 是基于libcurl的c++库，但它不仅仅只是一个curl的面向对象的c++封装

最新版本的CXXUrl将只包含头文件

如果你想了解更多关于curl的信息，访问 [http://curl.haxx.se/](http://curl.haxx.se/)

Under [MIT LICENSE](LICENSE)

作者：xiaozhuai - [xiaozhuai7@gmail.com](xiaozhuai7@gmail.com)

# 构建

使用cmake构建项目

```bash
$ cd /path/to/cxxurl
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make check # 运行测试用例
```

# 运行示例

构建完成后，你就可以运行一些示例了

```bash
$ ../example_server/start_server # 为运行示例开启一个http服务, 需要 php > 5.6
$ ./example_get
```

# 安装

直接将 `src/cxxurl` 中的文件复制到你需要的地方！

# 例子和用法

你可以在example目录下找到所有例子的源码

## Get

See [examples/example_get.cpp](examples/example_get.cpp)

要发起一个get请求并获取输出，这是所有你需要做的事情


至于解析body，我们提供了一个json解析器

See [examples/example_parse_json_body.cpp](examples/example_parse_json_body.cpp)

感谢 [https://github.com/nlohmann/json](https://github.com/nlohmann/json)

你可以简单的将 `contentOutput` 改为一个 `ofstream` 类的实例就可以完成下载的功能.

See [examples/example_download.cpp](examples/example_download.cpp)

如果你需要响应头的输出

See [examples/example_response_header.cpp](examples/example_response_header.cpp)

当然，我们还提供了一个解析器

See [examples/example_parse_response_header.cpp](examples/example_parse_response_header.cpp)

## Post

发起一个post请求或许比get要复杂一些，但仍然是一件非常简单的事情

See [examples/example_post.cpp](examples/example_post.cpp)

CXXUrl 提供了三者form类型 `SimpleForm`, `MultipartForm` 和 `RawRequestBody`.
* SimpleForm ---- 仅仅是键值对 (application/x-www-form-urlencoded)
* MultipartForm ---- 文件和键值对 (multipart/form-data)
* RawRequestBody ---- 二进制数据 (raw request body)

## Https

See [examples/example_get_https_enable.cpp](examples/example_get_https_enable.cpp)

对于某些网站，你也可以关闭ssl验证，像这样 `.verifySSL(false)`

See [examples/example_get_https_disable.cpp](examples/example_get_https_disable.cpp)

## 设置Request Headers

设置Request Headers用法类似于form

See [examples/example_set_request_header.cpp](examples/example_set_request_header.cpp)

对于一些常用的header, 例如userAgent、 referer等，你可以通过这些方法设置 `.userAgent(...)`, `.referer(...)`

## Cookies

再来说说cookie

假设一种情景，我们需要登录一个网站，把登录成功的cookie保存到一个文件，然后下次访问的时候带上这个cookie

See [examples/example_cookie.cpp](examples/example_cookie.cpp)

## 原生CURL选项

如果你想要使用原生的CURL选项

See [examples/example_use_curl_option.cpp](examples/example_use_curl_option.cpp)

这个例子和第一个例子(get)是完全等效的，
不同之处是使用了 `.curlOptionString(CURLOPT_URL, "http://xiaozhuai.github.io")` 来替代 `.url("http://xiaozhuai.github.io")`

## RequestBuilder

RequestBuilder正如它的名字，仅仅是个builder，它只是为了简化代码，你完全可以不使用它

See [examples/example_without_request_builder.cpp](examples/example_without_request_builder.cpp)

那么你喜欢哪种方式呢？

# 最后
感谢cURL
