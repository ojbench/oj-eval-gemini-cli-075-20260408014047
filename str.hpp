#ifndef STR_HPP
#define STR_HPP

#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
    char* data;
    size_t length;

public:
    str() : data(nullptr), length(0) {}

    str(const char &c) : length(1) {
        data = new char[2];
        data[0] = c;
        data[1] = '\0';
    }

    str(const char *&& s_) {
        if (s_) {
            length = std::strlen(s_);
            data = new char[length + 1];
            std::strcpy(data, s_);
        } else {
            length = 0;
            data = nullptr;
        }
    }

    str &operator=(const char *&& s_) {
        if (data) {
            delete[] data;
        }
        if (s_) {
            length = std::strlen(s_);
            data = new char[length + 1];
            std::strcpy(data, s_);
        } else {
            length = 0;
            data = nullptr;
        }
        return *this;
    }

    str(const str &other) {
        length = other.length;
        if (other.data) {
            data = new char[length + 1];
            std::strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    str &operator=(const str &other) {
        if (this != &other) {
            if (data) {
                delete[] data;
            }
            length = other.length;
            if (other.data) {
                data = new char[length + 1];
                std::strcpy(data, other.data);
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    char &operator[](size_t pos) {
        return data[pos];
    }

    const char &operator[](size_t pos) const {
        return data[pos];
    }

    size_t len() const {
        return length;
    }

    str join(const std::vector<str> &strs) const {
        if (strs.empty()) return str();
        size_t total_len = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            total_len += strs[i].len();
        }
        total_len += length * (strs.size() - 1);
        
        char* new_data = new char[total_len + 1];
        size_t current_pos = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            if (strs[i].len() > 0) {
                std::strcpy(new_data + current_pos, strs[i].data);
                current_pos += strs[i].len();
            }
            if (i < strs.size() - 1 && length > 0) {
                std::strcpy(new_data + current_pos, data);
                current_pos += length;
            }
        }
        new_data[total_len] = '\0';
        str result;
        result.data = new_data;
        result.length = total_len;
        return result;
    }

    str slice(size_t l, size_t r) const {
        if (l >= r || l >= length) return str();
        if (r > length) r = length;
        size_t new_len = r - l;
        char* new_data = new char[new_len + 1];
        std::strncpy(new_data, data + l, new_len);
        new_data[new_len] = '\0';
        str result;
        result.data = new_data;
        result.length = new_len;
        return result;
    }

    ~str() {
        if (data) {
            delete[] data;
        }
    }
};

#endif
