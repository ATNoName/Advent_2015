#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

class LightMap {
    public:
        int** map;
        LightMap() {
            map = new int*[1000];
            for (int i = 0;i < 1000;i++) {
                map[i] = new int[1000];
                for (int j = 0;j < 1000;j++) {
                    map[i][j] = 0;
                }
            }
        }

        int old_turn(int length_start, int length_end, int width_start, int width_end, bool status) {
            int change = 0;
            for (int i = length_start;i <= length_end; i++) {
                for (int j = width_start; j <= width_end; j++) {
                    if (this->map[i][j] != status) {
                        if (status) {
                            this->map[i][j] = status;
                            change++;
                        } else {
                            this->map[i][j] = status;
                            change--;
                        }
                    }
                }
            }
            return change;
        }

        int old_toggle(int length_start, int length_end, int width_start, int width_end) {
            int change = 0;
            for (int i = length_start;i <= length_end; i++) {
                for (int j = width_start; j <= width_end; j++) {
                    this->map[i][j] = this->map[i][j] ^ 1;
                    if (this->map[i][j]) {
                        change++;
                    } else {
                        change--;
                    }
                }
            }
            return change;
        }

        int new_turn(int length_start, int length_end, int width_start, int width_end, bool status) {
            int change = 0;
            for (int i = length_start;i <= length_end; i++) {
                for (int j = width_start; j <= width_end; j++) {
                    if (status) {
                        this->map[i][j] += status;
                        change++;
                    } else {
                        if (this->map[i][j] > 0) {
                            this->map[i][j] -= 1;
                            change--;
                        }
                    }
                }
            }
            return change;
        }

        int new_toggle(int length_start, int length_end, int width_start, int width_end) {
            int change = 0;
            for (int i = length_start;i <= length_end; i++) {
                for (int j = width_start; j <= width_end; j++) {
                    this->map[i][j] += 2;
                    change += 2;
                }
            }
            return change;
        }
        void clear() {
            for (int i = 0;i < 1000;i++) {
                map[i] = new int[1000];
                for (int j = 0;j < 1000;j++) {
                    map[i][j] = 0;
                }
            }
        }
};

void get_instruction(std::ifstream* file, char* str) {
    *str = file->get();
    *(str+1) = '\0';
    int pos = 0;
    while ((*file).good() && *(str+pos) != '\n' && *(str+pos) != ' ') {
        pos++;
        *(str+pos) = file->get();
        *(str+pos+1) = '\0';
    }
}

int read_until(std::ifstream* file, char* str, char stop) {
    *str = file->get();
    *(str+1) = '\0';
    int pos = 0;
    while ((*file).good() && *(str+pos) != stop) {
        pos++;
        *(str+pos) = file->get();
        *(str+pos+1) = '\0';
    }
    return pos;
}

int char_to_num(char* str, int length) {
    int num = 0;
    int index = 0;
    while (index < length) {
        num += (*(str+index) - '0') * pow(10, length-index-1);
        index++;
    }
    return num;
}

void read_turn(std::ifstream* file, char* str, int* length_start, int* length_end, int* width_start, int* width_end, bool* status) {
    int pos = 0;
    // read status
    read_until(file, str, ' ');
    std::string parse = str;
    if (parse == "on ") {
        *status = true;
    } else {
        *status = false;
    }
    // read length_start
    pos = read_until(file, str, ',');
    *length_start = char_to_num(str, pos);
    // read width_start
    pos = read_until(file, str, ' ');
    *width_start = char_to_num(str, pos);
    // get to length_end
    read_until(file, str, ' ');
    // read length_end
    pos = read_until(file, str, ',');
    *length_end = char_to_num(str, pos);
    // read width_end
    pos = read_until(file, str, '\n');
    *width_end = char_to_num(str, pos);
}

void read_toggle(std::ifstream* file, char* str, int* length_start, int* length_end, int* width_start, int* width_end) {
    int pos = 0;
    // read length_start
    pos = read_until(file, str, ',');
    *length_start = char_to_num(str, pos);
    // read width_start
    pos = read_until(file, str, ' ');
    *width_start = char_to_num(str, pos);
    // get to length_end
    read_until(file, str, ' ');
    // read length_end
    pos = read_until(file, str, ',');
    *length_end = char_to_num(str, pos);
    // read width_end
    pos = read_until(file, str, '\n');
    *width_end = char_to_num(str, pos);
}

int main() {
    std::ifstream file;
    file.open("input.txt");
    char* str = (char *) malloc(64);
    LightMap* map = new LightMap();
    int count = 0;
    while (file.good()) {
        read_until(&file, str, ' ');
        std::string parse = str;
        if (parse == "turn ") {
            int length_start, length_end, width_start, width_end;
            bool status;
            read_turn(&file, str, &length_start, &length_end, &width_start, &width_end, &status);
            count += map->old_turn(length_start, length_end, width_start, width_end, status);
        } else if (parse == "toggle ") {
            int length_start, length_end, width_start, width_end;
            read_toggle(&file, str, &length_start, &length_end, &width_start, &width_end);
            count += map->old_toggle(length_start, length_end, width_start, width_end);
        } else {
            break;
        }
    }
    std::cout << count;
    std::cout << "\n";
    // reset for part 2
    map->clear();
    count = 0;
    file.clear();
    file.seekg(0);
    while (file.good()) {
        read_until(&file, str, ' ');
        std::string parse = str;
        if (parse == "turn ") {
            int length_start, length_end, width_start, width_end;
            bool status;
            read_turn(&file, str, &length_start, &length_end, &width_start, &width_end, &status);
            count += map->new_turn(length_start, length_end, width_start, width_end, status);
        } else if (parse == "toggle ") {
            int length_start, length_end, width_start, width_end;
            read_toggle(&file, str, &length_start, &length_end, &width_start, &width_end);
            count += map->new_toggle(length_start, length_end, width_start, width_end);
        } else {
            break;
        }
    }
    free(str);
    file.close();
    std::cout << count;
    return 0;
}