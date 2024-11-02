#include <iostream>
#include "cube/magicfive.hpp"
#include "hillclimb/stochastic.hpp"
#include "hillclimb/randomrestart.hpp"
#include "advanced/genetic.hpp"
#include "hillclimb/steepestascent.hpp"
#include "hillclimb/sidewaysmove.hpp"
#include "advanced/simulatedannealing.hpp"
#include "advanced/genetic.hpp"

using namespace std;

int main() {
    MagicFive cube;
    cube.showCube();
    MagicFive solvedCube;

    while (true) {
        int choice = 0;
        while (choice < 1 || choice > 9) {
            try {
                cout << "Choose the algorithm to solve the Magic Five Cube:" << endl;
                cout << "1. Hill Climbing: Steepest Ascent" << endl;
                cout << "2. Hill Climbing: Sideways Move" << endl;
                cout << "3. Hill Climbing: Random Restart" << endl;
                cout << "4. Hill Climbing: Stochastic" << endl;
                cout << "5. Simulated Annealing" << endl;
                cout << "6. Genetic Algorithm" << endl;
                cout << "7. Visualize Cube" << endl;
                cout << "8. Reset Cube" << endl;
                cout << "9. Exit" << endl;
                cout << "Choice:";
                cin >> choice;
            }
            catch (const exception& e) {
                cout << "Invalid input. Please try again." << endl;
            }
        }

        switch (choice) {
        case 1: {
            SteepestAscent sa = SteepestAscent(cube);
            sa.solve();
            solvedCube.setData(sa.getCube().getData());
            solvedCube.showCube();
            break;
        }
        case 2: {
            SidewaysMove sm = SidewaysMove(cube, 1000); // Dummy value
            sm.solve(); // Immplement
            solvedCube.setData(sm.getCube().getData());
            solvedCube.showCube();
            break;
        }
        case 3: {
            RandomRestart rr = RandomRestart(cube, 1000); // Dummy value
            rr.solve();
            solvedCube.setData(rr.getCube().getData());
            solvedCube.showCube();
            break;
        }
        case 4: {
            Stochastic st = Stochastic(cube);
            st.solve();
            solvedCube.setData(st.getCube().getData());
            solvedCube.showCube();
            break;
        }
        case 5: {
            SimulatedAnnealing sa = SimulatedAnnealing(cube, 10000, 0.001, 1); // Dummy value
            sa.solve();
            solvedCube.setData(sa.getCube().getData());
            solvedCube.showCube();
            break;
        }
        case 6: {
            Genetic gen = Genetic(cube); // Dummy value
            gen.solve();
            solvedCube.setData(gen.getCube().getData());
            solvedCube.showCube();
            break;
        }
        case 7: {
            cout << "Visualisasi" << endl;
            break;
        }
        case 8: {
            MagicFive newCube;
            cube.setData(newCube.getData());
            solvedCube.showCube();
            break;
        }
        case 9: {
            exit(0);
            break;
        }
        default: {
            continue;
        }
        }
    }

    return 0;
}