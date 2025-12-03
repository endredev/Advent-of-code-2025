#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string maxNumberKeepK(const std::string& s, int k) {
    int toRemove = s.size() - k;
    std::vector<char> st;

    for (char c : s) {
        while (!st.empty() && toRemove > 0 && st.back() < c) {
            st.pop_back();
            toRemove--;
        }
        st.push_back(c);
    }

    st.resize(k);

    return std::string(st.begin(), st.end());
}

void partOne() {
    std::ifstream file("01");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::string line;
    int total = 0;

    while (std::getline(file, line)) {
        int bestA = -1;
        int bestB = -1;
        int bestValue = -1;

        for (int i = 0; i < line.size(); i++) {
            int a = line[i] - '0';
            for (int j = i + 1; j < line.size(); j++) {
                int b = line[j] - '0';
                int value = a * 10 + b;
                if (value > bestValue) {
                    bestValue = value;
                    bestA = a;
                    bestB = b;
                }
            }
        }
        total += bestValue;
    }

    std::cout << "Total output joltage: " << total << "\n";
}

void partTwo() {
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::string line;
    long long total = 0;

    while (std::getline(file, line)) {
        std::string best = maxNumberKeepK(line, 12);
        total += std::stoll(best);
    }

    std::cout << "Total output joltage = " << total << "\n";
}

int main()
{
    partOne();
    partTwo();
    return 0;
}