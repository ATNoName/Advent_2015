#pragma once
#include <string>
#include <iostream>
#include <fstream>

class StringParser {
    
    public:
        std::ifstream file;
        char* str;
        int size;
        int pos;

        StringParser(std::string input);
        void read_until(char stop);
        int char_to_num(char reference);
        bool realloc_string();
        void reset_file();
        void free_parse();
};