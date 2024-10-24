#ifndef STOCHASTIC_HPP
#define STOCHASTIC_HPP

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include "../cube/magicfive.hpp"
#include "../solver/solver.hpp"

using namespace std;

class Stochastic : public Solver {
public:
    Stochastic();
    Stochastic(const MagicFive& other);

    void solve() override;
};


#endif