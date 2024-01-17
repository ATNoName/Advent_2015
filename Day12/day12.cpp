#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int extract_num(std::ifstream* f) {
    std::string s = "";
    char c = f->get();
    while (f->good() && !(c == '-' || (c >= '0' && c <= '9'))) {
        c = f->get();
    }
    if (c == EOF) {
        return 0;
    }
    s += c;
    c = f->get();
    while (c == '-' || (c >= '0' && c <= '9')) {
        s += c;
        c = f->get();
    }
    return stoi(s);
}

bool ignore_red(std::vector<int> array_level, std::vector<int> red_level, int level) {
    if (!red_level.empty() && array_level.empty()) {}
    return false;
}

int extract_sum(std::ifstream* f) {
    bool has_red = false;
    int sum = 0;
    std::string s;
    char c = f->get();
    while (f->good()) {
        if (c == '{') {
            sum += extract_sum(f);
        }
        if (c == '[') {
            sum += extract_sum(f);
        }
        if (c == ']') {
            return sum;
        }
        if (c == '}') {
            if (has_red) {
                return 0;
            } else {
                return sum;
            }
        }
        if (c == '"') {
            s = "";
            c = f->get();
            while (c != '"') {
                s += c;
                c = f->get();
            }
            if (s == "red") {
                has_red = true;
            }
        }
        if (c == '-' || (c >= '0' && c <= '9')) {
            s = "";
            while (c == '-' || (c >= '0' && c <= '9')) {
                s += c;
                c = f->get();
            }
            sum += stoi(s);
            if (c == ']') {
                return sum;
            }
            if (c == '}') {
                if (has_red) {
                    return 0;
                } else {
                    return sum;
                }
            }
        }
        c = f->get();
    }
    return sum;
}

int main() {
    std::ifstream f;
    f.open("sampleinput.json");
    int sum = 0;
    while (f.good()) {
        sum += extract_num(&f);
    }
    std::cout << sum << '\n';
    f.clear();
    f.seekg(0);
    char c = f.get();
    sum = extract_sum(&f);
    std::cout << sum;
    return 0;
}