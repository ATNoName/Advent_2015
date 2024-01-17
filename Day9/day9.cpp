#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

class StringParser {
    public:
    std::ifstream file;
    char* str;
    int size;
    int pos;

    StringParser(std::string input) {
        this->file.open(input);
        this->str = (char *) malloc(64);
        this->pos = 0;
        this->size = 64;
    }

    void read_until(char stop = '\n') {
        this->pos = 0;
        while (this->file.good() && *(this->str+pos-1) != stop) {
            *(this->str+pos) = this->file.get();
            (this->pos)++;
        }
        this->pos--;
        *(this->str+pos) = '\0';
    }

    int char_to_num(char reference = '0') {
        if ((*(this->str) - reference > 9 || *(this->str) - reference < 0) && reference == '0') {
            return -1;
        }
        int num = 0;
        int power = 1;
        while (this->pos > 0) {
            num += (*(this->str+this->pos-1) - reference) * power;
            power *= 10;
            pos--;
        }
        return num;
    }

    bool realloc_string() {
        void* temp = realloc(this->str, size*2);
        if (!temp) {
            return false;
        } else {
            this->str = (char *) temp;
            return true;
        }
    }

    void reset_file() {
        this->file.clear();
        this->file.seekg(0);
    }

    void free_parse() {
        free(this->str);
        this->file.close();
    }
};

class Location {
    public:
    char* name;
    Location(char* name = NULL) {
        this->name = new char[16];
        if (name) {
            strcpy(this->name, name);
        } else {
            *this->name = '\0';
        }
    }

    bool operator==(Location other) {
        return strcmp(this->name, other.name) == 0;
    }

    bool operator==(char* name) {
        return strcmp(this->name, name) == 0;
    }

    bool operator!=(Location other) {
        return strcmp(this->name, other.name) != 0;
    }

    bool operator!=(char* other) {
        return strcmp(this->name, name) == 0;
    }

    void insert(Location adj, int size) {
        int index = 0;
        for (int i = 0;i < 8;i++) {
        }
    }
};

class Map {
    public:
    Location* loc_list;
    int** adj_matrix;
    int** dist_matrix;
    int size;
    Map(int size = 0) {
        this->size = size;
        this->loc_list = new Location[size];
        adj_matrix = new int*[size];
        dist_matrix = new int*[size];
        for (int i = 0;i < this->size;i++) {
            loc_list[i] = Location(NULL);
            adj_matrix[i] = new int[size-1];
            dist_matrix[i] = new int[size-1];
            for (int j = 0;j < (this->size)-1;j++) {
                adj_matrix[i][j] = -1;
                dist_matrix[i][j] = INT_MAX;
            }
        }
    }
    
    int search(char* name) {
        for (int i = 0;i < this->size;i++) {
            if (loc_list[i] == name) {
                return i;
            }
        }
        return -1;
    }

    void build(StringParser* s) {
        int index = 0;
        while (s->file.good()) {
            s->read_until(' ');
            if (!s->file.good()) {
                break;
            }
            if (this->search(s->str) == -1) {
                strcpy(loc_list[index].name, s->str);
                index++;
            }
            int index1 = this->search(s->str);
            s->read_until(' ');
            s->read_until(' ');
            if (this->search(s->str) == -1) {
                strcpy(loc_list[index].name, s->str);
                index++;
            }
            int index2 = this->search(s->str);
            s->read_until(' ');
            s->read_until('\n');
            int dist = s->char_to_num();
            for (int i = 0;i < this->size;i++) {
                if (adj_matrix[index1][i] == -1) {
                    adj_matrix[index1][i] = index2;
                    dist_matrix[index1][i] = dist;
                    break;
                }
            }
            for (int i = 0;i < this->size;i++) {
                if (adj_matrix[index2][i] == -1) {
                    adj_matrix[index2][i] = index1;
                    dist_matrix[index2][i] = dist;
                    break;
                }
            }
        }
    }

    int shortest_path() {
        int shortest_path_dist = INT_MAX;
        // Pick start location
        for (int i = 0;i < this->size;i++) {
            int visited[] = {-1, -1, -1, -1, -1, -1, -1, -1};
            visited[0] = i;
            int total_dist = 0;
            // Run through the path
            for (int j = 0;j < this->size-1;j++) {
                int loc = -1;
                int dist = INT_MAX;
                // Pick shortest edge
                for (int k = 0;k < this->size-1;k++) {
                    bool has_visited = false;
                    // Exclude visited vertices
                    for (int l = 0;l < j+1;l++) {
                        if (adj_matrix[visited[j]][k] == visited[l]) {
                            has_visited = true;
                            break;
                        }
                    }
                    if (!has_visited) {
                        if (dist_matrix[visited[j]][k] < dist) {
                                loc = adj_matrix[visited[j]][k];
                                dist = dist_matrix[visited[j]][k];
                        }
                    }
                }
                visited[j+1] = loc;
                total_dist += dist;
            }
            if (total_dist < shortest_path_dist) {
                shortest_path_dist = total_dist;
            }
        }
        return shortest_path_dist;
    }

    void longest_path(int* path, int size, int* longest_path_dist) {
        if (size == this->size) {
            int path_dist = eval_distance(path);
            if (path_dist > *longest_path_dist) {
                *longest_path_dist = path_dist;
            }
        } else {
            for (int i = 0;i < this->size;i++) {
                bool in_path = false;
                for (int j = 0;j < size; j++) {
                    if (i == path[j]) {
                        in_path = true;
                        break;
                    }
                }
                if (in_path) {
                    continue;
                }
                path[size] = i;
                longest_path(path, size+1, longest_path_dist);
            }
        }
    }

    int eval_distance(int* path) {
        int dist = 0;
        for (int i = 0;i < this->size-1;i++) {
            for (int j = 0;j < this->size;j++) {
                if (adj_matrix[path[i]][j] == path[i+1]) {
                    dist += dist_matrix[path[i]][j];
                }
            }
        }
        return dist;
    }
};

int main() {
    StringParser s = StringParser("input.txt");
    Map m = Map(8);
    m.build(&s);
    std::cout << m.shortest_path() << '\n';
    int* path = new int[8];
    int longest_path_dist = 0;
    m.longest_path(path, 0, &longest_path_dist);
    std::cout << longest_path_dist;
    s.free_parse();
    return 0;
}