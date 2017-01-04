/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include "../include/Header.h"

namespace CXXUrl {

Header::Header() :
        curlSlist(NULL){

}

Header::~Header() {
    if(curlSlist!=NULL) curl_slist_free_all(list);
}

void Header::add(string key, string value) {
    headList.insert(key + ": " + value);
}

void Header::add(string line) {
    headList.insert(line);
}

struct curl_slist* Header::getHeaders() {
    if(curlSlist!=NULL) curl_slist_free_all(list);

    for(int i=0; i<headList.size(); i++){
        curlSlist = curl_slist_append(curlSlist, headList[i]);
    }
    return curlSlist;
}

}