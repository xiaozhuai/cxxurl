//
// Created by xiaozhuai on 17/4/28.
//

#include <string>
#include <iostream>
#include <cxxurl/cxxurl_all.h>
#include "ez_test.h"

using namespace std;
using namespace CXXUrl;

SimpleForm simpleForm;

#define ASSERT_SIMPLE_FORM(a, b)        simpleForm.clear(); EZ_ASSERT_EQUAL(a.getData(), string(b))

EZ_TEST{
    ASSERT_SIMPLE_FORM(
            simpleForm.add("key1", "value1").add("key2", "value2"),
            "key1=value1&key2=value2"
    );
    ASSERT_SIMPLE_FORM(
            simpleForm.add("key1", "值1").add("key2", "值2"),
            "key1=%E5%80%BC1&key2=%E5%80%BC2"
    );
}