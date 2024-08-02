#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Position {
public:
    int x, y;

    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Position& pos) {
        os << "(" << pos.x << "," << pos.y << ")";
        return os;
    }
};

void calculatePathsHelper(Position castle, vector<Position> soldiers, vector<Position> currentPath, vector<vector<Position>>& uniquePaths) {
    if (soldiers.empty()) {
        if (castle == currentPath.front()) {
            uniquePaths.push_back(currentPath);
        }
        return;
    }

    for (auto it = soldiers.begin(); it != soldiers.end(); ++it) {
        Position soldier = *it;
        vector<Position> remainingSoldiers = soldiers;
        remainingSoldiers.erase(it);
        currentPath.push_back(soldier);
        Position newCastle = soldier;
        calculatePathsHelper(newCastle, remainingSoldiers, currentPath, uniquePaths);
        currentPath.pop_back();
    }
}

vector<vector<Position>> calculatePaths(Position castle, vector<Position> soldiers) {
    vector<vector<Position>> uniquePaths;
    vector<Position> currentPath;
    currentPath.push_back(castle); // Start from the castle position
    calculatePathsHelper(castle, soldiers, currentPath, uniquePaths);
    return uniquePaths;
}

int main() {
    int numSoldiers;
    cout << "Enter number of soldiers: ";
    cin >> numSoldiers;

    vector<Position> soldiers;

    for (int i = 0; i < numSoldiers; ++i) {
        int x, y;
        cout << "Enter coordinates for soldier " << (i + 1) << ": ";
        cin >> x >> y;
        soldiers.emplace_back(x, y);
    }

    int startX, startY;
    cout << "Enter the coordinates for your “special” castle: ";
    cin >> startX >> startY;
    Position castle(startX, startY);

    vector<vector<Position>> uniquePaths = calculatePaths(castle, soldiers);

    cout << "Thanks. There are " << uniquePaths.size() << " unique paths for your ‘special_castle’" << endl;

    for (size_t i = 0; i < uniquePaths.size(); ++i) {
        cout << "Path " << (i + 1) << ":" << endl;
        for (const Position& pos : uniquePaths[i]) {
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}
