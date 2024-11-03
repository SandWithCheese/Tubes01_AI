#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../cube/magicfive.hpp"

class Solver {
protected:
    MagicFive cube;
    vector<int> objective_functions;
public:
    Solver();
    Solver(const MagicFive& other);
    virtual ~Solver();

    MagicFive& getCube();
    vector<int> getObjectiveFunctions();
    void setObjectiveFunctions(const vector<int>& new_objective_functions);
    void appendObjectiveFunction(int new_objective_function);

    virtual void solve() = 0;

    void showCube();
};

#endif
