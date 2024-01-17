#include <string>
#include <string.h>
#include <iostream>

std::string look_say(std::string input, int iteration) {
    std::string old_input;
    std::string new_string = input;
    for (int i = 0; i < iteration;i++) {
        old_input = new_string;
        new_string = "";
        char prev_value = old_input.at(0);
        int last_pos = 0;
        for (int j = 1;j < old_input.length();j++) {
            if (prev_value != old_input.at(j)) {
                new_string += std::to_string(j-last_pos);
                new_string += prev_value;
                prev_value = old_input.at(j);
                last_pos = j;
            }
        }
        new_string += std::to_string(old_input.length()-last_pos);
        new_string += prev_value;
    }
    return new_string;
}

int main() {
    std::string input = "1";
    std::cout << look_say(input, 5).length();
    return 0;
}