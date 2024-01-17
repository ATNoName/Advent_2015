#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Go through the entire instruction and arrive at the destination
 * 
 * @param file 
 * @return int 
 */

int move_to(std::ifstream* file) {
    int answer = 0;
    while ((*file).good()) {
        if ((*file).get() == '(') {
            answer++;
        } else {
            answer--;
        }
    }
    return answer;
}

/**
 * @brief Go to the instruction until Santa arrives at a particular floor.
 * Return the position of the instruction
 * 
 * @param floor 
 * @param file 
 * @return int 
 */
int last_position(int floor, std::ifstream* file) {
    int current_floor = 0;
    int count = 0;
    while ((*file).good()) {
        if (current_floor == floor) {
            break;
        }
        if ((*file).get() == '(') {
            current_floor++;
        } else {
            current_floor--;
        }
        count++;
    }
    return count;
}

int main() {
    std::ifstream file;
    file.open("input.txt");
    int answer = move_to(&file);
    std::cout << answer;
    std::cout << "\n";
    file.clear();
    file.seekg(0);
    answer = last_position(-1, &file);
    std::cout << answer;
    file.close();
    return 0;
}
