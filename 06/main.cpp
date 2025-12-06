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

    std::vector<std::vector<int64_t>> nums;

    std::string line;
    while (getline(file, line)) {
        if (line.find_first_of("0123456789") == std::string::npos) {
            break;
        }

        std::vector<int64_t> row;
        std::stringstream ss(line);
        std::string token;
        while (ss >> token) {
            row.push_back(stoll(token));
        }
        nums.push_back(row);
    }

    int n = static_cast<int>(nums.size()), m = static_cast<int>(nums[0].size());

    std::stringstream ss(line);
    int64_t ans = 0;
    for (int p = 0; p < m; p++) {
        char c;
        ss >> c;

        if (c == '*') {
            int64_t prod = 1;
            for (int i = 0; i < n; i++) {
                prod *= nums[i][p];
            }
            ans += prod;
        } else if (c == '+') {
            int64_t sum = 0;
            for (int i = 0; i < n; i++) {
                sum += nums[i][p];
            }
            ans += sum;
        }
    }
    std::cout << "Part one answer: " << ans << '\n';
}

void partTwo() {
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::vector<std::string> nums;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find_first_of("0123456789") == std::string::npos) {
            break;
        }

        nums.push_back(line);
    }

    int n = static_cast<int>(nums.size()), m = static_cast<int>(nums[0].size());

    std::vector<std::vector<int64_t>> new_nums;
    std::vector<int64_t> tmp;
    for (int j = 0; j < m; j++) {
        int64_t col = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i][j] != ' ') {
                col = (col * 10) + (nums[i][j] - '0');
            }
        }
        if (col == 0) {
            new_nums.push_back(tmp);
            tmp.clear();
        } else {
            tmp.push_back(col);
        }
    }
    new_nums.push_back(tmp);

    std::stringstream ss(line);
    int64_t ans = 0;
    for (auto& x : new_nums) {
        char c;
        ss >> c;

        if (c == '*') {
            int64_t prod = 1;
            for (auto& y : x) {
                prod *= y;
            }
            ans += prod;
        } else {
            int64_t sum = 0;
            for (auto& y : x) {
                sum += y;
            }
            ans += sum;
        }
    }
    std::cout << "Part one answer: " << ans << '\n';
}

int main()
{
    partOne();
    partTwo();
    return 0;
}