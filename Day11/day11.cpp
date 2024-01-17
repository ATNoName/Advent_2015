#include <string.h>
#include <iostream>

void increment(char* password, int length) {
    int pos = length-1;
    while (pos >= 0) {
        if (password[pos] == 'z') {
        password[pos] = 'a';
        pos--;
        } else {
            password[pos]++;
            break;
        }
    }
}

bool straight_letter(char* pass, int length) {
    int count = 0;
    char prev_letter = pass[0];
    for (int i = 1;i < length;i++) {
        if (pass[i] == prev_letter + 1) {
            count++;
            if (count == 2) {
                return true;
            }
        } else {
            count = 0;
        }
        prev_letter = pass[i];
    }
    return false;
}

bool no_contain(char* pass, int length) {
    for (int i = 0;i < length;i++) {
        if (pass[i] == 'i' || pass[i] == 'o' || pass[i] == 'l') {
            return false;
        }
    }
    return true;
}

bool double_letter(char* pass, int length) {
    int count = 0;
    char prev_letter = pass[0];
    for (int i = 1;i < length;i++) {
        if (pass[i] == prev_letter) {
            count++;
            if (count == 2) {
                return true;
            }
            i++;
        }
        prev_letter = pass[i];
    }
    return false;
}

char* new_pass(char* pass, int length, bool (**req) (char*, int), int func_num) {
    bool success = false;
    while(!success) {
        increment(pass, length);
        success = true;
        for (int i = 0;i < func_num;i++) {
            if (!(*req[i])(pass, length)) {
                success = false;
                break;
            }
        }
    }
    return pass;
}

int main() {
    char input[8] = {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'};
    int length = strlen(input) - 1;
    bool (*req[])(char*, int) = {straight_letter, no_contain, double_letter};
    int func_num = 3;
    std::cout << new_pass(input, length, req, func_num) << '\n';
    std::cout << new_pass(input, length, req, func_num);
    return 0;
}