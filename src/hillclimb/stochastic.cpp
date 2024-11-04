#include "stochastic.hpp"

Stochastic::Stochastic() : HillClimb() {}
Stochastic::Stochastic(const MagicFive& other) : HillClimb(other) {}

void Stochastic::solve() {
    int iterations = 0;
    int current_obj = cube.objectiveFunction();
    appendObjectiveFunction(current_obj);
    while (iterations < 500000) {
        vector<vector<int>> current_cube = cube.getData();
        current_obj = cube.objectiveFunction();

        vector<vector<int>> random_successor_data = generateRandomSuccessor();
        MagicFive random_successor = MagicFive(random_successor_data);

        int random_obj = random_successor.objectiveFunction();

        if (random_obj > current_obj) {
            // cout << "Objective function: " << random_obj << endl;
            cube.setData(random_successor_data);
        }
        
        appendObjectiveFunction(current_obj);

        iterations++;

        if (current_obj == 0) {
            cout << "Solution found in " << iterations << " iterations." << endl;
            break;
        }
    }

    cout << "Objective function: " << cube.objectiveFunction() << endl;
    cout << "Solution found in " << iterations << " iterations." << endl;
}