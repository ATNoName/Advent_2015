#include <string>
#include <iostream>
#include <fstream>

using namespace std;
void get_input(ifstream* f, int* row, int* col) {
    int* operate = row;
    string line;
    while (getline(*f, line, ' ')) {
        try {
            if (stoi(line)) {
                *operate = stoi(line);
                if (operate == row) {
                    operate = col;
                } else {
                    return;
                }
            }
        } catch (invalid_argument) {

        }
    }
}

int get_iterations(int row, int col) {
    int iterations = col * (col + 1) / 2;
    int incr = col;
    for (int i = 1;i < row;i++) {
        iterations += incr;
        incr++;
    }
    return iterations;
}

unsigned long long generate_code(int row, int col) {
    unsigned long long code = 20151125;
    int iterations = get_iterations(row, col);
    for (int i = 0;i < iterations-1;i++) {
        code *= 252533;
        code %= 33554393;
    }
    return code;
}

int main() {
    ifstream f;
    f.open("sampleinput.txt");
    int row, col;
    get_input(&f, &row, &col);
    cout << generate_code(row, col);
    return 0;
}