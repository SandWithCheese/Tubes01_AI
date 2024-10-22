#include <iostream>
#include "cube/magicfive.hpp"

using namespace std;

int main() {
    MagicFive cube;
    cube.showCube();
    int objFunc = cube.objectiveFunction();
    cout << "Objective function: " << objFunc << endl;
    return 0;
}