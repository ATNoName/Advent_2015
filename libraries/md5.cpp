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
    MD5(std::string input) {
        this->input = input;
        this->multiple = ceil((input.length() + 56) / 512);
        this->message = (uint8_t*) malloc(512*multiple);
        this->digest = new unsigned int[4];
    }
    void string_to_ascii() {
        this->multiple = this->input.length() >> 6;
        if (this->input != "") {
            for (int i = 0; i < input.length();i++) {
                *(this->message+i) = (int) this->input.at(i);
            }
        }
    }

    void preprocessing() {
        // padding
        for (int i = this->input.length(); i < 56; i++) {
            if (i == this->input.length()) {
                *(message+i) = 0b10000000;
            } else {
                *(message+i) = 0;
            }
        }
        // put the length of the bit into end of the message
        unsigned long long bit_length = this->input.length() << 3;
        for (int i = 0;i < 8;i++) {
            int index = (this->multiple+1)*64 - 8+ i;
            *(message+index) = bit_length & 0xff;
            bit_length = bit_length >> 8;
        }
    }
    unsigned int left_rotate(unsigned int F, unsigned short amount) {
        return (F << amount) | (F >> (32-amount));
    }
    void reverse_endian(unsigned int* n) {
        unsigned int new_n = ((*n & (0xff000000)) >> 24) + ((*n & (0x00ff0000)) >> 8) + ((*n & (0x0000ff00)) << 8) + ((*n & (0x000000ff)) << 24);
        *n = new_n;
    }

    void process() {
        unsigned short s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5,  9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21}; 
        unsigned int K[64];
        for (int i = 0; i < 64;i++) {
            K[i] = floor(pow(2, 32) * abs(sin(i + 1)));
        }
        unsigned int i;

        unsigned int a0 = 0x67452301;
        unsigned int b0 = 0xefcdab89;
        unsigned int c0 = 0x98badcfe;
        unsigned int d0 = 0x10325476;

        for (int o = 0; o < this->multiple+1;o++) {
            unsigned int M[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            for (int j = 0; j < 64;j++) {
                int M_index = j >> 2;
                int mess_index = o*64+j;
                int mess_num = *(message+o*64+j);
                int shift = (4 * (j % 4))*2;
                M[j >> 2] += *(message+o*64+j) << (4 * (j % 4)*2);
            }
            unsigned int A = a0;
            unsigned int B = b0;
            unsigned int C = c0;
            unsigned int D = d0;
            for (i = 0;i < 64;i++) {
                unsigned int F = 0;
                unsigned int g = 0;
                if (i < 16) {
                    F = ((B & C) | ((~B) & D));
                    g = i;
                } else if (i < 32) {
                    F = ((B & D) | (C & (~D)));
                    g = (5*i + 1) % 16;
                } else if (i < 48) {
                    F = (B ^ C ^ D);
                    g = (3*i + 5) % 16;
                } else {
                    F = (C ^ (B | (~D)));
                    g = (7*i) % 16;
                }
                F += A + K[i] + M[g];
                A = D;
                D = C;
                C = B;
                B += left_rotate(F, s[i]);
            }
            a0 += A;
            b0 += B;
            c0 += C;
            d0 += D;
        }
        reverse_endian(&a0);
        reverse_endian(&b0);
        reverse_endian(&c0);
        reverse_endian(&d0);
        /*
        printf("%x\n", a0);
        printf("%x\n", b0);
        printf("%x\n", c0);
        printf("%x\n", d0);
        */
        *this->digest = a0;
        *(this->digest+1) = b0;
        *(this->digest+2) = c0;
        *(this->digest+3) = d0;
    }

    std::string strMD5(std::string input){
        this->input = input;
        int mult = ceil((input.length() + 56) / 512);
        if (this->multiple < mult) {
            if(this->msg_realloc(mult*512)) {
                exit(0);
            }
        }
        this->multiple = mult;
        string_to_ascii();
        preprocessing();
        process();
        return print();
    }

    std::string print() {
        std::stringstream ss;
        std::string output = "";
        for (int i = 0;i < 4;i++) {
            ss << std::setfill('0') << std::setw(8) << std::hex << *(this->digest+i);
            output = output + ss.str();
        }
        return output;
    }

    bool msg_realloc(int multiple) {
        void* temp = realloc(this->message, multiple);
        if (!temp) {
            return false;
        } else {
            this->message = (uint8_t*) temp;
            return true;
        }
    }

    void free_msg() {
        free(this->message);
        free(this->digest);
        delete(this);
    }
};