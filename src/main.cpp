#include <iostream>
#include "cube/magicfive.hpp"
#include "hillclimb/stochastic.hpp"
#include "hillclimb/randomrestart.hpp"
#include "advanced/genetic.hpp"

using namespace std;

int main() {
    MagicFive cube;
    cube.showCube();

    Solver* solver = new RandomRestart(cube, 100000);
    solver->solve();
    solver->showCube();
    return 0;
}