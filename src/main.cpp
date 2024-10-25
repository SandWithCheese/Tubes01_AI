#include <iostream>
#include "cube/magicfive.hpp"
#include "hillclimb/stochastic.hpp"
#include "advanced/genetic.hpp"

using namespace std;

int main() {
    MagicFive cube;
    cube.showCube();

    Solver* solver = new Genetic(cube, 1000000, 5096, 5);
    solver->solve();
    solver->showCube();
    return 0;
}