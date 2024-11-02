#include "magicfive.hpp"

MagicFive::MagicFive() {
    rows = 5;
    cols = 25;
    data = this->generateRandomCube();
}

MagicFive::MagicFive(const vector<vector<int>>& new_data) : rows(5), cols(25), data(new_data) {}

MagicFive::MagicFive(const MagicFive& other) : rows(other.rows), cols(other.cols), data(other.data) {}

MagicFive::~MagicFive() {}

vector<vector<int>> MagicFive::getData() const {
    return data;
}

void MagicFive::setData(const vector<vector<int>>& new_data) {
    data = new_data;
}

int MagicFive::getRows() const {
    return rows;
}

int MagicFive::getCols() const {
    return cols;
}

vector<vector<int>> MagicFive::listToMatrix(const vector<int>& cube_list) {
    vector<vector<int>> cube_num(5, vector<int>(25));

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 25; ++j) {
            cube_num[i][j] = cube_list[i * 25 + j];
        }
    }

    return cube_num;
}

vector<int> MagicFive::matrixToList(const vector<vector<int>>& cube) {
    vector<int> cube_list(125);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 25; ++j) {
            cube_list[i * 25 + j] = cube[i][j];
        }
    }

    return cube_list;
}

vector<vector<int>> MagicFive::generateRandomCube() {
    vector<int> random_cube_list(125);
    iota(random_cube_list.begin(), random_cube_list.end(), 1);
    shuffle(random_cube_list.begin(), random_cube_list.end(), random_device());

    return listToMatrix(random_cube_list);
}

int MagicFive::checkRow() const {
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

int MagicFive::checkColumn() const {
    int heuristic = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            int col_sum = 0;
            for (int k = j; k < cols; k+=5) {
                col_sum += data[i][k];
            }
            if (col_sum != MAGIC_NUMBER) {
                heuristic++;
            }
        }
    }

    return heuristic;
}

int MagicFive::checkPillar() const {
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

int MagicFive::checkSpaceDiagonal() const {
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

int MagicFive::checkPlaneDiagonal() const {
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

int MagicFive::objectiveFunction() const {
    return -(checkRow() + checkColumn() + checkPillar() + checkSpaceDiagonal() + checkPlaneDiagonal());
}

int MagicFive::fitnessFunction() const {
    return 109 + objectiveFunction();
}

void MagicFive::showCube() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

set<Point> MagicFive::incorrectPosition() {
    set<Point> incorrectPosition;

    // Row
    int currRow = 0;
    for (const auto& row : data) { // Level
        for (int j = 0; j < cols; j += 5) { // Ke belakang
            int row_sum = accumulate(row.begin() + j, row.begin() + j + 5, 0);
            if (row_sum != MAGIC_NUMBER) {
                for (int k = j; k < j + 5; k++) { // Ke samping
                    incorrectPosition.insert(Point(currRow, k));
                }
            }
        }
        currRow++;
    }
    
    // Column
    for (int i = 0; i < rows; i++) { // Level
        for (int j = 0; j < rows; j++) { // Ke samping
            int col_sum = 0;
            for (int k = j; k < cols; k+=5) { // Ke belakang
                col_sum += data[i][k];
            }
            if (col_sum != MAGIC_NUMBER) {
                for (int k = j; k < cols; k+=5) {
                    incorrectPosition.insert(Point(i, k));
                }
            }
        }
    }
    
    // Pillar
    for (int i = 0; i < cols; ++i) { // Ke setiap item di sebuah level
        int pillar_sum = 0;
        for (int j = 0; j < rows; ++j) {
            pillar_sum += data[j][i];
        }
        if (pillar_sum != MAGIC_NUMBER) {
            for (int j = 0; j < rows; j++) { // Level
                incorrectPosition.insert(Point(j, i));
            }
        }
    }
    
    // Plane diagonal

    // Check diagonals divided by rows
    currRow = 0;
    for (const auto& row : data) {
        int diag1 = row[0] + row[6] + row[12] + row[18] + row[24];
        int diag2 = row[4] + row[8] + row[12] + row[16] + row[20];
        if (diag1 != MAGIC_NUMBER) {
            for (int i = 0; i < cols; i+=6) {
                incorrectPosition.insert(Point(currRow, i));
            }
        };
        currRow++;
        if (diag2 != MAGIC_NUMBER) {
            for (int i = rows - 1; i < cols; i+=4) {
                incorrectPosition.insert(Point(currRow, i));
            }
        };
    }
    
    // Check diagonals divided by columns
    for (int i = 0; i < rows; ++i) {
        int diag1 = data[0][i] + data[1][i + 5] + data[2][i + 10] + data[3][i + 15] + data[4][i + 20];
        int diag2 = data[4][i + 20] + data[3][i + 15] + data[2][i + 10] + data[1][i + 5] + data[0][i];
        if (diag1 != MAGIC_NUMBER) {
            for (int j = 0; j < rows; j++) {
                incorrectPosition.insert(Point(j, i + j * 5));
            }
        };
        if (diag2 != MAGIC_NUMBER) {
            for (int j = 0; j < rows; j++) {
                incorrectPosition.insert(Point(j, i + (4 - j) * 5));
            }
        };
    }
    
    // Check diagonals divided by pillars
    for (int i = 0; i < cols; i += 5) {
        int diag1 = data[0][i] + data[1][i + 1] + data[2][i + 2] + data[3][i + 3] + data[4][i + 4];
        int diag2 = data[0][i + 4] + data[1][i + 3] + data[2][i + 2] + data[3][i + 1] + data[4][i];
        if (diag1 != MAGIC_NUMBER) {
            for (int j = 0; j < rows; j++) {
                incorrectPosition.insert(Point(j, i + j));
            }
        };
        if (diag2 != MAGIC_NUMBER) {
            for (int j = 0; j < rows; j++) {
                incorrectPosition.insert(Point(j, i + (4 - j)));
            }
        };
    }
    
    // Space diagonals
    vector<vector<Point>> diagPos;

    vector<Point>temp1;
    for(int i = 0; i < rows; i++) {
        temp1.emplace_back(i, i * 6);
    }
    diagPos.emplace_back(temp1);

    vector<Point>temp2;
    for(int i = 0; i < rows; i++) {
        temp2.emplace_back(i, i*4);
    }
    diagPos.emplace_back(temp2);

    vector<Point>temp3;
    for(int i = 0; i < rows; i++) {
        temp3.emplace_back(i, (5-i) * 4);
    }
    diagPos.emplace_back(temp3);

    vector<Point>temp4;
    for(int i = 0; i < rows; i++) {
        temp4.emplace_back(i, (4-i) * 6);
    }
    diagPos.emplace_back(temp4);


    vector<int> diags = {
            data[0][0] + data[1][6] + data[2][12] + data[3][18] + data[4][24],
            data[0][4] + data[1][8] + data[2][12] + data[3][16] + data[4][20],
            data[0][20] + data[1][16] + data[2][12] + data[3][8] + data[4][4],
            data[0][24] + data[1][18] + data[2][12] + data[3][6] + data[4][0]
    };


    for (int i = 0; i < 4; i++) {
        if (diags[i] != MAGIC_NUMBER) {
            for (int j = 0; j < rows; j++) {
                incorrectPosition.insert(diagPos[i][j]);
            }
        }
    }
    
    return incorrectPosition;

}