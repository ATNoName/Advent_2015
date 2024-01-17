#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Item {
    public:
    int cost;
    int damage;
    int armour;
    Item(int cost = 0, int damage = 0, int armour = 0) {
        this->cost = cost;
        this->damage = damage;
        this->armour = armour;
    }
};

class Battler {
    public:
    int hp;
    int atk;
    int def;
    Battler(int hp = 0, int atk = 0,int def = 0) {
        this->hp = hp;
        this->atk = atk;
        this->def = def;
    }
    void equip_inventory(Item weapon_shop = Item(), Item armour = Item(), Item ring1 = Item(), Item ring2 = Item()) {
        this->atk = weapon_shop.damage + ring1.damage + ring2.damage;
        this->def = armour.armour + ring1.armour + ring2.armour;
    }
};

bool init_battle(Battler player, Battler boss) {
    bool turn = true; // true for player, false for boss
    while (player.hp > 0 && boss.hp > 0) {
        if (turn) {
            boss.hp -= player.atk - boss.def;
        } else {
            player.hp -= boss.atk - player.def;
        }
        turn = turn^1;
    }
    return player.hp > 0;
}

Battler read_boss(ifstream* f) {
    string line;
    getline(*f, line, ' ');
    getline(*f, line, ' ');
    getline(*f, line, '\n');
    int hp = stoi(line);
    getline(*f, line, ' ');
    getline(*f, line, '\n');
    int atk = stoi(line);
    getline(*f, line, ' ');
    getline(*f, line, '\n');
    int def = stoi(line);
    return Battler(hp, atk, def);
}

int solve(Battler boss, bool optimize) {
    // hardcode in the shop
    Item* weapon_shop = new Item[5];
    Item* armour_shop = new Item[6];
    Item* ring_shop = new Item[8];
    weapon_shop[0] = Item(8, 4, 0);
    weapon_shop[1] = Item(10, 5, 0);
    weapon_shop[2] = Item(25, 6, 0);
    weapon_shop[3] = Item(40, 7, 0);
    weapon_shop[4] = Item(74, 8, 0);
    armour_shop[0] = Item(0, 0, 0);
    armour_shop[1] = Item(13, 0, 1);
    armour_shop[2] = Item(31, 0, 2);
    armour_shop[3] = Item(53, 0, 3);
    armour_shop[4] = Item(75, 0, 4);
    armour_shop[5] = Item(102, 0, 5);
    ring_shop[0] = Item(0, 0, 0);
    ring_shop[1] = Item(0, 0, 0);
    ring_shop[2] = Item(25, 1, 0);
    ring_shop[3] = Item(50, 2, 0);
    ring_shop[4] = Item(100, 3, 0);
    ring_shop[5] = Item(20, 0, 1);
    ring_shop[6] = Item(40, 0, 2);
    ring_shop[7] = Item(80, 0, 3);
    
    if (optimize) {
        int min_cost = INT_MAX;
        for (int w = 0;w < 5;w++) {
            for (int a = 0;a < 6;a++) {
                for (int r1 = 0;r1 < 8;r1++) {
                    for (int r2 = 1;r2 < 8;r2++) {
                        if (r1 != r2) {
                            Battler player = Battler(100, 0, 0);
                            player.equip_inventory(weapon_shop[w], armour_shop[a], ring_shop[r1], ring_shop[r2]);
                            if (init_battle(player, boss)) {
                                int cost = weapon_shop[w].cost + armour_shop[a].cost + ring_shop[r1].cost + ring_shop[r2].cost;
                                if (cost < min_cost) {
                                    min_cost = cost;
                                }
                            }
                        }
                    }
                }       
            }
        }
        return min_cost;
    } else {
        int max_cost = 0;
        for (int w = 0;w < 5;w++) {
            for (int a = 0;a < 6;a++) {
                for (int r1 = 0;r1 < 8;r1++) {
                    for (int r2 = 1;r2 < 8;r2++) {
                        if (r1 != r2) {
                            Battler player = Battler(100, 0, 0);
                            player.equip_inventory(weapon_shop[w], armour_shop[a], ring_shop[r1], ring_shop[r2]);
                            if (!init_battle(player, boss)) {
                                int cost = weapon_shop[w].cost + armour_shop[a].cost + ring_shop[r1].cost + ring_shop[r2].cost;
                                if (cost > max_cost) {
                                    max_cost = cost;
                                }
                            }
                        }
                    }
                }       
            }
        }
        return max_cost;
    }
}

int main() {
    ifstream f;
    f.open("sampleinput.txt");
    Battler boss = read_boss(&f);
    cout << solve(boss, true) << '\n';
    cout << solve(boss, false);
    return 0;
}