#include <string>
#include <iostream>
#include <fstream>

class StringParser {
    public:
        std::ifstream file;
        char* str;
        int size;
        int pos;

        StringParser(std::string input) {
            this->file.open(input);
            this->str = (char *) malloc(64);
            this->pos = 0;
            this->size = 64;
        }

        void read_until(char stop = '\n') {
            this->pos = 0;
            while (this->file.good() && *(this->str+pos-1 != stop) {
                *(this->str+pos) = this->file.get();
                (this->pos)++;
            }
            *(this->str+pos-1) = '\0';
        }

        int char_to_num(char reference = '0') {
            if ((*(this->str) - reference > 9 || *(this->str) - reference < 0) && reference == '0') {
                return -1;
            }
            int num = 0;
            int power = 1;
            while (this->pos > 0) {
                num += (*(this->str+this->pos-1) - reference) * power;
                power *= 10;
                pos--;
            }
            return num;
        }

        bool realloc_string() {
            void* temp = realloc(this->str, size*2);
            if (!temp) {
                return false;
            } else {
                this->str = (char *) temp;
                return true;
            }
        }

        void reset_file() {
            this->file.clear();
            this->file.seekg(0);
        }

        void free_parse() {
            free(this->str);
            this->file.close();
            delete(this);
        }
};