#include <string>
#include "Point.hpp"

Point::Point(int row, int col) {
    this->row = row;
    this->col = col;
}

void Point::setCol(int col) {
    this->col = col;
}

void Point::setRow(int row) {
    this->row = row;
}

int Point::getCol() {
    return this->col;
}

int Point::getRow() {
    return this->row;
}

bool Point::operator<(const Point& other) const {
    if (row == other.row) {
        return col < other.col;
    }
    return row < other.row;
}

bool Point::operator==(const Point& other) const {
    return (row == other.row && col == other.col);
}