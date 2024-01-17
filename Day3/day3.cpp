#include <string>
#include <iostream>
#include <fstream>

class Point2 {
    public:
        int x;
        int y;
        Point2(int init_x = 0, int init_y = 0) {
            this->x = init_x;
            this->y = init_y;
        }

        bool equals(Point2 point) {
            return this->x == point.x && this->y == point.y;
        }
};

class Node {
    public:
        Point2 val;
        Node* next;
        Node(Point2 init_val) {
            val = init_val;
            next = NULL;
        }
};

class LinkedList {
    public:
        Node* head;
        Node* tail;
        int size;

        LinkedList() {
            head = NULL;
            tail = NULL;
            size = 0;
        }

        void insert(Point2 val) {
            Node* new_node = new Node(val);
            if (this->size != 0) {
                if (this->head == this->tail) {
                    this->head->next = new_node;
                    this->tail = new_node;
                } else {
                    this->tail->next = new_node;
                    this->tail = new_node;
                }
            } else {
                this->head = new_node;
                this->tail = new_node;
            }
            this->size += 1;
        }

        bool search(Point2 val) {
            if (size == 0) {
                return false;
            }
            Node* current_node = this->head;
            if (current_node->val.equals(val)) {
                return true;
            }
            while (current_node->next != NULL) {
                if (current_node->next->val.equals(val)) {
                    return true;
                } else {
                    current_node = current_node->next;
                }
            }
            return false;
        }

        void clear() {
            if (this->size > 1) {
                Node* current_node = this->head;
                Node* next_node = this->head->next;
                while (next_node != this->tail) {
                    delete(current_node);
                    current_node = next_node;
                    next_node = next_node->next;
                }
                delete(current_node);
                delete(next_node);
            }
            this->size = 0;
            this->head = NULL;
            this->tail = NULL;
        }
};

class HashMap {
    public:
        int size;
        LinkedList* map;
        HashMap(int init_size = 0) {
            size = init_size;
            map = new LinkedList[init_size];
        }

        int hash(Point2 point) {
            return abs((31*(point.x)+17*(point.y)) % this->size);
        }

        void insert(Point2 point) {
            int table = hash(point);
            this->map[table].insert(point);
        }

        bool search(Point2 point) {
            int table = hash(point);
            return this->map[table].search(point);
        }
        
        void clear() {
            for (int i = 0; i < this->size;i++) {
                map[i].clear();
            }
        }
};

int main() {
    
    std::ifstream file;
    file.open("input.txt");
    Point2 santa_loc = Point2(0,0);
    HashMap hash = HashMap(1000);
    int count = 1;
    hash.insert(santa_loc);
    char instruction;
    while (file.good()) {
        file.get(instruction);
        if (instruction == '^') {
            santa_loc.y += 1;
        } else if (instruction == 'v') {
            santa_loc.y -= 1;
        } else if (instruction == '<') {
            santa_loc.x -= 1;
        } else {
            santa_loc.x += 1;
        }
        if (!hash.search(santa_loc)) {
            count++;
            hash.insert(santa_loc);
        }
    }
    std::cout << count;
    // Reset
    santa_loc = Point2(0,0);
    Point2 robo_loc = Point2(0,0);
    Point2* current_loc;
    hash.clear();
    file.clear();
    file.seekg(0, std::ios::beg);
    count = 1;
    hash.insert(santa_loc);
    bool turn; // 0 for Santa, 1 for Robo
    while (file.good()) {
        file.get(instruction);
        if (turn) {
            current_loc = &robo_loc;
        } else {
            current_loc = &santa_loc;
        }
        if (instruction == '^') {
            current_loc->y += 1;
        } else if (instruction == 'v') {
            current_loc->y -= 1;
        } else if (instruction == '<') {
            current_loc->x -= 1;
        } else {
            current_loc->x += 1;
        }
        if (!hash.search(*current_loc)) {
            count++;
            hash.insert(*current_loc);
        }
        if (turn) {
            turn = 0;
        } else {
            turn = 1;
        }
    }
    std::cout << "\n";
    std::cout << count;
    file.close();
    return 0;
}