#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class Reindeer {
    public:
    string name;
    int speed;
    int travel_time;
    int rest_time;
    Reindeer(string name, int speed = 0, int travel_time = 0, int rest_time = 0) {
        this->name = name;
        this->speed = speed;
        this->travel_time = travel_time;
        this->rest_time = rest_time;
    }
    int calc_dist(int time) {
        if (this->travel_time < 1 || this->speed < 1) {
            return -1;
        }
        int total_run_period = this->speed * this->travel_time * (time / (this->travel_time + this->rest_time));
        int remaining = time % (this->travel_time + this->rest_time);
        if (remaining > travel_time) {
            return total_run_period + travel_time * speed;
        } else {
            return total_run_period + remaining * speed;
        }
    }
};

vector<Reindeer> read_data(ifstream* f) {
    string name = "";
    int speed = 0;
    int travel_time = 0;
    int rest_time = 0;
    string line = "";
    vector<Reindeer> competitor = vector<Reindeer>();
    while (getline(*f, line, ' ')) {
        name = line;
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        speed = stoi(line);
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        travel_time = stoi(line);
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        getline(*f, line, ' ');
        rest_time = stoi(line);
        getline(*f, line, '\n');
        Reindeer data = Reindeer(name, speed, travel_time, rest_time);
        competitor.push_back(data);
    }
    return competitor;
}

int calc_fastest_dist(vector<Reindeer> competitor, int time) {
    int longest_dist = 0;
    for (Reindeer deer: competitor) {
        if (longest_dist < deer.calc_dist(time)) {
            longest_dist = deer.calc_dist(time);
        }
    }
    return longest_dist;
}

int race(vector<Reindeer> competitor, int time) {
    int* com_dist = new int[competitor.size()];
    int* points = new int[competitor.size()];;
    for (int i = 0;i < competitor.size();i++) {
        com_dist[i] = 0;
        points[i] = 0;
    }
    for (int i = 0;i < time;i++) {
        int lead = 0;
        for (int j = 0;j < competitor.size();j++) {
            com_dist[j] = competitor[j].calc_dist(i+1);
            if (com_dist[j] > lead) {
                lead = com_dist[j];
            }
        }
        for (int j = 0;j < competitor.size();j++) {
            if (com_dist[j] == lead) {
                points[j]++;
            }
        }
    }
    int highest = 0;
    for (int i = 0;i < competitor.size();i++) {
        if (points[i] > highest) {
            highest = points[i];
        }
    }
    return highest;
}

int main() {
    ifstream f;
    f.open("input.txt");
    vector<Reindeer> competitor = read_data(&f);
    cout << calc_fastest_dist(competitor, 2503);
    cout << '\n';
    cout << race(competitor, 2503);
    return 0;
}