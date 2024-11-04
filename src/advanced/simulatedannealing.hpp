#ifndef SIMULATED_HPP
#define SIMULATED_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "../cube/magicfive.hpp"
#include "../solver/solver.hpp"

using namespace std;

/**
 * Kelas solver Simulated Annealing
 * @param temperature
 * @param cooling_rate: penurunan temperature setiap iterasi. Penurunan dengan mengurangi temperature dengan cooling rate)
 * @param acceptance_probability: batas apakah state diterima jika objective function neighbor lebih kecil
 */
class SimulatedAnnealing : public Solver {
private:
    vector<float> acceptance_probabilities;
    float temperature;
    float cooling_rate;
    float acceptance_probability;
    double min_temperature;

public:
    SimulatedAnnealing();
    SimulatedAnnealing(const MagicFive& cube);
    vector<float> getAcceptanceProbabilities();
    void appendAcceptanceProbability(float new_acceptance_probability);
    vector<vector<int>> generateRandomSuccessor();
    void generateInitialTemperature();
    void solve() override;
    double decreaseTemperature(long iteration);
    double acceptanceProbability(int objCurrent, int objNeighbor, double currentTemperature);
};

#endif