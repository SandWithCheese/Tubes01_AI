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
    float acceptance_probability;

public:
    SimulatedAnnealing(float temperature, float cooling_rate);
    SimulatedAnnealing(float temperature, float cooling_rate, float acceptance_probability);
    SimulatedAnnealing(const MagicFive& other, float temperature, float cooling_rate);
    SimulatedAnnealing(const MagicFive& other, float temperature, float cooling_rate, float acceptance_probability);
    vector<vector<int>> generateRandomSuccessor();
    float acceptanceProbability(int objCurrent, int objNeighbor);
    void decreaseTemperature();
    void solve() override;
};

#endif