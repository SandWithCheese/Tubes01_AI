#ifndef HILLCLIMB_HPP
#define HILLCLIMB_HPP

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include "../cube/magicfive.hpp"
#include "../solver/solver.hpp"

using namespace std;

class HillClimb : public Solver {
public:
    HillClimb();
    HillClimb(const MagicFive& other);
    virtual ~HillClimb();

    vector<vector<int>> generateSuccessors();
    vector<vector<int>> generateRandomSuccessor();

    virtual void solve() = 0;
};


#endif