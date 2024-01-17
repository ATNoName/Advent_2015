#include <iostream>
using namespace std;
// This code was done using as few lines as possible while being readable
int main() {
    int input = 1000; //sample input
    int house = 1;
    int present = 10;
    while (present < input) {
        house++;
        present = 10;
        for (int i = 2;i <= (house+1)/2;i++) {
            if (house % i == 0) {
                present += i * 10;
            }
        }
        present += house * 10;
    }
    cout << house << "\n";
    house = 0;
    present = 0;
    while (present < input) {
        house++;
        present = 0;
        for (int i = 1+((house-1)/50);i <= (house+1)/2;i++) {
            if (house % i == 0) {
                present += i * 11;
            }
        }
        present += house * 11;
    }
    cout << house << "\n";
    return 0;
}