//
// Created by xiaozhuai on 17/4/28.
//

#include <cxxurl/cxxurl_all.h>
#include "ez_test.h"

using namespace std;
using namespace CXXUrl;

#define ASSERT_SIMPLE_FORM(a, b)        do{             \
    EZ_ASSERT_EQUAL(string((a).getData()), string(b));  \
    (a).clear();                                        \
}while(0)

EZ_TEST {
    SimpleForm simpleForm;

    ASSERT_SIMPLE_FORM(
            simpleForm.add("key1", "value1").add("key2", "value2"),
            "key1=value1&key2=value2"
    );
    ASSERT_SIMPLE_FORM(
            simpleForm.add("key_a", "值1").add("key_b", "值2"),
            "key_a=%E5%80%BC1&key_b=%E5%80%BC2"
    );
}