#ifndef SIMULATED_HPP
#define SIMULATED_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "../cube/magicfive.hpp"
#include "../solver/solver.hpp"

using namespace std;

class SimulatedAnnealing : public Solver {
private:
    float temperature;
    float cooling_rate;
    int iterations;

public:
    SimulatedAnnealing();
    SimulatedAnnealing(float temperature, float cooling_rate);
    SimulatedAnnealing(const MagicFive& other);
};

#endif