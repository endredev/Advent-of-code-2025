#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int countLowNeighbors(const std::vector<std::vector<char>>& positions)
{
    int rows = positions.size();
    int cols = positions[0].size();
    int total = 0;

    int dirs[8][2] = {
        {-1,-1},{-1,0},{-1,1},
        { 0,-1},       { 0,1},
        { 1,-1},{ 1,0},{ 1,1}
    };

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Only check roll of paper cells
            if (positions[i][j] != '@')
                continue;

            int around = 0;

            for (auto& d : dirs)
            {
                int ni = i + d[0];
                int nj = j + d[1];

                if (ni >= 0 && ni < rows &&
                    nj >= 0 && nj < cols &&
                    positions[ni][nj] == '@')
                {
                    around++;
                }
            }

            if (around < 4)
                total++;
        }
    }

    return total;
}

int countNeighbors(const std::vector<std::vector<char>>& pos, int i, int j)
{
    int rows = pos.size();
    int cols = pos[0].size();

    int dirs[8][2] = {
        {-1,-1},{-1,0},{-1,1},
        { 0,-1},       { 0,1},
        { 1,-1},{ 1,0},{ 1,1}
    };

    int count = 0;
    for (auto& d : dirs)
    {
        int ni = i + d[0];
        int nj = j + d[1];
        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && pos[ni][nj] == '@')
            count++;
    }
    return count;
}

void partOne() {
    std::ifstream file("01");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01\n";
        return;
    }
    std::vector<std::vector<char>> positions;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<char> row;
        char pos;
        while (iss >> pos) {
            row.push_back(pos);
        }
        positions.push_back(row);
    }
    int result = countLowNeighbors(positions);
    std::cout << "Part one result: " << result << '\n';
}

void partTwo()
{
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 02\n";
        return;
    }
    std::vector<std::vector<char>> pos;
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<char> row;
        for (char c : line) row.push_back(c);
        pos.push_back(row);
    }

    int rows = pos.size();
    int cols = pos[0].size();

    int totalRemoved = 0;

    while (true)
    {
        std::vector<std::pair<int,int>> removable;

        // Find all removable @
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (pos[i][j] != '@') continue;

                int n = countNeighbors(pos, i, j);
                if (n < 4)
                    removable.push_back({i, j});
            }
        }

        if (removable.empty())
            break; // no more accessible rolls

        // Remove all found @ in this wave
        for (auto& p : removable)
        {
            pos[p.first][p.second] = '.';
            totalRemoved++;
        }
    }

    std::cout << "Part two result: " << totalRemoved << "\n";
}

int main()
{
    partOne();
    partTwo();
    return 0;
}