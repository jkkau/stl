#pragma once

#include <string.h>
#include <stdlib.h>

#define SSO_LENGTH 15
// 最后一位是'/0'
#define SSO_DATA_SIZE 16

class String {
public:
    String() : isSSO(true) {
        data.sso_data[0] = '\0';
    }
    String(const char *str) {
        int len = strlen(str);
        if (len <= SSO_LENGTH) {
            isSSO = true;
            memcpy(data.sso_data, str, len+1);
            return;
        }
        isSSO = false;
        data.long_data.size = len;
        data.long_data.data = (char *)malloc(len+1);
        memcpy(data.long_data.data, str, len+1);
    }
    String(const String& other) {
        setData(other);
    }
    String& operator=(const String& other) {
        if (this == &other) {
            return *this;
        }
        this->~String();
        setData(other);
        return *this;
    }

    const char *get() const {
        if (isSSO) {
            return data.sso_data;
        }
        return data.long_data.data;
    }

    ~String() {
        if (!isSSO) {
            free(data.long_data.data);
        }
    }
    bool sso() const {
        return isSSO;
    }
private:
    void setData(const String& other) {
        if (other.sso()) {
            isSSO = true;
            memcpy(data.sso_data, other.get(), strlen(other.get())+1);
            return;
        }
        isSSO = false;
        data.long_data.size = strlen(other.get());
        data.long_data.data = (char *)malloc(data.long_data.size+1);
        memcpy(data.long_data.data, other.get(), data.long_data.size+1);
    }

private:
    union {
        char sso_data[SSO_DATA_SIZE];
        struct {
            int size;
            char *data;
        }long_data;
    }data;
    bool isSSO;
};