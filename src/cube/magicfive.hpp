#ifndef MAGICFIVE_HPP
#define MAGICFIVE_HPP

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

const int MAGIC_NUMBER = 315;

class MagicFive {
private:
    vector<vector<int>> data;
    int rows = 5;
    int cols = 25;

public:
    MagicFive();
    MagicFive(const MagicFive& other);
    ~MagicFive();

    vector<vector<int>> listToMatrix(const vector<int>& cube_list);
    vector<vector<int>> generateRandomCube();

    int checkRow();
    int checkColumn();
    int checkPillar();
    int checkSpaceDiagonal();
    int checkPlaneDiagonal();
    int objectiveFunction();

    void showCube();
};

#endif