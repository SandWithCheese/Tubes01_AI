#include "sidewaysmove.hpp"

SidewaysMove::SidewaysMove(int maxSideways) : HillClimb(), maxSidewaysMoves(maxSideways) {}
SidewaysMove::SidewaysMove(const MagicFive& other, int maxSideways) : HillClimb(other), maxSidewaysMoves(maxSideways) {}
SidewaysMove::~SidewaysMove() {}

void SidewaysMove::solve() {
    int currentScore = cube.objectiveFunction(); // current cube's objective score
    int sidewaysCount = 0; 
    bool improved;

    do {
        improved = false;
        vector<vector<int>> successors = generateSuccessors(); 
        vector<int> bestSuccessorData = cube.matrixToList(cube.getData());
        int bestScore = currentScore;

        for (const auto& successor : successors) {
            cube.setData(MagicFive::listToMatrix(successor));  // bangkitkan successor cube
            int newScore = cube.objectiveFunction();

            // jika skor lebih baik, simpan sebagai terbaik dan reset sideways count
            if (newScore > bestScore) {
                bestSuccessorData = successor;
                bestScore = newScore;
                improved = true;
                sidewaysCount = 0; 
            }
            else if (newScore == bestScore) {
                bestSuccessorData = successor;
                improved = true;  // lanjutkan ke tetangga
            }
        }

        if (improved) {
            cube.setData(MagicFive::listToMatrix(bestSuccessorData));
            currentScore = bestScore;
        }

    } while (improved);  // lanjut sampai semua tetangga lebih rendah dari skor saat ini
}
