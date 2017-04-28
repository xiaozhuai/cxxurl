//
// Created by xiaozhuai on 17/4/28.
//

#include <string>
#include <iostream>
#include <cxxurl/cxxurl_all.h>
#include "ez_test.h"

using namespace std;
using namespace CXXUrl;

EZ_TEST{
    SimpleForm simpleForm;
    simpleForm.add("aaa", "bbb");
    EZ_ASSERT_EQUAL(string(simpleForm.getData()), string("aaa=bbb"));
}