#ifndef ELEVEN_H
#define ELEVEN_H

#include <cstddef> 
#include <string>
#include <initializer_list>
#include <stdexcept> 

class Eleven {
public:
    Eleven();
    Eleven(const size_t& n, unsigned char t = 0);
    Eleven(const std::initializer_list<unsigned char>& t);
    Eleven(const std::string& t);

    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;

    virtual ~Eleven() noexcept;

    Eleven add(const Eleven& other) const;
    Eleven subtract(const Eleven& other) const;
    Eleven copy() const;

    bool greaterThan(const Eleven& other) const;
    bool lessThan(const Eleven& other) const;
    bool equalTo(const Eleven& other) const;

    std::string toString() const;
    size_t getSize() const;

private:
    unsigned char* digits_;
    size_t size_;

    void normalize(); 
    static bool isValidDigit(unsigned char d); 
};

#endif 