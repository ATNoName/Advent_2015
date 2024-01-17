#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class Ingredient {
    public:
    string name;
    int capacity;
    int durability;
    int flavour;
    int texture;
    int calories;
    Ingredient(string name = "", int capacity = 0, int durability = 0, int flavour = 0, int texture = 0, int calories = 0) {
        this->name = name;
        this->capacity = capacity;
        this->durability = durability;
        this->flavour = flavour;
        this->texture = texture;
        this->calories = calories;
    }
};

vector<Ingredient> read_data(ifstream* f) {
    string name;
    int capacity;
    int durability;
    int flavour;
    int texture;
    int calories;
    string line;
    vector<Ingredient> ing_list = vector<Ingredient>();
    while (getline(*f, line, ':')) {
        name = line;
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ',');
        capacity = stoi(line);
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ',');
        durability = stoi(line);
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ',');
        flavour = stoi(line);
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ',');
        texture = stoi(line);
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, '\n');
        calories = stoi(line);
        Ingredient i = Ingredient(name, capacity, durability, flavour, texture, calories);
        ing_list.push_back(i);
    }
    return ing_list;
}

int calc_score(vector<Ingredient> ing_list, int* ing_amount) {
    int total_capacity = 0;
    int total_durability = 0;
    int total_flavour = 0;
    int total_texture = 0;
    for (int i = 0;i < ing_list.size();i++) {
        total_capacity += ing_list[i].capacity * ing_amount[i];
        total_durability += ing_list[i].durability * ing_amount[i];
        total_flavour += ing_list[i].flavour * ing_amount[i];
        total_texture += ing_list[i].texture * ing_amount[i];
    }
    // if any score is negative, print 0
    if (total_capacity < 0 || total_durability < 0 || total_flavour < 0 || total_texture < 0) {
        return 0;
    }
    return total_capacity * total_durability * total_flavour * total_texture;
}

int optimize(vector<Ingredient> ing_list, int amount) {
    // Distribute the ingredients evenly
    int* ing_amount = new int[4];
    for (int i = 0;i < ing_list.size();i++) {
        ing_amount[i] = amount / (ing_list.size() - i);
        amount -= ing_amount[i];
    }
    bool optimized = false;
    int score = calc_score(ing_list, ing_amount);
    // tries to increase score by shifting around amounts.
    while (!optimized) {
        bool score_increased = false;
        for (int i = 0;i < ing_list.size(); i++) {
            for (int j = i+1;j < ing_list.size(); j++) {
                // first, try increases, then try decreases.
                ing_amount[i]++;
                ing_amount[j]--;
                int new_score = calc_score(ing_list, ing_amount);
                if (new_score > score) {
                    score = new_score;
                    score_increased = true;
                    break;
                } else {
                    ing_amount[i] -= 2;
                    ing_amount[j] += 2;
                    new_score = calc_score(ing_list, ing_amount);
                    if (new_score > score) {
                        score = new_score;
                        score_increased = true;
                        break;
                    } else {
                        ing_amount[i]++;
                        ing_amount[j]--;
                    }
                }
            }
            if (score_increased) {
                break;
            }
        }
        if (!score_increased) {
            optimized = true;
        }
    }
    return score;
}

int calc_calories(vector<Ingredient> ing_list, int* ing_amount) {
    int calories = 0;
    for (int i = 0;i < ing_list.size();i++) {
        calories += ing_list[i].calories * ing_amount[i];
    }
    return calories;
}

int optimize_for_calories(vector<Ingredient> ing_list, int amount, int calories) {
    int* ing_amount = new int[ing_list.size()];
    ing_amount[0] = amount;
    for (int i = 1;i < ing_list.size();i++) {
        ing_amount[i] = 0;
    }
    int score = 0;
    // brute Force all combinations and print highest score
    while(ing_amount[ing_list.size()-1] != amount) {
        if (calc_calories(ing_list, ing_amount) == calories) {
            int new_score = calc_score(ing_list, ing_amount);
            if (new_score > score) {
                score = new_score;
            }
        }
        // adjust amount
        if (ing_amount[0] != 0) {
            ing_amount[0]--;
            ing_amount[1]++;
        } else {
            for (int i = 1;i < ing_list.size();i++) {
                if (ing_amount[i] != 0) {
                    ing_amount[0] = ing_amount[i] - 1;
                    ing_amount[i] = 0;
                    ing_amount[i+1] += 1;
                    break;
                }
            }
        }
    }
    return score;
}

int main() {
    ifstream f;
    f.open("input.txt");
    vector<Ingredient> ing_list = read_data(&f);
    int score = optimize(ing_list, 100);
    cout << score;
    cout << '\n';
    cout << optimize_for_calories(ing_list, 100, 500);
    return 0;
}