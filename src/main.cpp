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
#include "plt/plot.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    MagicFive cube;
    cube.showCube();
    MagicFive solvedCube;
    high_resolution_clock::time_point start, stop;
    milliseconds duration;

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
            start = high_resolution_clock::now();
            sa.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            solvedCube.setData(sa.getCube().getData());
            solvedCube.showCube();
            vector<int> obj = sa.getObjectiveFunctions();
            Plot::plotObjectiveFunctions(obj);
            break;
        }
        case 2: {
            SidewaysMove sm = SidewaysMove(cube, 1000); // Dummy value
            start = high_resolution_clock::now();
            sm.solve(); // Immplement
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            solvedCube.setData(sm.getCube().getData());
            solvedCube.showCube();
            vector<int> obj = sm.getObjectiveFunctions();
            Plot::plotObjectiveFunctions(obj);
            break;
        }
        case 3: {
            RandomRestart rr = RandomRestart(cube);
            start = high_resolution_clock::now();
            rr.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            solvedCube.setData(rr.getCube().getData());
            solvedCube.showCube();
            vector<int> obj = rr.getObjectiveFunctions();
            Plot::plotObjectiveFunctions(obj);
            break;
        }
        case 4: {
            Stochastic st = Stochastic(cube);
            start = high_resolution_clock::now();
            st.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            solvedCube.setData(st.getCube().getData());
            solvedCube.showCube();
            vector<int> obj = st.getObjectiveFunctions();
            Plot::plotObjectiveFunctions(obj);
            break;
        }
        case 5: {
            SimulatedAnnealing sa = SimulatedAnnealing(cube, 10000000, 1, 0.5); // Dummy value
            start = high_resolution_clock::now();
            sa.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            solvedCube.setData(sa.getCube().getData());
            solvedCube.showCube();
            vector<float> obj = sa.getAcceptanceProbabilities();
            Plot::plotAcceptanceProbabilities(obj);
            break;
        }
        case 6: {
            Genetic gen = Genetic(cube); // Dummy value
            start = high_resolution_clock::now();
            gen.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            solvedCube.setData(gen.getCube().getData());
            solvedCube.showCube();
            vector<int> max_obj = gen.getMaxObjectiveFunctions();
            vector<int> avg_obj = gen.getAvgObjectiveFunctions();
            Plot::plotMaxObjectiveFunctions(max_obj);
            Plot::plotAvgObjectiveFunctions(avg_obj);
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