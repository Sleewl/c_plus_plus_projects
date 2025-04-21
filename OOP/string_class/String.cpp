#include "String.h"
#include <ostream>
#include <cstring>
#include <stdexcept>
#include <iostream>


std::ostream& operator<<(std::ostream& out, const String& str) {
    return (out << str.pointer_);
}

char& String::operator[] (std::size_t pos) {
    if (pos > size_) {
        throw std::out_of_range("Index is out of range");
    }
    return pointer_[pos];
}

const char& String::operator[] (std::size_t pos) const {
    if (pos > size_) {
        throw std::out_of_range("Index is out of range");
    }
    return pointer_[pos];
}

String& String::operator=(const String& str) {
    if (this != &str) {
        String temp(str);
        swap(temp);
    }
    return *this;
}

String& String::operator=(String&& right) noexcept
{
    if (this != &right) {
        swap(right);
        delete[] right.pointer_;
    }
    return *this;
}

void String::swap(String& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(pointer_, other.pointer_);
}

String& String::append(const String& str) {
    char* newPointer = new char[size_ + str.size_ + 1];
    std::strcpy(newPointer, pointer_);
    std::strcat(newPointer, str.pointer_);

    delete[] pointer_;
    pointer_ = newPointer;
    size_ += str.size_;
    capacity_ = size_ + 1;

    return *this;
}

String String::operator+(const String& str) const {
    String result = *this;
    result.append(str);
    return result;
}


    String temp(*this);
    delete[] temp.pointer_;
    std::size_t strLen = std::strlen(str);
    temp.size_ += strLen;
    temp.capacity_ = temp.size_ + 1;
    temp.pointer_ = new char[temp.capacity_] {};
    std::strncat(temp.pointer_, pointer_, pos);
    std::strncat(temp.pointer_, str, strLen);
    std::strncat(temp.pointer_, pointer_ + pos, this->size_ - pos);
    swap(temp);
    return *this;
}

int String::compare(const String& str) const {
    return std::strcmp(pointer_, str.pointer_);
}

