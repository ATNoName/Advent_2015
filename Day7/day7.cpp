#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class StringParser {
    public:
        std::ifstream file;
        std::string str;

        StringParser(std::string input) {
            this->file.open(input);
            this->str = "";
        }

        void read_until(char stop = '\n') {
            str = (char) this->file.get();
            while (this->file.good() && this->str.at(str.length()-1) != stop) {
                this->str = this->str + (char) this->file.get();
            }
            this->str.erase(this->str.length() - 1);
        }

        int char_to_num(char reference = '0') {
            if (((str.at(0) - reference > 9 || str.at(0) - reference < 0) && reference == '0')) {
                return -1;
            }
            int num = 0;
            int power = 1;
            int index = str.length() - 1;
            while (index >= 0) {
                num += (str.at(index) - reference) * power;
                power *= 10;
                index--;
            }
            return num;
        }

        void reset_file() {
            this->file.clear();
            this->file.seekg(0);
        }

        void free_parse() {
            this->file.close();
            delete(this);
        }
};

class Circuit;

class Wire {
    public:
    std::string derive;
    std::string id;
    unsigned short signal;
    bool has_signal;
    Wire(std::string id = "") {
        this->derive = "";
        this->id = id;
        this->signal = 0;
        this->has_signal = false;
    }

    unsigned short solve(Circuit* c);
    int operator==(Wire other){
        return this->id == other.id;
    }

    bool operator<(Wire other) {
        return this->id < other.id;
    }

    bool operator<(const Wire& other) const {
        return this->id < other.id;
    }

    bool operator>(const Wire& other) const {
        return this->id > other.id;
    }
};

class Circuit {
    public:
    std::vector<Wire> wire_set;
    Circuit() {
        this->wire_set = std::vector<Wire>();
    }

    void insert(Wire w) { // Ordered insert
        wire_set.insert(std::upper_bound(wire_set.begin(), wire_set.end(), w), w);
    }

    Wire* search(Wire w) {
        auto find = std::lower_bound(wire_set.begin(), wire_set.end(), w);
        if (find != wire_set.end()) {
            return &wire_set.at(find - wire_set.begin());
        } else {
            return nullptr;
        }
    }

    void build(StringParser* s) {
        while (s->file.good()) {
            this->read_line(s);
        }
    }
    // Build helper functions

    void read_line(StringParser* s) {
        s->read_until('-');
        if (!s->file.good()) {
            return;
        }
        std::string derive = s->str;
        derive.erase(derive.length()-1);
        s->read_until(' ');
        s->read_until('\n');
        Wire wire = Wire(s->str);
        wire.derive = derive;
        this->insert(wire);
    }

    unsigned short get_signal(Wire w) {
        Wire* wire = this->search(w);
        return wire->solve(this);
    }

    void override_derive(Wire w, std::string derive) {
        Wire* find = this->search(w);
        if (find) {
            find->derive = derive;
        }
    }

    void reset() {
        for (int i = 0;i < this->wire_set.size();i++) {
            Wire* elem = &this->wire_set.at(i);
            elem->has_signal = false;
            elem->signal = 0;
        }
    }
};

bool is_num(std::string str) {
    bool is_num = true;
    for (char c: str) {
        if (!isdigit(c)) {
            is_num = false;
            break;
        }   
    }
    return is_num;
}


unsigned short Wire::solve(Circuit* c) {
    // base case
    if (this->has_signal) {
        return this->signal;
    }
    if (is_num(this->derive)) {
        this->signal = (unsigned short) stoi(this->derive);
        this->has_signal = true;
        return this->signal;
    }
    // recursive step
    if (derive.length() < 3) { // just a wire
        Wire* src = c->search(Wire(derive));
        this->signal = src->solve(c);
        this->has_signal = true;
        return this->signal;
    }
    // check if theres a not operator
    if (derive.substr(0, 3) == "NOT") {
        if (is_num(this->derive.substr(4))) {
            this->signal = ~(unsigned short)stoi(derive.substr(4));
        } else {
            Wire* src = c->search(Wire(derive.substr(4)));
            this->signal = ~src->solve(c);
        }
        this->has_signal = true;
        return this->signal;
    }
    // dual operators
    int index = derive.find(' ');
    if (is_num(this->derive.substr(0, index))) {
        this->signal = (unsigned short) std::stoi(this->derive.substr(0, index));
    } else {
        Wire* src1 = c->search(Wire(this->derive.substr(0, index)));
        this->signal = src1->solve(c);
    }

    if (derive.substr(index+1, 3) == "AND") {
        index = derive.find(' ', index+1);
        if (is_num(this->derive.substr(index+1))) {
            unsigned short src2 = (unsigned short) std::stoi(this->derive.substr(index+1));
            this->signal = this->signal & src2;
        } else {
            Wire* src2 = c->search(Wire(derive.substr(index+1)));
            this->signal = this->signal & src2->solve(c);
        }
    }
    // or operator
    if (derive.substr(index+1, 2) == "OR") {
        index = derive.find(' ', index+1);
        if (is_num(this->derive.substr(index+1))) {
            unsigned short src2 = (unsigned short) std::stoi(this->derive.substr(index+1));
            this->signal = this->signal | src2;
        } else {
            Wire* src2 = c->search(Wire(derive.substr(index+1)));
            this->signal = this->signal | src2->solve(c);
        }
    }
    // LShift operator
    if (derive.substr(index+1, 6) == "LSHIFT") {
        index = derive.find(' ', index+1);
        int shift = stoi(derive.substr(index+1));
        this->signal = this->signal << shift;
    }
    // RShift operator
    if (derive.substr(index+1, 6) == "RSHIFT") {
        index = derive.find(' ', index+1);
        int shift = stoi(derive.substr(index+1));
        this->signal = this->signal >> shift;
    }
    this->has_signal = true;
    return this->signal;
}

int main() {
    StringParser s = StringParser("sampleinput.txt");
    Circuit c = Circuit();
    c.build(&s);
    std::cout << c.get_signal(Wire("a")) << '\n';
    c.override_derive(Wire("b"), std::to_string(c.get_signal(Wire("a"))));
    c.reset();
    std::cout << c.get_signal(Wire("a")) << '\n';
    s.free_parse();
    return 0;
}