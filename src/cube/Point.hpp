#ifndef POINT
#define POINT

class Point {
public:
    int level;
    int col;

    Point(int level, int col);
    void setLevel(int level);
    void setCol(int col);
    int getLevel();
    int getCol();
    bool operator<(const Point& other) const;
};

#endif