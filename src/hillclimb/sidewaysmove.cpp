#include "sidewaysmove.hpp"
#include <iostream>

SidewaysMove::SidewaysMove(int maxSidewaysMoves) 
    : HillClimb(), maxSidewaysMoves(maxSidewaysMoves) {}

SidewaysMove::SidewaysMove(const MagicFive& other, int maxSidewaysMoves) 
    : HillClimb(other), maxSidewaysMoves(maxSidewaysMoves) {}

SidewaysMove::~SidewaysMove() {}

void SidewaysMove::solve() {
    int currentScore = cube.objectiveFunction();
    int sidewaysMoves = 0;
    bool improved;

    // buat hitung iterasi
    int count = 0;

    do {
        improved = false;
        std::vector<std::vector<int>> successors = generateSuccessors();
        std::vector<int> bestSuccessorData = cube.matrixToList(cube.getData());
        int bestScore = currentScore;

        for (const auto& successor : successors) {
            cube.setData(MagicFive::listToMatrix(successor)); // generate suksesor
            int newScore = cube.objectiveFunction();

            if (newScore > bestScore) {
                bestSuccessorData = successor;
                bestScore = newScore;
                sidewaysMoves = 0;  // reset sideways move count kalau ada yang lebih baik
                improved = true;
            } else if (newScore == currentScore && sidewaysMoves < maxSidewaysMoves) {
                bestSuccessorData = successor;
                sidewaysMoves++; 
                improved = true;
            }
        }

        if (improved) {
            cube.setData(MagicFive::listToMatrix(bestSuccessorData));  // ambil suksesor best value
            currentScore = bestScore;
            std::cout << "Objective function: " << currentScore << std::endl;
            count++;
        }

        // cek apakah sudah mencapai batas sideways moves
        if (sidewaysMoves >= maxSidewaysMoves) {
            std::cout << "Reached maximum sideways moves limit of " << maxSidewaysMoves << std::endl;
            break;
        }

    } while (improved);  // lanjut kalo ada tetangga yang better dan belum mencapai batas sideways moves

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
    } else {
        std::cout << "Optimal solution not found." << std::endl;
    }
}
