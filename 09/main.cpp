#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Tile {
    int X;
    int Y;
};

bool operator==(const Tile& a, const Tile& b) {
    return a.X == b.X && a.Y == b.Y;
}

bool containsTile(const std::vector<Tile>& tiles, const Tile& t) {
    return std::find(tiles.begin(), tiles.end(), t) != tiles.end();
}

void partOne() {
    std::vector<Tile> tiles;
    std::ifstream file("01");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    int64_t maxArea = 0;
    std::string line;
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        char comma;
        int X;
        int Y;
        iss >> X >> comma >> Y;
        Tile tile{X, Y};
        tiles.push_back(tile);
    }

    for (const Tile& tileA : tiles) {
        for (const Tile& tileB : tiles) {
            if (tileA.X != tileB.X || tileA.Y != tileB.Y) {
                int64_t width = std::abs(tileA.X - tileB.X) + 1;
                int64_t height = std::abs(tileA.Y - tileB.Y) + 1;
                int64_t area = width * height;
                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }
    }

    std::cout << "Part one max area: " << maxArea << '\n';
}

void updateBounds(int& startingX, int& startingY, int& endingX, int& endingY, const Tile& tile) {
    if (tile.X < startingX) {
        startingX = tile.X;
    }
    if (tile.Y < startingY) {
        startingY = tile.Y;
    }
    if (tile.X > endingX) {
        endingX = tile.X;
    }
    if (tile.Y > endingY) {
        endingY = tile.Y;
    }
}

void scanLine(std::vector<Tile>& mergedTiles, int minX, int minY, int maxX, int maxY) {
    for (int y = minY; y <= maxY; ++y) {
        // Gyűjtsd az adott sorban a red és green tile-okat
        std::vector<int> xPositions;
        for (const Tile& t : mergedTiles)
            if (t.Y == y) xPositions.push_back(t.X);

        if (xPositions.size() < 2) continue;
        std::sort(xPositions.begin(), xPositions.end());

        // Minden páros tile között töltsd ki a köztes tile-okat
        for (size_t i = 0; i + 1 < xPositions.size(); i += 2) {
            int startX = xPositions[i];
            int endX = xPositions[i+1];
            for (int x = startX + 1; x < endX; ++x) {
                Tile t{x, y};
                if (!containsTile(mergedTiles, t))
                    mergedTiles.push_back(t);
            }
        }
    }
}

void partTwo() {
    std::vector<Tile> redTiles;
    std::vector<Tile> mergedTiles;
    std::ifstream file("02");
    if (!file.is_open()) {
        std::cerr << "Error opening file 01";
        return;
    }

    int64_t maxArea = 0;
    std::string line;

    // Get the red tiles
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        char comma;
        int X;
        int Y;
        iss >> X >> comma >> Y;
        Tile tile{X, Y};
        redTiles.push_back(tile);
    }

    int startingX = redTiles[0].X;
    int startingY = redTiles[0].Y;
    int endingX = redTiles[0].X;
    int endingY = redTiles[0].Y;

    // Fill with green tiles
    for (int i = 0; i < redTiles.size(); ++i) {
        if (i == 0 || i == redTiles.size() - 1){
            continue;
        }

        Tile currentTile = redTiles[i];
        Tile nextTile = redTiles[i + 1];
        
        mergedTiles.push_back(currentTile);
        updateBounds(startingX, startingY, endingX, endingY, currentTile);

        for (size_t i = 0; i < redTiles.size(); ++i) {
            Tile currentTile = redTiles[i];
            Tile nextTile = redTiles[(i+1) % redTiles.size()]; // wrap around

            mergedTiles.push_back(currentTile);
            updateBounds(startingX, startingY, endingX, endingY, currentTile);

            if (currentTile.X == nextTile.X) {
                int fromY = std::min(currentTile.Y, nextTile.Y);
                int toY   = std::max(currentTile.Y, nextTile.Y);
                for (int y = fromY + 1; y < toY; ++y) {
                    Tile greenTile{currentTile.X, y};
                    if (!containsTile(mergedTiles, greenTile)) {
                        mergedTiles.push_back(greenTile);
                        updateBounds(startingX, startingY, endingX, endingY, greenTile);
                    }
                }
            } else if (currentTile.Y == nextTile.Y) {
                int fromX = std::min(currentTile.X, nextTile.X);
                int toX   = std::max(currentTile.X, nextTile.X);
                for (int x = fromX + 1; x < toX; ++x) {
                    Tile greenTile{x, currentTile.Y};
                    if (!containsTile(mergedTiles, greenTile)) {
                        mergedTiles.push_back(greenTile);
                        updateBounds(startingX, startingY, endingX, endingY, greenTile);
                    }
                }
            }
        }
    }

    // Solve
    scanLine(mergedTiles, startingX, startingY, endingX, endingY);
    for (const Tile &tileA : redTiles)
    {
            for (const Tile &tileB : redTiles)
            {
                if (tileA.X != tileB.X || tileA.Y != tileB.Y)
                {
                    int width = std::abs(tileA.X - tileB.X) + 1;
                    int height = std::abs(tileA.Y - tileB.Y) + 1;
                    
                    Tile fromTile = {std::min(tileA.X, tileB.X), std::min(tileA.Y, tileB.Y)};   // Top-left corner
                    Tile toTile = {std::max(tileA.X, tileB.X), std::max(tileA.Y, tileB.Y)};     // Bottom-right corner

                    bool isOutside = false;
                    for (int i = fromTile.X; i <= toTile.X; ++i)
                    {
                        for (int j = fromTile.Y; j <= toTile.Y; ++j)
                        {
                            Tile currentTile{i, j};
                            // Check if current tile is red or green
                            bool isInMerged = containsTile(mergedTiles, currentTile);

                            if (!isInMerged)
                            {
                                isOutside = true;
                                break;
                            }
                        }

                        if (isOutside)
                        {
                            break;
                        }
                    }

                    if (!isOutside)
                    {
                        int64_t area = width * height;
                        if (area > maxArea)
                        {
                            maxArea = area;
                        }
                    }
                }
            }
        }

    std::cout << "Part two max area: " << maxArea << '\n';
}

int main()
{
    //partOne();
    partTwo();
    return 0;
}