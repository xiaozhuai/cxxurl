/*
 * Created by xiaozhuai on 17/4/28.
 * Email xiaozhuai7@gmail.com
 *
 * MIT License
 *
 * Copyright (c) 2017 xiaozhuai, Weihang Ding
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef EZ_TEST_H
#define EZ_TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define EZ_ASSERT(X)                    do{                                                         \
    __caseCount__ ++;                                                                               \
    if(!(X)) {                                                                                      \
        fprintf(stderr, "[%d] EZTest Failed %s:%d %s\n", __caseCount__, __FILE__, __LINE__, #X);    \
        fflush(stderr);                                                                             \
        __hasErr__ = true;                                                                          \
    }else{                                                                                          \
        fprintf(stdout, "[%d] Passed\n", __caseCount__);                                            \
        fflush(stdout);                                                                             \
    }                                                                                               \
}while(0)

#define EZ_ASSERT_EQUAL(a, b)           EZ_ASSERT((a)==(b))

#define EZ_ASSERT_NOT_EQUAL(a, b)       EZ_ASSERT((a)!=(b))

#define EZ_TEST                         \
bool __hasErr__ = false;                \
int __caseCount__=0;                    \
void __run_tests__();                   \
int main(){                             \
    __run_tests__();                    \
    return __hasErr__ ? 1 : 0;          \
}                                       \
void __run_tests__()

#endif //EZ_TEST_H
