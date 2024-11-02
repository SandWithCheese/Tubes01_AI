#include "solver.hpp"

Solver::Solver() : cube() {}
Solver::Solver(const MagicFive& other) : cube(other) {}
Solver::~Solver() {}

MagicFive& Solver::getCube() {
    return cube;
}

vector<int> Solver::getObjectiveFunctions() {
    return objective_functions;
}

void Solver::setObjectiveFunctions(const vector<int>& new_objective_functions) {
    objective_functions = new_objective_functions;
}

void Solver::appendObjectiveFunction(int new_objective_function) {
    objective_functions.push_back(new_objective_function);
}

void Solver::showCube() {
    cube.showCube();
}
