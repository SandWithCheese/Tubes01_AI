#include "randomrestart.hpp"

RandomRestart::RandomRestart() : HillClimb() {}

RandomRestart::RandomRestart(const MagicFive& other) : HillClimb(other) {}

void RandomRestart::solve() {
    int best_objective = cube.objectiveFunction();
    vector<vector<int>> best_data = cube.getData();
    int restarts = 0;

    while (restarts < this->max_restart) {
        int currentScore = cube.objectiveFunction();  // current cube's objective score
        bool improved;

        do {
            improved = false;
            vector<vector<int>> successors = generateSuccessors();
            vector<int> bestSuccessorData = cube.matrixToList(cube.getData());
            int bestScore = currentScore;

            for (const auto& successor : successors) {
                cube.setData(MagicFive::listToMatrix(successor));  // generate suksesor
                int newScore = cube.objectiveFunction();

                if (newScore > bestScore) {
                    bestSuccessorData = successor;
                    bestScore = newScore;
                    improved = true;
                }
            }

            if (improved) {
                cube.setData(MagicFive::listToMatrix(bestSuccessorData));  // ambil suksesor best value 
                currentScore = bestScore;
            }

        } while (improved);  // lanjut kalo ada tetangga yang better

        if (currentScore > best_objective) {
            best_objective = currentScore;
            best_data = cube.getData();
        }

        // Restart the cube with random values
        cube = MagicFive();
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

    cout << "Solution matrix:" << endl;
    for (const auto& row : cube.getData()) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}