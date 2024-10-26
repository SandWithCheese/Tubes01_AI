#include "randomrestart.hpp"

RandomRestart::RandomRestart(int max_restart) : HillClimb() {
    this->max_restart = max_restart;
}

RandomRestart::RandomRestart(const MagicFive& other, int max_restart) : HillClimb(other) {
    this->max_restart = max_restart;
}

void RandomRestart::solve() {
    int best_objective = cube.objectiveFunction();
    vector<vector<int>> best_data = cube.getData();
    int restarts = 0;

    while (restarts < this->max_restart) {
        cube = MagicFive();  // Random Initial State
        int current_obj = cube.objectiveFunction();
        
        while (current_obj != 0) {
            vector<vector<int>> successor_data = generateRandomSuccessor(); // Tetangga acak
            MagicFive successor(successor_data);
            int successor_obj = successor.objectiveFunction();

            if (successor_obj > current_obj) {
                current_obj = successor_obj;
                cube.setData(successor_data);
            } else {
                break;
            }
        }

        int current_objective = cube.objectiveFunction();
        if (current_objective > best_objective) {
            best_objective = current_objective;
            best_data = cube.getData();
        }

        restarts++;

        if (best_objective == 0) {
            cout << "Solution found after " << restarts << " restarts." << endl;
            break;
        }
    }

    cube.setData(best_data);
    if (best_objective != 0) {
        cout << "Best solution found after " << this->max_restart << " restarts." << endl;
        cout << "Objective function: " << best_objective << endl;
    }
}