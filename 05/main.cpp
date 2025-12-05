#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using Interval = std::pair<double,double>;

double countFresh(const std::vector<Interval>& rangesInput) {
    std::vector<Interval> ranges = rangesInput;
    std::sort(ranges.begin(), ranges.end(),
              [](auto& a, auto& b){ return a.first < b.first; });

    double total = 0;
    double curStart = ranges[0].first;
    double curEnd   = ranges[0].second;

    for (size_t i = 1; i < ranges.size(); ++i) {
        auto& r = ranges[i];

        if (r.first <= curEnd) {
            curEnd = std::max(curEnd, r.second);
        } else {
            total += (curEnd - curStart + 1);
            curStart = r.first;
            curEnd   = r.second;
        }
    }

    total += (curEnd - curStart + 1);

    return total;
}

void partOne() {
    std::ifstream file("01");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::vector<std::pair<double, double>> goodNumbers;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (line.empty()) {
            break;
        }

        double a, b;
        char dash, comma;
        iss >> a >> dash >> b >> comma;
        goodNumbers.emplace_back(a, b);
    }

    int goodIdCounter = 0;

    while (std::getline(file, line)) {
        bool isValid = false;
        double number = std::stod(line);

        for (auto iter : goodNumbers) {
            double a = iter.first;
            double b = iter.second;
            if (number >= a && number <= b) {
                isValid = true;
                break;
            }
        }
        if (isValid) {
            goodIdCounter++;
        }
    }
    std::cout << "Part one good IDs: " << goodIdCounter << '\n'; 
}

void partTwo() {
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::vector<std::pair<double, double>> goodNumbers;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (line.empty()) {
            break;
        }

        double a, b;
        char dash, comma;
        iss >> a >> dash >> b >> comma;
        goodNumbers.emplace_back(a, b);
    }

    double count = countFresh(goodNumbers);
    std::cout << "Fresh id count: " << std::fixed << std::setprecision(0) << count << "\n";
}

int main()
{
    partOne();
    partTwo();
    return 0;
}