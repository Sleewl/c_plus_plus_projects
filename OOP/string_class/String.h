//#ifndef String_h
//#define String_h
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>

#include <cstddef>

#include <iosfwd>

class String
{
private:
    std::size_t size_;
    std::size_t capacity_;
    char* pointer_;
public:
    String() :
        size_(0),
        capacity_(1),
        pointer_(new char[1] {})
    {}

    String(const char* str) :
        size_(std::strlen(str))
    {
        capacity_ = size_ + 1;
        pointer_ = new char[capacity_];
        std::strcpy(pointer_, str);

    }

    String(const String& str) :
        size_(str.size_),
        capacity_(str.size_ + 1),
        pointer_(new char[str.size_ + 1])
    {
        std::strcpy(pointer_, str.pointer_);
    }

    String(String&& str) noexcept :
        size_(str.size_),
        capacity_(str.size_ + 1)
    {
        pointer_ = new char[capacity_] {};
        std::strcpy(pointer_, str.pointer_);
    }

    ~String()
    {
        delete[] pointer_;
    }

    friend std::ostream& operator<<(std::ostream& out, const String& str);

    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;

    String& operator=(const String& str);
    String& operator=(String&& right) noexcept;

    String operator+(const String& str) const;

    String& insert(std::size_t pos, const char* str);
    String& append(const String& str);
    void swap(String& other) noexcept;
    int compare(const String& str) const;

};


//#endif /* String_hpp */
