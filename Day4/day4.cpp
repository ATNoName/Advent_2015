#include <string>
#include <iostream>
#include <math.h>
#include <cstdint>

void string_to_ascii(std::string input, int* multiple, uint8_t* message) {
    *multiple = input.length() >> 6;
    if (input != "") {
        for (int i = 0; i < input.length();i++) {
        *(message+i) = (int) input.at(i);
        }
    }
}

void preprocessing(uint8_t* message, int length, int* multiple) {
    // padding
    for (int i = length; i < 56; i++) {
        if (i == length) {
            *(message+i) = 0b10000000;
        } else {
            *(message+i) = 0;
        }
    }
    // put the length of the bit into end of the message
    unsigned long long bit_length = length << 3;
    for (int i = 0;i < 8;i++) {
        int index = (*multiple+1)*64 - 8+ i;
        *(message+index) = bit_length & 0xff;
        bit_length = bit_length >> 8;
    }
}

unsigned int left_rotate(unsigned int F, unsigned short amount) {
    return (F << amount) | (F >> (32-amount));
}

void ReverseEndian(unsigned int* n) {
    unsigned int new_n = ((*n & (0xff000000)) >> 24) + (((*n & (0x00ff0000)) >> 16) << 8) + (((*n & (0x0000ff00)) >> 8) << 16) + ((*n & (0x000000ff)) << 24);
    *n = new_n;
}

void process(uint8_t* message, int* multiple, unsigned int* digest) {
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

    for (int o = 0; o < *multiple+1;o++) {
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
    ReverseEndian(&a0);
    ReverseEndian(&b0);
    ReverseEndian(&c0);
    ReverseEndian(&d0);
    /*
    printf("%x\n", a0);
    printf("%x\n", b0);
    printf("%x\n", c0);
    printf("%x\n", d0);
    */
    *digest = a0;
    *(digest+1) = b0;
    *(digest+2) = c0;
    *(digest+3) = d0;
}

void strMD5(std::string input, uint8_t* message, unsigned int* digest){
    int multiple = 0;
    int length = input.length();
    string_to_ascii(input, &multiple, message);
    preprocessing(message, length, &multiple);
    process(message, &multiple, digest);
}

int find_hash(std::string input, unsigned int less_than, unsigned int* digest, uint8_t* message) {
    bool found = 0;
    int num = 1;
    int reacc = 0;
    while (!found) {
        std::string md5_input = input + std::to_string(num);
        if (md5_input.length() % 512 == 449) {
            void* temp = realloc(message, reacc*512);
            if (!temp) {
                return 1;
            }
            reacc++;
            message = (uint8_t*) temp;
        }
        strMD5(md5_input, message, digest);
        if (*digest < less_than) {
            found = true;
            break;
        }
        num++;
    }
    return num;
}

int main() {
    std::string input = "0";
    unsigned int* digest = (unsigned int*) malloc(32);
    uint8_t* message = (uint8_t*) malloc(512);
    int reacc = 0;
    std::cout << find_hash(input, 0x00001000, digest, message);
    // part 2
    std::cout << "\n";
    std::cout << find_hash(input, 0x00000100, digest, message);
    free(digest);
    free(message);
   /*
   strMD5("1", message, digest);
   std::cout << *digest;
   */
    return 0;
}