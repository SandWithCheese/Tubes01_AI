#include <iostream>
#include "cube/magicfive.hpp"
#include "hillclimb/stochastic.hpp"

using namespace std;

int main() {
    MagicFive cube;
    cube.showCube();

    Solver* solver = new Stochastic(cube);
    solver->solve();
    solver->showCube();
    return 0;
}