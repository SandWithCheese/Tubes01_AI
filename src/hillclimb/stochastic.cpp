#include "stochastic.hpp"

Stochastic::Stochastic() : HillClimb() {}
Stochastic::Stochastic(const MagicFive& other) : HillClimb(other) {}

void Stochastic::solve() {
    int iterations = 0;
    while (iterations < 500000) {
        vector<vector<int>> current_cube = cube.getData();
        int current_obj = cube.objectiveFunction();

        vector<vector<int>> random_successor_data = generateRandomSuccessor();
        MagicFive random_successor = MagicFive(random_successor_data);

        int random_obj = random_successor.objectiveFunction();

        if (random_obj > current_obj) {
            cout << "Objective function: " << random_obj << endl;
            cube.setData(random_successor_data);
        }

        iterations++;

        if (current_obj == 0) {
            cout << "Solution found in " << iterations << " iterations." << endl;
            break;
        }
    }

    cout << "Solution found in " << iterations << " iterations." << endl;
}