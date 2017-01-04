/**
 * @author : xiaozhuai
 * @date   : 17/1/4
 */

#include "Header.h"

namespace CXXUrl {

Header::Header() :
        curlSlist(NULL){

}

Header::~Header() {
    if(curlSlist!=NULL) curl_slist_free_all(curlSlist);
}

void Header::add(string key, string value) {
    headList.push_back(key + ": " + value);
}

void Header::add(string line) {
    headList.push_back(line);
}

struct curl_slist* Header::getHeaders() {
    if(curlSlist!=NULL) curl_slist_free_all(curlSlist);

    for(int i=0; i<headList.size(); i++){
        curlSlist = curl_slist_append(curlSlist, headList[i].c_str());
    }
    return curlSlist;
}

}