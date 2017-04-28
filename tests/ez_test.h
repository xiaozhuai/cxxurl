//
// Created by xiaozhuai on 17/4/28.
//

#ifndef EZ_TEST_H
#define EZ_TEST_H

#include <stdio.h>
#include <stdlib.h>

#define EZ_ASSERT(X)                                                                                \
        if(!(X)) {                                                                                  \
            printf("EZTest Failed %s:%d %s\n", __FILE__, __LINE__, #X);                             \
            exit(1);                                                                                \
        }

#define EZ_ASSERT_EQUAL(a, b)                                                                       \
        EZ_ASSERT(((a)==(b)))

#define EZ_ASSERT_NOT_EQUAL(a, b)                                                                   \
        EZ_ASSERT(((a)!=(b)))

#define EZ_TEST                                                                                     \
        int main()

#endif //EZ_TEST_H
