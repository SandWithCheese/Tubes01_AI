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
    int count = 0;
    bool improved;

    do {
        improved = false;
        std::vector<int> bestSuccessorData = cube.matrixToList(cube.getData());
        int bestScore = currentScore;
        std::vector<std::vector<int>> successors = generateSuccessors();

        for (const auto& successor : successors) {
            cube.setData(MagicFive::listToMatrix(successor));
            int newScore = cube.objectiveFunction();

            if (newScore > bestScore) {
                bestSuccessorData = successor;
                bestScore = newScore;
                sidewaysMoves = 0;  // Reset sideways move count if improvement is found
                improved = true;
            } else if (newScore == currentScore && sidewaysMoves < maxSidewaysMoves) {
                bestSuccessorData = successor;
                sidewaysMoves++;  // Allow sideways move if within the limit
                improved = true;
            }
        }

        // Update the cube and current score if improvement was found or allowed sideways move
        if (improved) {
            cube.setData(MagicFive::listToMatrix(bestSuccessorData));
            currentScore = bestScore;
            std::cout << "Objective function: " << currentScore << std::endl;
            count++;
        }

        // Check if sideways move limit was reached
        if (sidewaysMoves >= maxSidewaysMoves) {
            std::cout << "Reached maximum sideways moves limit of " << maxSidewaysMoves << std::endl;
            break;
        }

    } while (improved);

    // Final result output
    std::cout << "Final objective function: " << currentScore << std::endl;
    std::cout << "Total iterations: " << count << std::endl;

    // Check if global optimum was found
    if (currentScore == 0) {
        std::cout << "Optimal solution found." << std::endl;
    } else {
        std::cout << "Optimal solution not found." << std::endl;
    }
}
