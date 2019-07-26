//
// Created by Brandon Martin on 6/6/19.
//

#ifndef CURSEN_SERIALIZABLE_H
#define CURSEN_SERIALIZABLE_H

#include <cstring>
#include <string>

class Serializable {

public:

    static size_t Serialize(char * const buffer, const Serializable& val) {
        return val.serialize(buffer);
    }

    static size_t Serialize(char * const buffer, const int& val) {
        memcpy(buffer, &val, sizeof(int));
        return sizeof(int);
    }

    static size_t Serialize(char * const buffer, const bool& val) {
        memcpy(buffer, &val, sizeof(bool));
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

    static size_t Serialize(char * const buffer, const std::string& str)
    {
        auto len = str.length();
        memcpy(buffer, &len, sizeof(len));
        return Serialize(buffer + sizeof(len), str.c_str(), len) + sizeof(len);
    }

    static size_t Deserialize(const char * const buffer, Serializable& val) {
        return val.deserialize(buffer);
    }

    static size_t Deserialize(const char * const buffer, int& val) {
        memcpy(&val, buffer, sizeof(int));
        return sizeof(int);
    }

    static size_t Deserialize(const char * const buffer, bool& val) {
        memcpy(&val, buffer, sizeof(bool));
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

    static size_t DeserializeArray(const char * const buffer, char*& arr, const size_t& len) {
        arr = new char[len + 1];
        memcpy(arr, buffer, sizeof(char) * len);
        arr[len] = '\0';
        return sizeof(char) * len;
    }

    static size_t Deserialize(const char* const buffer, std::string& str)
    {
        size_t len;

        size_t read = Deserialize(buffer, len);

        char raw[len];
        read += Deserialize(buffer + read, raw, len);
        raw[len] = '\0';
        str = std::string(raw);

        return read;
    }

    /* Default Behaviors */

    virtual size_t serialize(char * const buffer) const = 0;
    virtual size_t deserialize(const char * const buffer) = 0;
    virtual size_t sizeOf() const = 0;

};

#endif //CURSEN_SERIALIZABLE_H
