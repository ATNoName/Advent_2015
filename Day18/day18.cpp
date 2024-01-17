#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class LightMap {
    public:
    bool** map;
    int size;
    LightMap(int size = 0) {
        map = new bool*[size];
        for (int i = 0;i < size;i++) {
            map[i] = new bool[size];
        }
    }

    LightMap(ifstream* f) {
        string line;
        getline(*f, line, '\n');
        this->size = line.size();
        this->map = new bool*[size];
        for (int i = 0;i < size;i++) {
            map[i] = new bool[size];
        }
        f->seekg(0);
        char c;
        for (int i = 0;i < size*size;i++) {
            c = f->get();
            if (c == '\n') {
                c = f->get();
            }
            if (c == '.') {
                this->map[i/size][i % size] = false;
            } else {
                this->map[i/size][i % size] = true;
            }
        }
    }

    void update() {
        LightMap new_map = LightMap();
        for (int i = 0;i < size*size;i++) {
            if (this->map[i/100][i % 100] == true) {
                if ((check_neighbour(i%size, i/size) == 2 || check_neighbour(i%size, i/size) == 3)) {
                    new_map.map[i/size][i % size] = true;
                } else {
                    new_map.map[i/size][i % size] = false;
                }
            } else {
                if (check_neighbour(i%size, i/size) == 3) {
                    new_map.map[i/size][i % size] = true;
                } else {
                    new_map.map[i/size][i % size] = false;
                }
            }
        }
        this->map = new_map.map;
    }

    void new_update() {
        LightMap new_map = LightMap();
        for (int i = 0;i < size*size;i++) {
            if (i == 0 || i == size-1 || i == (size-1)*size || i == size*size-1) {
                new_map.map[i/size][i % size] = true;
                continue;
            }
            if (this->map[i/size][i % size] == true) {
                if ((check_neighbour(i%size, i/size) == 2 || check_neighbour(i%size, i/size) == 3)) {
                    new_map.map[i/size][i % size] = true;
                } else {
                    new_map.map[i/size][i % size] = false;
                }
            } else {
                if (check_neighbour(i%size, i/size) == 3) {
                    new_map.map[i/size][i % size] = true;
                } else {
                    new_map.map[i/size][i % size] = false;
                }
            }
        }
        this->map = new_map.map;
    }

    int check_neighbour(int x, int y) {
        int count = 0;
        for (int i = 0;i < 8;i++) {
            switch(i) {
                case 0:
                x -= 1;
                y -= 1;
                break;
                case 1:
                x += 1;
                break;
                case 2:
                x += 1;
                break;
                case 3:
                x -= 2;
                y += 1;
                break;
                case 4:
                x += 2;
                break;
                case 5:
                x -= 2;
                y += 1;
                break;
                case 6:
                x += 1;
                break;
                case 7:
                x += 1;
                break;
            }
            if (!(y >= 100 || y < 0 || x >= 100 || x < 0)) {
                if (this->map[y][x] == true) {
                    count += 1;
                }
            }
        }
        return count;
    }

    int count() {
        int count = 0;
        for (int i = 0;i < size*size;i++) {
            if (this->map[i/size][i % size] == true) {
                count += 1;
            }
        }
        return count;
    }
};

int main() {
    ifstream f;
    f.open("sampleinput.txt");
    int step = 5;
    LightMap map = LightMap(&f);
    for (int i = 0;i < step;i++) {
        map.update();
    }
    cout << map.count() << '\n';
    f.clear();
    f.seekg(0);
    LightMap map = LightMap(&f);
    for (int i = 0;i < step;i++) {
        map.new_update();
    }
    cout << map.count();
    return 0;
}