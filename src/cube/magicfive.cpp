#include "magicfive.hpp"

MagicFive::MagicFive() {
    data = this->generateRandomCube();
}

MagicFive::MagicFive(const MagicFive& other) : data(other.data) {}

MagicFive::~MagicFive() {}

vector<vector<int>> MagicFive::listToMatrix(const vector<int>& cube_list) {
    vector<vector<int>> cube_num(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cube_num[i][j] = cube_list[i * cols + j];
        }
    }
    return cube_num;
}

vector<vector<int>> MagicFive::generateRandomCube() {
    vector<int> random_cube_list(125);
    iota(random_cube_list.begin(), random_cube_list.end(), 1);
    shuffle(random_cube_list.begin(), random_cube_list.end(), random_device());

    return listToMatrix(random_cube_list);
}

int MagicFive::checkRow() {
    int heuristic = 0;
    for (const auto& row : data) {
        for (int j = 0; j < cols; j += 5) {
            int row_sum = accumulate(row.begin() + j, row.begin() + j + 5, 0);
            if (row_sum != MAGIC_NUMBER) {
                heuristic++;
            }
        }
    }
    return heuristic;
}

int MagicFive::checkColumn() {
    int heuristic = 0;
    for (int i = 0; i < cols; ++i) {
        int col_sum = 0;
        for (int j = 0; j < rows; ++j) {
            col_sum += data[j][i];
        }
        if (col_sum != MAGIC_NUMBER) {
            heuristic++;
        }
    }
    return heuristic;
}

int MagicFive::checkPillar() {
    int heuristic = 0;
    for (int i = 0; i < cols; ++i) {
        int pillar_sum = 0;
        for (int j = 0; j < rows; ++j) {
            pillar_sum += data[j][i];
        }
        if (pillar_sum != MAGIC_NUMBER) {
            heuristic++;
        }
    }
    return heuristic;
}

int MagicFive::checkSpaceDiagonal() {
    int heuristic = 0;
    // Four diagonals
    vector<int> diags = {
        data[0][0] + data[1][6] + data[2][12] + data[3][18] + data[4][24],
        data[0][4] + data[1][8] + data[2][12] + data[3][16] + data[4][20],
        data[0][20] + data[1][16] + data[2][12] + data[3][8] + data[4][4],
        data[0][24] + data[1][18] + data[2][12] + data[3][6] + data[4][0]
    };

    for (const auto& diag : diags) {
        if (diag != MAGIC_NUMBER) {
            heuristic++;
        }
    }
    return heuristic;
}

int MagicFive::checkPlaneDiagonal() {
    int heuristic = 0;

    // Check diagonals divided by rows
    for (const auto& row : data) {
        int diag1 = row[0] + row[6] + row[12] + row[18] + row[24];
        int diag2 = row[4] + row[8] + row[12] + row[16] + row[20];
        if (diag1 != MAGIC_NUMBER) heuristic++;
        if (diag2 != MAGIC_NUMBER) heuristic++;
    }

    // Check diagonals divided by columns
    for (int i = 0; i < rows; ++i) {
        int diag1 = data[0][i] + data[1][i + 5] + data[2][i + 10] + data[3][i + 15] + data[4][i + 20];
        int diag2 = data[4][i + 20] + data[3][i + 15] + data[2][i + 10] + data[1][i + 5] + data[0][i];
        if (diag1 != MAGIC_NUMBER) heuristic++;
        if (diag2 != MAGIC_NUMBER) heuristic++;
    }

    // Check diagonals divided by pillars
    for (int i = 0; i < cols; i += 5) {
        int diag1 = data[0][i] + data[1][i + 1] + data[2][i + 2] + data[3][i + 3] + data[4][i + 4];
        int diag2 = data[0][i + 4] + data[1][i + 3] + data[2][i + 2] + data[3][i + 1] + data[4][i];
        if (diag1 != MAGIC_NUMBER) heuristic++;
        if (diag2 != MAGIC_NUMBER) heuristic++;
    }

    return heuristic;
}

int MagicFive::objectiveFunction() {
    return -(checkRow() + checkColumn() + checkPillar() + checkSpaceDiagonal() + checkPlaneDiagonal());
}

void MagicFive::showCube() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}