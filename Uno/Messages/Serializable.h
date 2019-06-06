//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_SERIALIZABLE_H
#define CURSEN_SERIALIZABLE_H

#include <cstring>

class Serializable {

public:

    static size_t Serialize(char * const buffer, const Serializable& val) {
        return val.serialize(buffer);
    }

    static size_t Serialize(char * const buffer, const int& val) {
        memcpy(buffer, &val, sizeof(int));
        return sizeof(int);
    }

    static size_t Serialize(char * const buffer, const size_t& val) {
        memcpy(buffer, &val, sizeof(size_t));
        return sizeof(size_t);
    }

    static size_t Serialize(char * const buffer, const short& val) {
        memcpy(buffer, &val, sizeof(short));
        return sizeof(short);
    }

    static size_t Serialize(char * const buffer, const float& val) {
        memcpy(buffer, &val, sizeof(float));
        return sizeof(float);
    }

    static size_t Serialize(char * const buffer, const char& val) {
        memcpy(buffer, &val, sizeof(char));
        return sizeof(char);
    }

    static size_t Serialize(char * const buffer, const char* val, const size_t& len) {
        memcpy(buffer, val, sizeof(char) * len);
        return sizeof(char) * len;
    }

    static size_t Deserialize(const char * const buffer, Serializable& val) {
        return val.deserialize(buffer);
    }

    static size_t Deserialize(const char * const buffer, int& val) {
        memcpy(&val, buffer, sizeof(int));
        return sizeof(int);
    }

    static size_t Deserialize(const char * const buffer, size_t& val) {
        memcpy(&val, buffer, sizeof(size_t));
        return sizeof(size_t);
    }

    static size_t Deserialize(const char * const buffer, short& val) {
        memcpy(&val, buffer, sizeof(short));
        return sizeof(short);
    }

    static size_t Deserialize(const char * const buffer, float& val) {
        memcpy(&val, buffer, sizeof(float));
        return sizeof(float);
    }

    static size_t Deserialize(const char * const buffer, char& val) {
        memcpy(&val, buffer, sizeof(char));
        return sizeof(char);
    }

    static size_t Deserialize(const char * const buffer, char* arr, const size_t& len) {
        memcpy(arr, buffer, sizeof(char) * len);
        return sizeof(char) * len;
    }

    /* Default Behaviors */

    virtual size_t serialize(char * const buffer) const {
        // Skip Over VTable.
        size_t len = sizeOf() - sizeof(void*);  // Size of object minus the vtable
        char* p = (char*)this;
        p += sizeof(void*);                     // Hop over vtable
        memcpy(buffer, p, len);                 // Memcpy
        return len;                             // Return bytes written
    };

    virtual size_t deserialize(const char * const buffer) {
        size_t len = sizeOf() - sizeof(void*);
        char* p = (char*)this;
        p += sizeof(void*);
        memcpy(p, buffer, len);
        return len;
    };

    virtual size_t sizeOf() const = 0;

};

#endif //CURSEN_SERIALIZABLE_H
