#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isInvalidIDPartOne(long long x) {
    std::string s = std::to_string(x);

    // Length must be even to be a repeat-twice
    int n = s.length();
    if (n % 2 != 0) {
        return false;
    }

    // IDs never have leading zeros by definition
    if (s[0] == '0') {
        return false;
    }

    int half = n / 2;

    // Compare the two halves
    for (int i = 0; i < half; i++) {
        if (s[i] != s[i + half]) {
            return false;
        }
    }
    return true;
}

bool isInvalidIDPartTwo(long long x) {
    std::string s = std::to_string(x);
    int n = s.size();

    // IDs cannot start with 0
    if (s[0] == '0') {
        return false;
    }

    // Try all possible pattern lengths
    for (int len = 1; len <= n / 2; len++) {
        // pattern must divide the full length
        if (n % len != 0) {
            continue;
        }

        int repeatCount = n / len;

        // must repeat at least twice
        if (repeatCount < 2) {
            continue;
        }

        std::string pat = s.substr(0, len);

        bool match = true;
        for (int i = len; i < n; i += len) {
            if (s.compare(i, len, pat) != 0) {
                match = false;
                break;
            }
        }

         // found repeating pattern
        if (match) {
            return true;
        }
    }

    return false;
}


void partOne() {
    std::ifstream file("01");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::string line;
    std::getline(file, line);

    std::stringstream ss(line);
    std::string segment;

    long long invalidIdSum = 0;

    while (std::getline(ss, segment, ',')) {
        if (segment.empty()) continue;

        std::stringstream rangeStream(segment);
        std::string left, right;

        std::getline(rangeStream, left, '-');
        std::getline(rangeStream, right);

        long long a = std::stoll(left);
        long long b = std::stoll(right);

        for (long long i = a; i <= b; i++) {
            if (isInvalidIDPartOne(i)) {
                invalidIdSum += i;
            }
        }
    }

    std::cout << invalidIdSum << '\n';
}

void partTwo() {
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::string line;
    std::getline(file, line);

    std::stringstream ss(line);
    std::string segment;

    long long invalidIdSum = 0;

    while (std::getline(ss, segment, ',')) {
        if (segment.empty()) continue;

        std::stringstream rangeStream(segment);
        std::string left, right;

        std::getline(rangeStream, left, '-');
        std::getline(rangeStream, right);

        long long a = std::stoll(left);
        long long b = std::stoll(right);

        for (long long i = a; i <= b; i++) {
            if (isInvalidIDPartTwo(i)) {
                invalidIdSum += i;
            }
        }
    }

    std::cout << invalidIdSum << '\n';
}

int main()
{
    //partOne();
    partTwo();
    return 0;
}