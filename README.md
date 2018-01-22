# CXXCurl

[[English README](README.md)] [[中文说明](README_CN.md)]

CXXUrl is base on libcurl, but it's not only an object-oriented C++ wrapper for cURL.

Now, CXXUrl is header-only!

By the way, if you want to known more about libcurl, you should go [http://curl.haxx.se/](http://curl.haxx.se/)

Under [MIT LICENSE](LICENSE)

author: xiaozhuai - [xiaozhuai7@gmail.com](xiaozhuai7@gmail.com)

# Build

First, clone with submodule
```bash
$ git clone --recursive https://github.com/xiaozhuai/cxxurl
```

If you already clone it, but without submodules, you can do this

```bash
$ cd /path/to/cxxurl
$ git submodule update --init --recursive
```

Now, build examples and tests with cmake

```bash
$ cd /path/to/cxxurl
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Run Example

Once you have build the project, you can run some examples.

```bash
$ ../example_server/start_server # Run a http server for examples, require php > 5.6
$ ./example_get
```

# Install

Just drop files in `src/cxxurl` to where you like!

# Examples & Usages

You can find all example source in example dir.

## Get

See [examples/example_get.cpp](examples/example_get.cpp)

That's all you need to perform a get request.

And you can parse body, we provide a json parser.

See [examples/example_parse_json_body.cpp](examples/example_parse_json_body.cpp)

Thank [https://github.com/nlohmann/json](https://github.com/nlohmann/json), a modern json parser for c++.

You can simplely download a file just change the `contentOutput` to a `ofstream` instance.

See [examples/example_download.cpp](examples/example_download.cpp)

And if you need header output, just set it

See [examples/example_response_header.cpp](examples/example_response_header.cpp)

Of course, we also provide a parser

See [examples/example_parse_response_header.cpp](examples/example_parse_response_header.cpp)

## Post

Do a post request maybe something more than get request, but it's still easy

See [examples/example_post.cpp](examples/example_post.cpp)

CXXUrl provide three form type, `SimpleForm`, `MultipartForm` and `RawRequestBody`.
* SimpleForm ---- just key-values (application/x-www-form-urlencoded)
* MultipartForm ---- key-values and files (multipart/form-data)
* RawRequestBody ---- raw data of request body (raw request body)

## Https

See [examples/example_get_https_enable.cpp](examples/example_get_https_enable.cpp)

And you can disable ssl verify on a https website by `.verifySSL(false)`

See [examples/example_get_https_disable.cpp](examples/example_get_https_disable.cpp)

## Set Headers

Headers usage look like post form

See [examples/example_set_request_header.cpp](examples/example_set_request_header.cpp)

Some frequently used headers, such as userAgent and referer, you can simplely set by `.userAgent(...)`, `.referer(...)`

## Cookies

Let's talk about cookies. 

First, we need export cookies to a file when login some website, and then import it if we need visit it after.

See [examples/example_cookie.cpp](examples/example_cookie.cpp)

## Plain CURL Api

Yes, if you want to use plain CURL api, here CXXurl provide a method.

See [examples/example_use_curl_option.cpp](examples/example_use_curl_option.cpp)

This example is just the same with simple get example.
The deference is use `.curlOptionString(CURLOPT_URL, "http://xiaozhuai.github.io")` to take place of `.url("http://xiaozhuai.github.io")`

## RequestBuilder

This just a builder to simplify code. Yes, you can use CXXurl without builder, it's just fine.

See [examples/example_without_request_builder.cpp](examples/example_without_request_builder.cpp)

So, which one do you prefer?

# At last
Thank cURL
