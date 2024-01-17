#pragma once
#include <string>
#include <iostream>
#include <math.h>
#include <cstdint>
#include <sstream>
#include <iomanip>

class MD5 {
    public:
    std::string input;
    int multiple;
    uint8_t* message;
    unsigned int* digest;
    MD5(std::string input);
    void string_to_ascii();
    void preprocessing();
    unsigned int left_rotate(unsigned int F, unsigned short amount);
    void reverse_endian(unsigned int* n);
    void process();
    std::string strMD5(std::string input);
    std::string print();
    bool msg_realloc();
    void free_msg();  
};