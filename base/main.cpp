#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void partOne() {
    std::ifstream file("01");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::string line;
    std::getline(file, line);
}

void partTwo() {
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::string line;
    std::getline(file, line);
}

int main()
{
    partOne();
    partTwo();
    return 0;
}