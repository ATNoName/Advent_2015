#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class Player {
    public:
    int hp;
    int mana;
    int poison_timer;
    int shield_timer;
    int recharge_timer;
    Player() {
        this->hp = 50;
        this->mana = 500;
        this->poison_timer = 0;
        this->shield_timer = 0;
        this->recharge_timer = 0;
    }
};

class Boss {
    public:
    int hp;
    int atk;
    Boss(int hp = 0, int atk = 0) {
        this->hp = hp;
        this->atk = atk;
    }
};

Boss read_data(ifstream* f) {
    string line;
    getline(*f, line, ' ');
    getline(*f, line, ' ');
    getline(*f, line, '\n');
    int hp = stoi(line);
    getline(*f, line, ' ');
    getline(*f, line, '\n');
    int atk = stoi(line);
    return Boss(hp, atk);
}

void recursive_battle(Player player, Boss boss, bool turn, int mana_spent, int* min_spent) {
    // play the turn
    if (player.poison_timer > 0) {
        boss.hp -= 3;
        player.poison_timer--; 
    }
    if (player.recharge_timer > 0) {
        player.mana += 101;
        player.recharge_timer--;
    }
    if (player.shield_timer > 0) {
        player.shield_timer--;
    }
    if (player.hp <= 0) {
        return;
    }
    if (boss.hp <= 0) {
        if (mana_spent < *min_spent) {
            *min_spent = mana_spent;
        }
        return;
    }
    if (!turn) {
        if (player.shield_timer > 0) {
            player.hp -= boss.atk - 7;
        } else {
            player.hp -= boss.atk;
        }
        recursive_battle(player, boss, true, mana_spent, min_spent);
    } else {
        if (player.mana >= 53 && *min_spent > mana_spent) {
            // Cast Magic Missile
            player.mana -= 53;
            boss.hp -= 4;
            recursive_battle(player, boss, false, mana_spent+53, min_spent);
            boss.hp += 4;
            player.mana += 53;
        }
        if (player.mana >= 73 && *min_spent > mana_spent) {
            // Cast Drain
            player.mana -= 73;
            player.hp += 2;
            boss.hp -= 2;
            recursive_battle(player, boss, false, mana_spent+73, min_spent);
            boss.hp += 2;
            player.hp -= 2;
            player.mana += 73;
        }
        if (player.mana >= 113 && player.shield_timer == 0 && *min_spent > mana_spent) {
            // Cast Shield
            player.mana -= 113;
            player.shield_timer = 6;
            recursive_battle(player, boss, false, mana_spent+113, min_spent);
            player.shield_timer = 0;
            player.mana += 113;
        }
        if (player.mana >= 173 && player.poison_timer == 0 && *min_spent > mana_spent) {
            player.mana -= 173;
            player.poison_timer = 6;
            recursive_battle(player, boss, false, mana_spent+173, min_spent);
            player.poison_timer = 0;
            player.mana += 173;
        }    
        if (player.mana >= 229 && player.recharge_timer == 0 && *min_spent > mana_spent) {
            player.mana -= 229;
            player.recharge_timer = 5;
            recursive_battle(player, boss, false, mana_spent+229, min_spent);
        }
    }
}

void recursive_hard_battle(Player player, Boss boss, bool turn, int mana_spent, int* min_spent) {
    // play the turn
    if (turn) {
        player.hp -= 1;
    }
    if (player.poison_timer > 0) {
        boss.hp -= 3;
        player.poison_timer--; 
    }
    if (player.recharge_timer > 0) {
        player.mana += 101;
        player.recharge_timer--;
    }
    if (player.shield_timer > 0) {
        player.shield_timer--;
    }
    if (player.hp <= 0) {
        return;
    }
    if (boss.hp <= 0) {
        if (mana_spent < *min_spent) {
            *min_spent = mana_spent;
        }
        return;
    }
    if (!turn) {
        if (player.shield_timer > 0) {
            player.hp -= boss.atk - 7;
        } else {
            player.hp -= boss.atk;
        }
        recursive_hard_battle(player, boss, true, mana_spent, min_spent);
    } else {
        if (player.mana >= 53 && *min_spent > mana_spent) {
            // Cast Magic Missile
            player.mana -= 53;
            boss.hp -= 4;
            recursive_hard_battle(player, boss, false, mana_spent+53, min_spent);
            boss.hp += 4;
            player.mana += 53;
        }
        if (player.mana >= 73 && *min_spent > mana_spent) {
            // Cast Drain
            player.mana -= 73;
            player.hp += 2;
            boss.hp -= 2;
            recursive_hard_battle(player, boss, false, mana_spent+73, min_spent);
            boss.hp += 2;
            player.hp -= 2;
            player.mana += 73;
        }
        if (player.mana >= 113 && player.shield_timer == 0 && *min_spent > mana_spent) {
            // Cast Shield
            player.mana -= 113;
            player.shield_timer = 6;
            recursive_hard_battle(player, boss, false, mana_spent+113, min_spent);
            player.shield_timer = 0;
            player.mana += 113;
        }
        if (player.mana >= 173 && player.poison_timer == 0 && *min_spent > mana_spent) {
            player.mana -= 173;
            player.poison_timer = 6;
            recursive_hard_battle(player, boss, false, mana_spent+173, min_spent);
            player.poison_timer = 0;
            player.mana += 173;
        }
        if (player.mana >= 229 && player.recharge_timer == 0 && *min_spent > mana_spent) {
            player.mana -= 229;
            player.recharge_timer = 5;
            recursive_hard_battle(player, boss, false, mana_spent+229, min_spent);
        }
    }
}

int main() {
    ifstream f;
    f.open("input.txt");
    Boss boss = read_data(&f);
    Player player = Player();
    int min_spent = INT_MAX;
    recursive_battle(player, boss, true, 0, &min_spent);
    cout << min_spent << '\n';
    min_spent = INT_MAX;
    recursive_hard_battle(player, boss, true, 0, &min_spent);
    cout << min_spent;
    return 0;
}