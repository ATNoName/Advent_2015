#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Convert input lines into dimensions
 * 
 * @param line 
 * @param dimensions 
 */
void parse_dimension(std::string line, int* dimensions) {
    std::string num = "";
    int count = 0;
    for (int i = 0; i < line.length();i++) {
        char pos = line.at(i);
        if (pos == 'x') {
            dimensions[count] = stoi(num);
            count++;
            num = "";
        } else {
            num = num + pos;
        }
    }
    dimensions[count] = stoi(num);
}

/**
 * @brief calculate surface area using dimension array.
 * 
 * @param dimensions 
 * @return int 
 */
int calc_surface_area(int* dimensions) {
    int area = (2*dimensions[0]*dimensions[1]) + (2*dimensions[1]*dimensions[2]) + (2*dimensions[2]*dimensions[0]);
    return area;
}

/**
 * @brief calculate area of the smallest side of the present
 * 
 * @param dimensions 
 * @return int 
 */
int calc_smallest_side(int* dimensions) {
    int area1 = dimensions[0]*dimensions[1];
    int area2 = dimensions[1]*dimensions[2];
    int area3 = dimensions[0]*dimensions[2];
    if (area1 < area2) {
        if (area1 < area3) {
            return area1;
        } else {
            return area3;
        }
    } else {
        if (area2 < area3) {
            return area2;
        } else {
            return area3;
        }
    }
}

/**
 * @brief Calculate the volume of the prism
 * 
 * @param dimensions 
 * @return int 
 */
int calc_volume(int* dimensions) {
    return dimensions[0]*dimensions[1]*dimensions[2];
}

int calc_smallest_perimeter(int* dimensions) {
    int perimeter1 = (dimensions[0]+dimensions[1])*2;
    int perimeter2 = (dimensions[1]+dimensions[2])*2;
    int perimeter3 = (dimensions[0]+dimensions[2])*2;
    if (perimeter1 < perimeter2) {
        if (perimeter1 < perimeter3) {
            return perimeter1;
        } else {
            return perimeter3;
        }
    } else {
        if (perimeter2 < perimeter3) {
            return perimeter2;
        } else {
            return perimeter3;
        }
    }
}

int main() {
    std::ifstream file;
    file.open("input.txt");
    int paper = 0;
    int ribbon = 0;
    while (file) {
        std::string line;
        std::getline(file, line);
        if (file.eof()) {
            break;
        }
        int dimensions[3];
        parse_dimension(line, dimensions);
        paper += calc_surface_area(dimensions);
        paper += calc_smallest_side(dimensions);
        ribbon += calc_volume(dimensions);
        ribbon += calc_smallest_perimeter(dimensions);
    }
    std::cout << paper;
    std::cout << '\n';
    std::cout << ribbon;
    return 0;
}