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
    int rows;
    int cols;

public:
    MagicFive();
    MagicFive(const vector<vector<int>>& new_data);
    MagicFive(const MagicFive& other);
    ~MagicFive();

    vector<vector<int>> getData();
    void setData(const vector<vector<int>>& new_data);
    int getRows();
    int getCols();

    static vector<vector<int>> listToMatrix(const vector<int>& cube_list);
    static vector<int> matrixToList(const vector<vector<int>>& cube);

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