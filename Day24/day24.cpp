#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
vector<int> read_data(ifstream* f, int* sum) {
    vector<int> packages;
    string line;
    while(getline(*f, line, '\n')) {
        if (!line.empty()) {
            packages.push_back(stoi(line));
            *sum += stoi(line);
        }
    }
    return packages;
}

void subset_sum(vector<int> packages, vector<bool> stored, int sum, int weight, int index, int* min_count, unsigned long long* min_quantum_entanglement) {
    if (index == packages.size()) {
        if (weight == sum) {
            int count = 0;
            unsigned long long quantum_entanglement = 0;
            for (int i = 0;i < packages.size();i++) {
                if (stored[i] == true) {
                    count++;
                    weight += packages[i];
                    if (quantum_entanglement == 0) {
                        quantum_entanglement = packages[i];
                    } else {
                        quantum_entanglement *= packages[i];
                    }
                }
            }
            if (count < *min_count) {
                *min_count = count;
                *min_quantum_entanglement = quantum_entanglement;
            } else if (count == *min_count) {
                if (*min_quantum_entanglement > quantum_entanglement) {
                    *min_count = count;
                    *min_quantum_entanglement = quantum_entanglement;
                }
            }
        }
    } else {
        if (weight < sum) { // no point in exploring any combination above sum
            stored[index] = true;
            subset_sum(packages,stored, sum, weight+packages[index], index+1, min_count, min_quantum_entanglement);
            stored[index] = false;
            subset_sum(packages,stored, sum, weight, index+1, min_count, min_quantum_entanglement);
        }
    }
}

int main() {
    ifstream f;
    f.open("sampleinput.txt");
    int sum = 0;
    vector<int> packages = read_data(&f, &sum);
    sum /= 3;
    vector<bool> stored = vector<bool>();
    for (int i = 0;i < packages.size();i++) {
        stored.push_back(false);
    }
    int min_count = INT_MAX;
    unsigned long long min_quantum_entanglement = ULLONG_MAX;
    subset_sum(packages, stored, sum, 0, 0, &min_count, &min_quantum_entanglement);
    cout << min_quantum_entanglement << '\n';
    min_count = INT_MAX;
    min_quantum_entanglement = ULLONG_MAX;
    sum = sum * 3 / 4;
    subset_sum(packages, stored, sum, 0, 0, &min_count, &min_quantum_entanglement);
    cout << min_quantum_entanglement;
    return 0;
}