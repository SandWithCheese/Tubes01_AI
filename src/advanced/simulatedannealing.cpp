#include "simulatedannealing.hpp"

SimulatedAnnealing::SimulatedAnnealing() {
    this->temperature = 100000;
    this->cooling_rate = 0.999;
    this->cube = MagicFive();
    this->min_temperature = 1.0e-323;
    this->acceptance_probability = 0.5;
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

double SimulatedAnnealing::decreaseTemperature(long iteration) {
    return temperature  * pow(cooling_rate, iteration);
}

double SimulatedAnnealing::acceptanceProbability(int objCurrent, int objNeighbor, double currentTemperature) {
    return exp((float)(objNeighbor - objCurrent) / currentTemperature);
}

vector<float> SimulatedAnnealing::getAcceptanceProbabilities() {
    return acceptance_probabilities;
}

void SimulatedAnnealing::appendAcceptanceProbability(float new_acceptance_probability) {
    acceptance_probabilities.push_back(new_acceptance_probability);
}

void SimulatedAnnealing::solve() {
    int objCurrent = cube.objectiveFunction();
    double currentTemperature = this->temperature;
    long iteration = 1;
    while (currentTemperature > this->min_temperature && objCurrent < 0) {
        vector<vector<int>> neighbor = generateRandomSuccessor();
        int objNeighbor = MagicFive(neighbor).objectiveFunction();
        double probability = acceptanceProbability(objCurrent, objNeighbor, currentTemperature);
        appendAcceptanceProbability((float)probability);
        if (objNeighbor > objCurrent) {
            cube = MagicFive(neighbor);
            objCurrent = objNeighbor;
        } else if (probability > acceptance_probability) {
            cube = MagicFive(neighbor);
            objCurrent = objNeighbor;
        }
        currentTemperature = decreaseTemperature(iteration);
        iteration++;
    }
    cout << "Objective function: " << objCurrent << " with steps: " << iteration << endl;
    if (objCurrent == 0) {
        cout << "Solution found." << endl;
    } else {
        cout << "Solution not found." << endl;
    }
}