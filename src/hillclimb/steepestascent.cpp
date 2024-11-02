#include "steepestascent.hpp"
#include <iostream> 

SteepestAscent::SteepestAscent() : HillClimb() {}
SteepestAscent::SteepestAscent(const MagicFive& other) : HillClimb(other) {}
SteepestAscent::~SteepestAscent() {}

void SteepestAscent::solve() {
    int currentScore = cube.objectiveFunction();  // current cube's objective score
    appendObjectiveFunction(currentScore);
    bool improved;

    // buat hitung iterasi
    int count = 0;

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
            cout << "Objective function: " << currentScore << endl;
            count++;
        }

        appendObjectiveFunction(currentScore);

    } while (improved);  // lanjut kalo ada tetangga yang better

    // result objective function 
    std::cout << "Final objective function: " << currentScore << std::endl;
    std::cout << "Total iterations: " << count << std::endl;

    // final cube
    std::cout << "Solution matrix:" << std::endl;
    for (const auto& row : cube.getData()) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    // optimal global or not
    if (currentScore == 0) {
        std::cout << "Optimal solution found." << std::endl;
    }
    else {
        std::cout << "Optimal solution not found." << std::endl;
    }
}
