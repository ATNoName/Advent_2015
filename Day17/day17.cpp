#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
vector<int> get_container(ifstream* f) {
    vector<int> containers = vector<int>();
    string line;
    while(getline(*f, line, '\n')) {
        containers.push_back(stoi(line));
    }
    return containers;
}

int calc_combination(vector<int> containers, bool* combination) {
    int total = 0;
    for (int i = 0;i < containers.size();i++) {
        total += combination[i] * containers[i];
    }
    return total;
}

void solve(vector<int> containers, bool* combination, int size, int amount, int* num) {
    if (size == containers.size()) {
        if (calc_combination(containers, combination) == amount) {
            (*num)++;
        }
    } else {
        combination[size] = false;
        solve(containers, combination, size+1, amount, num);
        combination[size] = true;
        solve(containers, combination, size+1, amount, num);
    }
}

void solve_minimum(vector<int> containers, bool* combination, int size, int amount, int* minimum, int* num) {
    if (size == containers.size()) {
        if (calc_combination(containers, combination) == amount) {
            int cur_minimum = 0;
            for (int i = 0;i < containers.size();i++) {
                cur_minimum += combination[i];
            }
            if (cur_minimum < *minimum) {
                *minimum = cur_minimum;
                *num = 1;
            } else if (cur_minimum == *minimum) {
                (*num)++;
            }
        }
    } else {
        combination[size] = false;
        solve_minimum(containers, combination, size+1, amount, minimum, num);
        combination[size] = true;
        solve_minimum(containers, combination, size+1, amount, minimum, num);
    }
}

int main() {
    ifstream f;
    f.open("sampleinput.txt");
    int store = 25;
    vector<int> containers = get_container(&f);
    bool* combination = new bool[containers.size()];
    for (int i = 0;i < containers.size();i++) {
        combination[i] = false;
    }
    int num = 0;
    solve(containers, combination, 0, store, &num);
    cout << num << '\n';
    int minimum = INT_MAX;
    num = 0;
    solve_minimum(containers, combination, 0, store, &minimum, &num);
    cout << num;
    return 0;
}