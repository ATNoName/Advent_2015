#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
vector<string> get_instruction(ifstream* f) {
    vector<string> instructions;
    string line;
    while (getline(*f, line, '\n')) {
        if (!line.empty()) {
            instructions.push_back(line);
        }
    }
    return instructions;
}

void process(unsigned int* a, unsigned int* b, vector<string> instructions) {
    int cur_line = 0;
    while (cur_line < instructions.size()) {
        string instr = instructions[cur_line];
        if (instr.substr(0,3) == "hlf") {
            if (instr.at(4) = 'a') {
                *a = *a >> 1;
            } else {
                *b = *b >> 1;
            }
            cur_line++;
        } else if (instr.substr(0,3) == "tpl") {
            if (instr.at(4) == 'a') {
                *a = *a * 3;
            } else {
                *b = *b * 3;
            }
            cur_line++;
        } else if (instr.substr(0,3) == "inc") {
            if (instr.at(4) == 'a') {
                (*a)++;
            } else {
                (*b)++;
            }
            cur_line++;
        } else if (instr.substr(0,3) == "jmp") {
            int jump = 0;
            bool sign = true; // true if positive, false if negative
            if (instr.at(4) == '-') {
                sign = false;
            }
            jump = stoi(instr.substr(5,instr.size()-4));
            if (!sign) {
                jump = -jump;
            }
            cur_line += jump;
        } else if (instr.substr(0,3) == "jie") {
            unsigned int* operate;
            if (instr.at(4) == 'a') {
                operate = a;
            } else {
                operate = b;
            }
            if (*operate % 2 != 0) {
                cur_line++;
            } else {
                int jump = 0;
                bool sign = true;
                if (instr.at(7) == '-') {
                sign = false;
                }
                jump = stoi(instr.substr(8,instr.size()-7));
                if (!sign) {
                    jump = -jump;
                }
                cur_line += jump;
            }
        } else if (instr.substr(0,3) == "jio") {
            unsigned int* operate;
            if (instr.at(4) == 'a') {
                operate = a;
            } else {
                operate = b;
            }
            if (*operate != 1) {
                cur_line++;
            } else {
                int jump = 0;
                bool sign = true;
                if (instr.at(7) == '-') {
                sign = false;
                }
                jump = stoi(instr.substr(8,instr.size()-7));
                if (!sign) {
                    jump = -jump;
                }
                cur_line += jump;
            }
        }
    }
}

int main() {
    ifstream f;
    f.open("sampleinput.txt");
    vector<string> instructions = get_instruction(&f);
    unsigned int a = 0;
    unsigned int b = 0;
    process(&a, &b, instructions);
    cout << b << '\n';
    a = 1;
    b = 0;
    process(&a, &b, instructions);
    cout << b;
    return 0;
}