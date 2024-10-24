#include "solver.hpp"

Solver::Solver() : cube() {}
Solver::Solver(const MagicFive& other) : cube(other) {}
Solver::~Solver() {}

void Solver::showCube() {
    cube.showCube();
}
