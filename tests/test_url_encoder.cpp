//
// Created by xiaozhuai on 17/4/28.
//

#include <cxxurl/cxxurl_all.h>
#include "ez_test.h"

using namespace std;
using namespace CXXUrl;

#define ASSERT_URL_ENCODE_EQUAL(STR, RES)   EZ_ASSERT_EQUAL(UrlEncoder::encode(STR), string(RES))
#define ASSERT_URL_DECODE_EQUAL(STR, RES)   EZ_ASSERT_EQUAL(UrlEncoder::decode(STR), string(RES))

EZ_TEST {
    ASSERT_URL_ENCODE_EQUAL("aaa", "aaa");
    ASSERT_URL_ENCODE_EQUAL("阿打算打阿斯蒂芬分隔然后", "%E9%98%BF%E6%89%93%E7%AE%97%E6%89%93%E9%98%BF%E6%96%AF%E8%92%82%E8%8A%AC%E5%88%86%E9%9A%94%E7%84%B6%E5%90%8E");

    ASSERT_URL_DECODE_EQUAL("aaa", "aaa");
    ASSERT_URL_DECODE_EQUAL("%E9%98%BF%E6%89%93%E7%AE%97%E6%89%93%E9%98%BF%E6%96%AF%E8%92%82%E8%8A%AC%E5%88%86%E9%9A%94%E7%84%B6%E5%90%8E", "阿打算打阿斯蒂芬分隔然后");
}