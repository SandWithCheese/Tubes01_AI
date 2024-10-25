#include "hillclimb.hpp"

HillClimb::HillClimb() : Solver() {}
HillClimb::HillClimb(const MagicFive& other) : Solver(other) {}
HillClimb::~HillClimb() {}

vector<vector<int>> HillClimb::generateSuccessors() {
    vector<int> cube_list = MagicFive::matrixToList(cube.getData());

    vector<vector<int>> successors;
    for (size_t i = 0; i < cube_list.size(); ++i) {
        for (size_t j = i + 1; j < cube_list.size(); ++j) {
            vector<int> new_cube = cube_list;
            swap(new_cube[i], new_cube[j]);
            successors.push_back(new_cube);
        }
    }

    return successors;
}

vector<vector<int>> HillClimb::generateRandomSuccessor() {
    vector<vector<int>> random_successor = cube.getData();
    int i = rand() % cube.getRows();
    int j = rand() % cube.getCols();
    int k = rand() % cube.getRows();
    int l = rand() % cube.getCols();
    swap(random_successor[i][j], random_successor[k][l]);

    return random_successor;
}