#include <iostream>
#include <chrono>
#include "cube/magicfive.hpp"
#include "hillclimb/stochastic.hpp"
#include "hillclimb/randomrestart.hpp"
#include "advanced/genetic.hpp"
#include "hillclimb/steepestascent.hpp"
#include "hillclimb/sidewaysmove.hpp"
#include "advanced/simulatedannealing.hpp"
#include "advanced/genetic.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    MagicFive cube;
    cube.showCube();

    int choice = 0;
    while (choice < 1 || choice > 6) {
        try {
            cout << "Choose the algorithm to solve the Magic Five Cube:" << endl;
            cout << "1. Hill Climbing: Steepest Ascent" << endl;
            cout << "2. Hill Climbing: Sideways Move" << endl;
            cout << "3. Hill Climbing: Random Restart" << endl;
            cout << "4. Hill Climbing: Stochastic" << endl;
            cout << "5. Simulated Annealing" << endl;
            cout << "6. Genetic Algorithm" << endl;
            cout << "Choice:";
            cin >> choice;
        } catch (const exception& e) {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    auto start = high_resolution_clock::now();

    switch (choice) {
        case 1: {
            SteepestAscent sa = SteepestAscent(cube);
            sa.solve();
            break;
        }
        case 2: {
            SidewaysMove sm = SidewaysMove(cube, 10000); 
            sm.solve(); 
            break;
        }
        case 3: {
            RandomRestart rr = RandomRestart(cube, 10000); 
            rr.solve();
            break;
        }
        case 4: {
            Stochastic st = Stochastic(cube);
            st.solve();
            break;
        }
        case 5: {
            SimulatedAnnealing sa = SimulatedAnnealing(cube, 10000, 0.001, 1); // Dummy value
            sa.solve();
            break;
        }
        case 6: {
            Genetic gen = Genetic(cube); // Dummy value
            gen.solve();
            break;
        }
        default : {
            Stochastic st = Stochastic(cube);
            st.solve();
            break;
        }

    }

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << "Execution time: " << duration.count() << " ms" << endl;

    return 0;
}