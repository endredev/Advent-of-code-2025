#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

void partOne() {
    std::ifstream file("01");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }

    // Fins starting pos
    int rows = grid.size();
    int cols = grid[0].size();
    int startRow = 0;
    int startCol = -1;
    for (int c = 0; c < grid[0].size(); c++) {
        if (grid[0][c] == 'S') {
            startCol = c;
            break;
        }
    }

    std::queue<std::pair<int,int>> beams;
    beams.push(std::make_pair(0, startCol));

    std::set<std::pair<int,int>> visited;
    int splitCount = 0;

    while (!beams.empty()) {
        std::pair<int,int> p = beams.front();
        beams.pop();

        int r = p.first;
        int c = p.second;

        // Out of bounds -> ignore
        if (r < 0 || r >= rows || c < 0 || c >= cols) continue;

        // If already visited, skip
        if (visited.count(std::make_pair(r, c)) > 0) continue;
        visited.insert(std::make_pair(r, c));

        char cell = grid[r][c];

        if (cell == '^') {
            // Splitter: stop downward, spawn left and right beams
            beams.push(std::make_pair(r, c - 1));
            beams.push(std::make_pair(r, c + 1));

            splitCount++;
            continue;
        } else {
            // Empty or S: continue downward
            beams.push(std::make_pair(r + 1, c));
        }
    }

    std::cout << "Part One: " << splitCount++ << "\n";
}

void partTwo() {
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }

    // Fins starting pos
    int rows = grid.size();
    int cols = grid[0].size();
    int startRow = 0;
    int startCol = -1;
    for (int c = 0; c < grid[0].size(); c++) {
        if (grid[0][c] == 'S') {
            startCol = c;
            break;
        }
    }

    std::unordered_map<int, long long> dp_row;
    dp_row[startCol] = 1LL;

    long long exitCount = 0LL;

    // For each row, resolve all splits that happen on that same row,
    // then let remaining beams fall to the next row.
    for (int r = 0; r < rows; ++r) {
        // Repeatedly process splitters on the same row until no more changes
        bool changed = true;
        while (changed) {
            changed = false;
            std::unordered_map<int, long long> new_dp = dp_row;

            for (auto &p : dp_row) {
                int c = p.first;
                long long cnt = p.second;
                if (cnt == 0) continue;

                // If current cell is a splitter, stop beams here and emit left & right
                if (c >= 0 && c < cols && grid[r][c] == '^') {
                    // remove the beam at this splitter (it stops)
                    new_dp[c] -= cnt;

                    // emit to the left
                    if (c - 1 < 0) {
                        exitCount += cnt; // left exit -> timeline ends
                    } else {
                        new_dp[c - 1] += cnt;
                    }

                    // emit to the right
                    if (c + 1 >= cols) {
                        exitCount += cnt; // right exit -> timeline ends
                    } else {
                        new_dp[c + 1] += cnt;
                    }

                    changed = true;
                }
            }

            dp_row.clear();
            for (auto &q : new_dp) {
                if (q.second != 0) dp_row[q.first] = q.second;
            }
        }

        // After closure, remaining beams (columns in dp_row) fall down one row
        std::unordered_map<int, long long> next_dp;
        for (auto &p : dp_row) {
            int c = p.first;
            long long cnt = p.second;

            // safety: if column somehow out of bounds, treat as exit
            if (c < 0 || c >= cols) {
                exitCount += cnt;
            } else {
                // if next row is beyond grid, they exit downward
                if (r + 1 >= rows) {
                    exitCount += cnt;
                } else {
                    next_dp[c] += cnt;
                }
            }
        }

        dp_row.swap(next_dp);
    }

    // any remaining beams (shouldn't normally remain) are exits too
    for (auto &p : dp_row) exitCount += p.second;
    std::cout << "Part Two: " << exitCount << "\n";
}


int main()
{
    partOne();
    partTwo();
    return 0;
}