#include "sidewaysmove.hpp"
#include <iostream>

SidewaysMove::SidewaysMove(int maxSidewaysMoves)
    : HillClimb(), maxSidewaysMoves(maxSidewaysMoves) {
}

SidewaysMove::SidewaysMove(const MagicFive& other, int maxSidewaysMoves)
    : HillClimb(other), maxSidewaysMoves(maxSidewaysMoves) {
}

SidewaysMove::~SidewaysMove() {}

void SidewaysMove::solve() {
    int currentScore = cube.objectiveFunction();
    appendObjectiveFunction(currentScore);
    int sidewaysMoves = 0;
    bool improved;

    // buat hitung iterasi
    int count = 0;

    do {
        improved = false;
        std::vector<std::vector<int>> successors = generateSuccessors();
        std::vector<int> bestSuccessorData = cube.matrixToList(cube.getData());
        std::vector<int> bestSidewayData = cube.matrixToList(cube.getData());
        int bestScore = currentScore;
        int bestSidewayScore = currentScore;

        for (const auto& successor : successors) {
            cube.setData(MagicFive::listToMatrix(successor)); // generate suksesor
            int newScore = cube.objectiveFunction();

            if (newScore > bestScore) {
                bestSuccessorData = successor;
                bestScore = newScore;
                sidewaysMoves = 0;  // reset sideways move count kalau ada yang lebih baik
                improved = true;
            }
            else if (newScore == currentScore && sidewaysMoves < maxSidewaysMoves) {
                bestSidewayData = successor;
                bestSidewayScore = newScore;
            }
        }

        if (improved) {
            cube.setData(MagicFive::listToMatrix(bestSuccessorData));  // ambil suksesor best value
            currentScore = bestScore;
            // std::cout << "Objective function: " << currentScore << std::endl;
            count++;
        }
        else if (sidewaysMoves < maxSidewaysMoves) {
            improved = true;
            cube.setData(MagicFive::listToMatrix(bestSidewayData));  // ambil suksesor best value
            currentScore = bestSidewayScore;
            count++;
            sidewaysMoves++;
        }

        appendObjectiveFunction(currentScore);

        // cek apakah sudah mencapai batas sideways moves
        if (sidewaysMoves >= maxSidewaysMoves) {
            std::cout << "Reached maximum sideways moves limit of " << maxSidewaysMoves << std::endl;
            break;
        }

    } while (improved);  // lanjut kalo ada tetangga yang better dan belum mencapai batas sideways moves

    // result objective function
    std::cout << "Final objective function: " << currentScore << std::endl;
    cout << "Solution found in " << count << " iterations." << endl;

    // optimal global or not
    if (currentScore == 0) {
        std::cout << "Optimal solution found." << std::endl;
    }
    else {
        std::cout << "Optimal solution not found." << std::endl;
    }
}