#include "solver.hpp"

Solver::Solver() : cube() {}
Solver::Solver(const MagicFive& other) : cube(other) {}
Solver::~Solver() {}

MagicFive& Solver::getCube() {
    return cube;
}

void Solver::showCube() {
    cube.showCube();
}
