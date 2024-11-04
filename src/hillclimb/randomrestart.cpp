#include "randomrestart.hpp"

RandomRestart::RandomRestart() : HillClimb() {}

RandomRestart::RandomRestart(const MagicFive& other, int max_restart) : HillClimb(other), max_restart(max_restart) {}

void RandomRestart::solve() {
    int best_objective = cube.objectiveFunction();
    appendObjectiveFunction(best_objective);
    vector<vector<int>> best_data = cube.getData();
    int iterations = 0;
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

            appendObjectiveFunction(currentScore);
            iterations++;

        } while (improved);  // lanjut kalo ada tetangga yang better

        cout << "Restart " << restarts << ": " << iterations << " iterations with objective function: " << currentScore << endl;

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
}