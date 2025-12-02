#include <numeric>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void partOne() {
    std::ifstream file("01");
    if (!file.is_open())
    {
        std::cerr << "Error opening file 01" << std::endl;
    }

    std::string line;
    int dialValue = 50;
    int counter = 0;

    while (std::getline(file, line)) {
        char direction = line[0];
        int number = std::stoi(line.substr(1));

        if (direction == 'L') {
            dialValue = (dialValue - number + 100) % 100;
        } else if (direction == 'R') {
            dialValue = (dialValue + number) % 100;
        }

        if (dialValue == 0) {
            counter++;
        }
    }

    std::cout << "Part one password: " << counter << '\n';
}

void partTwo()
{
    std::ifstream file("02");
    if (!file.is_open())
    {
        std::cerr << "Error opening file 02" << std::endl;
    }

    std::string line;
    int dialValue = 50;
    int counter = 0;

    while (std::getline(file, line)) {
        char direction = line[0];
        int number = std::stoi(line.substr(1));

        if (direction == 'L') {
            for (int i = 0; i < number; i++) {
                dialValue = (dialValue - 1 + 100) % 100;
                if (dialValue == 0)
                    counter++;
            }
        }
        else if (direction == 'R') {
            for (int i = 0; i < number; i++) {
                dialValue = (dialValue + 1) % 100;
                if (dialValue == 0)
                    counter++;
            }
        }
    }

    std::cout << "Part two password: " << counter << '\n';
}

int main()
{
    partOne();
    partTwo();
    return 0;
}