#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
class Person {
    public:
    string name;
    vector<string> relation_name;
    vector<int> relation_num;
    Person(string name = "") {
        this->name = name;
    }

    void add_relationship(string name, int num) {
        relation_name.push_back(name);
        relation_num.push_back(num);
    }

    int get_happiness(string name) {
        for (int i = 0;i < this->relation_name.size();i++) {
            if (name == this->relation_name[i]) {
                return relation_num[i];
            }
        }
        return 0;
    }
};

class DiningTable {
    public:
    vector<Person> participants;
    DiningTable() {}

    void build(ifstream* f) {
        string relate1 = "";
        string relate2 = "";
        int happiness = 0;
        bool gain_lose = true;
        for (string line; getline(*f, line, ' ');) {
            relate1 = line;
            getline(*f, line, ' ');
            getline(*f, line, ' ');
            if (line == "gain") {
                gain_lose = true;
            } else {
                gain_lose = false;
            }
            getline(*f, line, ' ');
            happiness = stoi(line);
            if (!gain_lose) {
                happiness = -happiness;
            }
            getline(*f, line, ' ');
            getline(*f, line, ' ');
            getline(*f, line, ' ');
            getline(*f, line, ' ');
            getline(*f, line, ' ');
            getline(*f, line, ' ');
            getline(*f, line, '.');
            relate2 = line;
            bool registered = false;
            Person* ref;
            for (int i = 0;i < this->participants.size();i++) {
                if (this->participants[i].name == relate1) {
                    ref = &this->participants[i];
                    registered = true;
                    break;
                }
            }
            if (!registered) {
                this->participants.push_back(Person(relate1));
                ref = &this->participants.back();
            }
            ref->add_relationship(relate2, happiness);
            getline(*f, line, '\n');
        }
    }

    int calc_happiness(Person* arrangement, int size) {
        int happiness = 0;
        for (int i = 0;i < size;i++) {
            if (i+1 == size) {
                happiness += arrangement[0].get_happiness(arrangement[i].name) + arrangement[i].get_happiness(arrangement[0].name);
            } else {
                happiness += arrangement[i].get_happiness(arrangement[i+1].name) + arrangement[i+1].get_happiness(arrangement[i].name);
            }
        }
        return happiness;
    }

    void optimal_seating(Person* arrangement, int size, int* highest_happiness) {
        if (size == this->participants.size()) {
            if (this->calc_happiness(arrangement, size) > *highest_happiness) {
                *highest_happiness = this->calc_happiness(arrangement, size);
            }
        } else {
            for (int i = 1; i < this->participants.size();i++) {
                bool in_arr = false;
                for (int j = 1; j < size;j++) {
                    if (arrangement[j].name == this->participants[i].name) {
                        in_arr = true;
                        break;
                    }
                }
                if (!in_arr) {
                    arrangement[size] = this->participants[i];
                    optimal_seating(arrangement, size+1, highest_happiness);
                }
            }
        }
    }
    void add_person(string name, string* relation_name, int* relation_num, string* inverse_relation_name, int* inverse_relation_num) {
        int old_size = this->participants.size();
        this->participants.push_back(Person(name));
        Person* new_guy = &this->participants.back();
        copy(&relation_name[0], &relation_name[old_size], back_inserter(new_guy->relation_name));
        copy(&relation_num[0], &relation_num[old_size], back_inserter(new_guy->relation_num));
        for (int i = 0;i < old_size;i++) {
            for (int j = 0;j < old_size;j++) {
                if (this->participants[j].name == inverse_relation_name[i]) {
                    this->participants[j].add_relationship(name, inverse_relation_num[i]);
                    break;
                }
            }
        }
    }
};

int main() {
    ifstream f;
    f.open("input.txt");
    DiningTable table = DiningTable();
    table.build(&f);
    Person* arrangement = new Person[9];
    arrangement[0] = table.participants[0];
    int happiness = 0;
    table.optimal_seating(arrangement, 1, &happiness);
    cout << happiness << '\n';
    string* relation_name = new string[table.participants.size()];
    int* relation_num = new int[table.participants.size()];
    for (int i = 0;i < table.participants.size();i++) {
        relation_name[i] = table.participants[i].name;
        relation_num[i] = 0;
    }
    table.add_person("You", relation_name, relation_num, relation_name, relation_num);
    happiness = 0;
    table.optimal_seating(arrangement, 1, &happiness);
    cout << happiness << '\n';
    return 0;
}