//
// Created by xiaozhuai on 17/4/28.
//

#include <string>
#include <iostream>
#include <cxxurl/cxxurl_all.h>
#include "ez_test.h"

using namespace std;
using namespace CXXUrl;

#define ASSERT_URL_ENCODE_EQUAL(STR, RES)   EZ_ASSERT_EQUAL(UrlEncode::encode(STR) , string(RES))

EZ_TEST{
    ASSERT_URL_ENCODE_EQUAL("aaa", "aaa");
}