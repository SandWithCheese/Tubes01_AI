#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../cube/magicfive.hpp"

class Solver {
protected:
    MagicFive cube;
public:
    Solver();
    Solver(const MagicFive& other);
    virtual ~Solver();

    MagicFive& getCube();

    virtual void solve() = 0;

    void showCube();
};

#endif
