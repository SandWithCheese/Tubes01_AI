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
    int iterations;
    int population_size;
    int threshold;
public:
    Genetic();
    Genetic(int iterations, int population_size, int threshold);
    Genetic(const MagicFive& other);
    Genetic(const MagicFive& other, int iterations, int population_size, int threshold);
    virtual ~Genetic();

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