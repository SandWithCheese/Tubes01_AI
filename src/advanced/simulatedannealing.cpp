#include "simulatedannealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(float temperature, float cooling_rate) : Solver() {
    this->temperature = temperature;
    this->cooling_rate = cooling_rate;
    this->cube = MagicFive();
    this->acceptance_probability = 0.5;
}

SimulatedAnnealing::SimulatedAnnealing(float temperature, float cooling_rate, float acceptance_probability) : Solver() {
    this->temperature = temperature;
    this->cooling_rate = cooling_rate;
    this->cube = MagicFive();
    this->acceptance_probability = acceptance_probability;
}

SimulatedAnnealing::SimulatedAnnealing(const MagicFive& other, float temperature, float cooling_rate) : Solver(other) {
    this->temperature = temperature;
    this->cooling_rate = cooling_rate;
    this->cube = other;
    this->acceptance_probability = 0.5;
}

SimulatedAnnealing::SimulatedAnnealing(const MagicFive& other, float temperature, float cooling_rate, float acceptance_probability) : Solver(other) {
    this->temperature = temperature;
    this->cooling_rate = cooling_rate;
    this->cube = other;
    this->acceptance_probability = acceptance_probability;
}

vector<vector<int>> SimulatedAnnealing::generateRandomSuccessor() {
    vector<vector<int>> random_successor = cube.getData();
    int i, j, k, l;
    do {
        i = rand() % cube.getRows();
        j = rand() % cube.getCols();
        k = rand() % cube.getRows();
        l = rand() % cube.getCols();
    } while (i == k && j == l);
    swap(random_successor[i][j], random_successor[k][l]);
    return random_successor;
}

float SimulatedAnnealing::acceptanceProbability(int objCurrent, int objNeighbor) {
    return exp((float)(objNeighbor - objCurrent) / temperature);
}

void SimulatedAnnealing::decreaseTemperature() {
    temperature = temperature  - cooling_rate; // TODO define temperature decrease functoin
}

void SimulatedAnnealing::solve() {
    int objCurrent = cube.objectiveFunction();
    while (temperature > 0 && objCurrent < 0) {
        vector<vector<int>> neighbor = generateRandomSuccessor();
        int objNeighbor = MagicFive(neighbor).objectiveFunction();
        if (objNeighbor > objCurrent) {
            cube = MagicFive(neighbor);
            objCurrent = objNeighbor;
        } else if (acceptanceProbability(objCurrent, objNeighbor) > (float)rand() / RAND_MAX) {
            cube = MagicFive(neighbor);
            objCurrent = objNeighbor;
        }
        decreaseTemperature();
    }
    cout << "Objective function: " << objCurrent << endl;
    if (objCurrent == 0) {
        cout << "Solution found." << endl;
    } else {
        cout << "Solution not found." << endl;
    }
}