#include <string>
#include <string.h>
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
            while (this->file.good() && *(this->str+pos-1) != stop) {
                *(this->str+pos) = this->file.get();
                (this->pos)++;
            }
            this->pos--;
            *(this->str+pos) = '\0';
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
        }
};

int get_difference(StringParser*s) {
    int strlen = 0;
    int pos = 0;
    char get = s->file.get();
    bool escape = false;
    while (get != '\n') {
        if (!s->file.good()) {
            return 0;
        }
        pos++;
        if (escape) {
            if (get == '\\') {
                strlen++;
            } else if (get == '"') {
                strlen++;
            } else if (get == 'x') {
                strlen -= 1;
            }
            escape = false;
        } else {
            if (get == '\\') {
                escape = true;
            } else if (get == '\"') {
            } else  {
                strlen++;
            }
        }
        get = s->file.get();
    }
    return pos - strlen;
}

int get_difference_reverse(StringParser* s) {
    int codelen = 2;
    int pos = 0;
    char get = s->file.get();
    while (get != '\n') {
        if (!s->file.good()) {
            return 0;
        }
        pos++;
        if (get == '"') {
            codelen += 2;
        } else if (get == '\\') {
            codelen += 2;
        } else {
            codelen++;
        }
        get = s->file.get();
    }
    return codelen - pos;
}

int main() {
    int diff = 0;
    StringParser s = StringParser("input.txt");
    while (s.file.good()) {
        diff += get_difference(&s);
    }
    std::cout << diff << "\n";
    s.reset_file();
    diff = 0;
    while (s.file.good()) {
        diff += get_difference_reverse(&s);
    }
    std::cout << diff << "\n";
    s.free_parse();
    return 0;
}