#include "Point.hpp"

Point::Point(int level, int col) {
    this->level = level;
    this->col = col;
}

void Point::setCol(int col) {
    this->col = col;
}

void Point::setLevel(int level) {
    this->level = level;
}

int Point::getCol() {
    return this->col;
}

int Point::getLevel() {
    return this->level;
}

bool Point::operator<(const Point& other) const {
    if (level != other.level) return level < other.level;
    return col < other.col;
}