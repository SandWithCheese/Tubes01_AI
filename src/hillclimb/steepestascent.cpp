#include "steepestascent.hpp"

SteepestAscent::SteepestAscent() : HillClimb() {}
SteepestAscent::SteepestAscent(const MagicFive& other) : HillClimb(other) {}
SteepestAscent::~SteepestAscent() {}

void SteepestAscent::solve() {
    int currentScore = cube.objectiveFunction();  // current cube's objective score
    bool improved;

    do {
        improved = false;
        vector<vector<int>> successors = generateSuccessors();
        vector<int> bestSuccessorData = cube.matrixToList(cube.getData());
        int bestScore = currentScore;

        for (const auto& successor : successors) {
            cube.setData(MagicFive::listToMatrix(successor));  // bangkitkan successor cube
            int newScore = cube.objectiveFunction();

            if (newScore > bestScore) {
                bestSuccessorData = successor;
                bestScore = newScore;
                improved = true;
            }
        }

        if (improved) {
            cube.setData(MagicFive::listToMatrix(bestSuccessorData));  // set best successor
            currentScore = bestScore;
        }

    } while (improved);  // lanjut hingga tidak ada successor yang skornya lebih baik
}
