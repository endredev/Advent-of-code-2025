#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Box {
    int64_t x, y, z;
};

Box operator-(const Box& a, const Box& b){ 
    return { a.x-b.x, a.y-b.y, a.z-b.z }; 
}

std::vector<Box> boxes;

std::vector<Box> loadInput(const std::string& file){
    std::vector<Box> ret;
    std::ifstream fs(file);
    std::string line;
    while (std::getline(fs, line)) {
        int x, y, z;
        char comma1, comma2;
        std::stringstream ss(line);
        ss >> x >> comma1 >> y >> comma2 >> z;
        ret.push_back({ x, y, z });
    }
    return ret;
}

long long squaredDistance(const Box& a, const Box& b){
    Box c = b - a;
    return c.x*c.x + c.y*c.y + c.z*c.z;
}

struct Edge {
    int a, b;
    int64_t dist;
    bool operator<(const Edge& right) const { return dist < right.dist; }
};

struct Dsu {
    std::vector<int> parent, size;

    Dsu(int n) : parent(n), size(n, 1) {
        for(int i=0; i<parent.size(); ++i){ parent[i] = i; }
    }

    int find(int x) {
        if(parent[x] != x){
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool uunion(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

size_t partOne(const std::vector<Box>& boxes, int pair_count)
{
    std::vector<Edge> edges;

    for(int i = 0; i < boxes.size(); ++i) {
        for(int j = i+1; j < boxes.size(); ++j) {
            edges.push_back({ i, j, squaredDistance(boxes[i], boxes[j]) });
        }
    }

    std::partial_sort(edges.begin(), edges.begin()+pair_count, edges.end());

    Dsu dsu((int)boxes.size());
    for(int i = 0; i < pair_count; ++i) {
        dsu.uunion(edges[i].a, edges[i].b);
    }

    std::partial_sort(dsu.size.begin(), dsu.size.begin()+3, dsu.size.end(), std::greater<int>());
    std::cout << "Part One: " << dsu.size[0] * dsu.size[1] * dsu.size[2] << "\n";
    return dsu.size[0] * dsu.size[1] * dsu.size[2];
}

size_t partTwo(const std::vector<Box>& boxes)
{
    std::vector<Edge> edges;

    for(int i = 0; i < boxes.size(); ++i) {
        for(int j = i+1; j < boxes.size(); ++j) {
            edges.push_back({ i, j, squaredDistance(boxes[i], boxes[j]) });
        }
    }

    std::sort(edges.begin(), edges.end());

    Dsu dsu((int)boxes.size());
    int idx = -1;

    for(int i = 0; i < edges.size(); ++i) {
        if(dsu.uunion(edges[i].a, edges[i].b)) {
            idx = i;
        }
    }

    Edge edge = edges[idx];
    std::cout << "Part Two: " << boxes[edge.a].x * boxes[edge.b].x << "\n";
    return boxes[edge.a].x * boxes[edge.b].x;
}

int main()
{
    auto actual_values = loadInput("01");

    partOne(actual_values, 1000);
    partTwo(actual_values);
    
    return 0;
}