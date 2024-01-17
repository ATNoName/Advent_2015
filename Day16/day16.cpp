#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

map<string, int> in_MFCSAM(ifstream* f) {
    map<string, int> MFCSAM = map<string, int>();
    string line;
    while (getline(*f, line, ':')) {
        string name = line;
        f->get();
        getline(*f, line, '\n');
        int num = stoi(line);
        MFCSAM[name] = num;
    }
    return MFCSAM;
}

int solve(ifstream* f, map<string, int> MFCSAM, map<string, int> compare) {
    string line;
    while (getline(*f, line, ' ')) {
        getline(*f, line, ':');
        int num = stoi(line);
        char check = f->get();
        // get entire line
        getline(*f, line, '\n');
        // check if profile matches MFCSAM
        stringstream profile(line);
        string compound;
        int amount;
        bool matches = true;
        while (getline(profile, compound, ':')) {
            getline(profile, line, ' ');
            getline(profile, line, ',');
            amount = stoi(line);
            // check if profile matches MFCSAM
            switch(compare[compound]) {
                case -1:
                if (MFCSAM[compound] > amount) {
                    getline(profile, line, ' ');
                } else {
                    matches = false;
                }
                break;
                case 0:
                if (MFCSAM[compound] == amount) {
                    getline(profile, line, ' ');
                } else {
                    matches = false;
                }
                break;
                case 1:
                if (MFCSAM[compound] < amount) {
                    getline(profile, line, ' ');
                } else {
                    matches = false;
                }
            }
            if (!matches) {
                break;
            }
        }
        if (matches) {
            return num;
        }
    }
    return -1;
}

int main() {
    ifstream p;
    p.open("MFCSAM.txt");
    map<string, int> MFCSAM = map<string, int>();
    MFCSAM = in_MFCSAM(&p);
    ifstream f;
    f.open("input.txt");
    map<string, int> compare = map<string, int>();
    for(auto i: MFCSAM) {
        compare[i.first] = 0;
    }
    cout << solve(&f, MFCSAM, compare);
    compare["cats"] = 1;
    compare["trees"] = 1;
    compare["pomeranians"] = -1;
    compare["goldfish"] = -1;
    cout << '\n';
    cout << solve(&f, MFCSAM, compare);
    return 0;
}