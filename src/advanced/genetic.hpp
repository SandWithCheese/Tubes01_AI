#ifndef GENETIC_HPP
#define GENETIC_HPP

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include "../cube/magicfive.hpp"
#include "../solver/solver.hpp"


using namespace std;

class Genetic : public Solver {
private:
    vector<int> max_objective_functions;
    vector<int> avg_objective_functions;

    int iterations;
    int population_size;
    int threshold;
public:
    Genetic();
    Genetic(int iterations, int population_size, int threshold);
    Genetic(const MagicFive& other);
    Genetic(const MagicFive& other, int iterations, int population_size, int threshold);
    virtual ~Genetic();

    vector<int> getMaxObjectiveFunctions();
    vector<int> getAvgObjectiveFunctions();
    void setMaxObjectiveFunctions(const vector<int>& new_objective_functions);
    void setAvgObjectiveFunctions(const vector<int>& new_objective_functions);
    void appendMaxObjectiveFunction(int new_objective_function);
    void appendAvgObjectFunction(int new_objective_function);

    int getIterations();
    void setIterations(int iterations);
    int getPopulationSize();
    void setPopulationSize(int population_size);

    vector<MagicFive> generatePopulations();

    MagicFive selection(vector<MagicFive>& populations);
    MagicFive crossover(const MagicFive& parent1, const MagicFive& parent2);
    MagicFive mutation(const MagicFive& child);

    void solve() override;
};


#endif