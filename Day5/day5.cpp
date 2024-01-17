#include <string>
#include <iostream>
#include <fstream>

bool vowel3(char parse, int* count) {
    const char vowel[] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < 5;i++) {
        if (parse == vowel[i]) {
            (*count)++;
            if ((*count) == 3) {
                return true;
            }
            break;
        }
    }
    return false;
}

bool double_occurence(char parse, char last_char) {
    return (last_char == parse);
}

bool no_occurence(char parse, char last_char) {
    if (last_char == 'a') {
        if (parse == 'b') {
            return true;
        }
    }
    if (last_char == 'c') {
        if (parse == 'd') {
            return true;
        }
    }
    if (last_char == 'p') {
        if (parse == 'q') {
            return true;
        }
    }
    if (last_char == 'x') {
        if (parse == 'y') {
            return true;
        }
    }
    return false;
}

bool pair_reoccurrence(char letter, char last_letter, char* previous_string) {
    char* working_letter = previous_string;
    char working_letter_previous = '\0';
    while ((*(working_letter)) != '\0') {
        if (last_letter == working_letter_previous && working_letter_previous != '\0') {
            if (letter == *working_letter) {
                return true;
            }
        }
        working_letter_previous = *working_letter;
        working_letter++;
    }
    return false;
}

bool letter_between(char letter, char last_two) {
    return (letter == last_two);
}

bool is_nice1(std::ifstream* file) {
    char letter = (*file).get();
    bool vowel = false;
    bool doubleoccurence = false;
    int count = 0;
    char last_char = '\0';
    while ((*file).good() && letter != '\n') {
        if (!vowel) {
            vowel = vowel3(letter, &count);
        }
        if (!doubleoccurence) {
            doubleoccurence = double_occurence(letter, last_char);
        }
        if (no_occurence(letter, last_char)) {
            while (letter != '\n') {
                letter = (*file).get();
            }
            return false;
        }
        last_char = letter;
        letter = (*file).get();
    }
    return vowel && doubleoccurence;
}

bool is_nice2(std::ifstream* file, char* previous_string) {
    char letter = (*file).get();
    char last_letter = '\0';
    char last_two = '\0';
    *previous_string = '\0';
    bool pair = false;
    bool between = false;
    int pos = 0;
    while(file->good() && letter != '\n') {
        if (!pair) {
            pair = pair_reoccurrence(letter, last_letter, previous_string);
        }
        if (!between) {
            between = letter_between(letter, last_two);
        }
        if (pos > 0) {
            *(previous_string+pos-1) = last_letter;
            *(previous_string+pos) = '\0';
        }
        last_two = last_letter;
        last_letter = letter;
        letter = file->get();
        pos++;
    }
    return between && pair;
}

int main() {
    std::ifstream file;
    file.open("input.txt");
    int nicecount = 0;
    while(file.good()) {
        nicecount += is_nice1(&file);
    }
    std::cout << nicecount;
    std::cout << "\n";
    file.clear();
    file.seekg(0);
    nicecount = 0;
    char* previous_string = (char *) malloc(32);
    while(file.good()) {
        nicecount += is_nice2(&file, previous_string);
    }
    std::cout << nicecount;
    free(previous_string);
    file.close();
    return 0;
}