//
// Created by xiaozhuai on 17/4/28.
//

#include <cxxurl/cxxurl_all.h>
#include "ez_test.h"

using namespace std;
using namespace CXXUrl;


template<typename T>
vector<T> toVector(initializer_list<T> args) {
    vector<T> list;
    for(auto& i : args) list.push_back(i);
    return list;
}

EZ_TEST {
    /**
     * test ltrim rtrim trim
     */
    EZ_ASSERT_EQUAL(
            StringUtils::ltrim("\r \n \t aaa\r \n \t "),
            "aaa\r \n \t "
    );
    EZ_ASSERT_EQUAL(
            StringUtils::rtrim("\r \n \t aaa\r \n \t "),
            "\r \n \t aaa"
    );
    EZ_ASSERT_EQUAL(
            StringUtils::trim("\r \n \t aaa\r \n \t "),
            "aaa"
    );
    EZ_ASSERT_EQUAL(
            StringUtils::ltrim("1242342342aaa3453476453453", "1234567890"),
            "aaa3453476453453"
    );
    EZ_ASSERT_EQUAL(
            StringUtils::rtrim("1242342342aaa3453476453453", "1234567890"),
            "1242342342aaa"
    );
    EZ_ASSERT_EQUAL(
            StringUtils::trim("1242342342aaa3453476453453", "1234567890"),
            "aaa"
    );


    /**
     * test explode
     */
    EZ_ASSERT_EQUAL(
            StringUtils::explode("abc", "123abc456abc789abc"),
            toVector<string>({"123", "456", "789", ""})
    );
    EZ_ASSERT_EQUAL(
            StringUtils::explode("abc", "123abc456abc789abc", 3),
            toVector<string>({"123", "456", "789abc"})
    );


    /**
     * test replace
     */
    EZ_ASSERT_EQUAL(
            StringUtils::replace("98dasdhuasdhabcadasdsdadsa", "abc", "!!!!!!!!"),
            "98dasdhuasdh!!!!!!!!adasdsdadsa"
    );

}