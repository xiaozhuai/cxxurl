/**
 * @author : xiaozhuai
 * @date   : 17/1/3
 */

#ifndef CXXURL_RAWFORM_H
#define CXXURL_RAWFORM_H

#include <string>
#include <cstring>
#include "Form.h"

namespace CXXUrl {

using namespace std;

class RawForm : public Form{

    public:
        RawForm() :
                Form(Form::RAW),
                m_RawData(nullptr),
                m_Len(0),
                m_Malloc(false){ }

        ~RawForm() {
            if(m_Malloc && m_RawData!=nullptr) free(m_RawDataMem);
        }

    public:
        RawForm &setRawText(string text, bool malloc_memory=false) {
            this->setRawData(text.data(), text.length(), malloc_memory);
            return *this;
        }

        RawForm &setRawData(const char* data, size_t len, bool malloc_memory=false) {
            m_Len = len;
            if(m_Malloc && m_RawData!=nullptr) free(m_RawDataMem);

            m_Malloc = malloc_memory;
            if(malloc_memory){
                m_RawDataMem = (char*)malloc(m_Len);
                memcpy(m_RawDataMem, data, m_Len);
                m_RawData = m_RawDataMem;
            }else{
                m_RawData = data;
            }

            return *this;
        }

        const char* getData() {
            return m_RawData;
        }

        size_t length() {
            return m_Len;
        }

        void clear() {
            if(m_Malloc && m_RawData!=nullptr) free(m_RawDataMem);
            m_RawData = nullptr;
        }

    protected:
        const char* m_RawData;
        char* m_RawDataMem;
        size_t m_Len;
        bool m_Malloc;


};

}

#endif //CXXURL_RAWFORM_H
