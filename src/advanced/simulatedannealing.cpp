#include "simulatedannealing.hpp"

SimulatedAnnealing::SimulatedAnnealing() : Solver() {
    this->temperature = 1000;
    this->cooling_rate = 0.003;
    this->iterations = 0;
}

SimulatedAnnealing::SimulatedAnnealing(float temperature, float cooling_rate) : Solver() {
    this->temperature = temperature;
    this->cooling_rate = cooling_rate;
    this->iterations = 0;
}

SimulatedAnnealing::SimulatedAnnealing(const MagicFive& other) : Solver(other) {
    this->cube = other;
    this->temperature = 1000;
    this->cooling_rate = 0.003;
    this->iterations = 0;
}
