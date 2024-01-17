#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
class Operation {
    public:
    string reactant;
    string product;
    Operation(string reactant = "", string product = "") {
        this->reactant = reactant;
        this->product = product;
    }

    string convert(string formula, int pos) {
        if (formula.substr(pos, this->reactant.size()) != this->reactant) {
            cout << "Error: Reactant didn't match, Formula: " << formula << " Required: " << this->reactant;
            exit(1);
        }
        return formula.substr(0, pos) + this->product + formula.substr(pos+this->reactant.size(), formula.size() - pos - reactant.size());
    }

    string reverse_convert(string formula, int pos) {
        if (formula.substr(pos, this->product.size()) != this->product) {
            cout << "Error: Product didn't match, Formula: " << formula << " Required: " << this->product;
            exit(1);
        }
        return formula.substr(0, pos) + this->reactant + formula.substr(pos+this->product.size(), formula.size() - pos - product.size());
    }
};

vector<Operation> parse(ifstream* f, string* formula) {
    string line;
    vector<Operation> operations = vector<Operation>();
    while (getline(*f, line, '\n')) {
        if (line.empty()) {
            break;
        } else {
            stringstream s(line);
            string reactant;
            string product;
            getline(s, reactant, ' ');
            getline(s, line, ' ');
            getline(s, product, '\n');
            operations.push_back(Operation(reactant, product));
        }
    }
    getline(*f, *formula, '\n');
    return operations;
}

int solve_part1(vector<Operation> operations, string formula) {
    vector<string> new_formulas = vector<string>();
    int count;
    for (Operation op: operations) {
        for (int i = 0;i < formula.size();i++) {
            if (formula.substr(i, op.reactant.size()) == op.reactant) {
                if (find(new_formulas.begin(), new_formulas.end(), op.convert(formula, i)) == new_formulas.end()) {
                    new_formulas.push_back(op.convert(formula, i));
                    count += 1;
                }
            }
        }
    }
    return count;
}

int solve_part2(vector<Operation> operations, string start, string end) {
    // Start from the end and work your way to beginning backwards.
    // Note: exploit very specific features about the operation list such as 1. no common output and 2. the algorithm does formula reduction only.
    // If the operations fits either one, it may not work.
    string cur_formula = end;
    int step = 1;
    while (step < 500) { // prevent infinite loop
        for (Operation op: operations) {
            for (int i = 0;i < cur_formula.size();i++) {
                if (cur_formula.substr(i, op.product.size()) == op.product) {
                    cur_formula = op.reverse_convert(cur_formula, i);
                    if (cur_formula == start) {
                        return step;
                    }
                    step++;
                }
            }
        }
    }
    return step;
}

int main() {
    ifstream f;
    f.open("sampleinput.txt");
    string formula = "";
    vector<Operation> operations = parse(&f, &formula);
    cout << solve_part1(operations, formula) << '\n';
    cout << solve_part2(operations, "e", formula);
    return 0;
}