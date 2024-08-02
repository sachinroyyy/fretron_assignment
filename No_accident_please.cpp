#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
};

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  
    return (val > 0) ? 1 : 2;
}

bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

bool isIntersecting(Point a1, Point a2, Point b1, Point b2) {

    int o1 = orientation(a1, a2, b1);
    int o2 = orientation(a1, a2, b2);
    int o3 = orientation(b1, b2, a1);
    int o4 = orientation(b1, b2, a2);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(a1, b1, a2)) return true;
    if (o2 == 0 && onSegment(a1, b2, a2)) return true;
    if (o3 == 0 && onSegment(b1, a1, b2)) return true;
    if (o4 == 0 && onSegment(b1, a2, b2)) return true;

    return false; 
}

bool isSafe(const vector<Point>& path, Point newPoint) {
    if (path.size() < 2) return true;
    Point lastPoint = path.back();
    Point secondLastPoint = path[path.size() - 2];

    for (int i = 0; i < path.size() - 1; i++) {
        if (isIntersecting(path[i], path[i + 1], secondLastPoint, newPoint)) {
            return false;
        }
    }
    return true;
}

void drawFlightPaths(const vector<vector<Point>>& flights) {
    vector<vector<Point>> paths;
    for (auto flight : flights) {
        vector<Point> path;
        bool isValid = true;
        for (auto point : flight) {
            if (path.empty() || isSafe(path, point)) {
                path.push_back(point);
            } else {
                cout << "Flight path intersects with previous flight. Cannot draw path." << endl;
                isValid = false;
                break;
            }
        }
        if (isValid) paths.push_back(path);
    }

    for (int i = 0; i < paths.size(); i++) {
        cout << "Flight " << i + 1 << " path: ";
        for (auto point : paths[i]) {
            cout << "(" << point.x << "," << point.y << ") ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<Point>> flights = {
        {{1, 1}, {2, 2}, {3, 3}},
        {{1, 1}, {2, 4}, {3, 2}},
        {{1, 1}, {4, 2}, {3, 4}}
    };

    drawFlightPaths(flights);

    return 0;
}
