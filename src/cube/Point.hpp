#ifndef POINT
#define POINT

#include <set>
#include <string>
using namespace std;
class Point {
public:
    int row;
    int col;

    Point(int row, int col);
    void setRow(int row);
    void setCol(int col);
    int getRow();
    int getCol();
    bool operator<(const Point& other) const;
    bool operator ==(const Point& other) const;
};

#endif