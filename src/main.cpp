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
#include "visualize/magic_cube.cpp"
#include "plt/plot.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
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
            cout << "Final Cube:" << endl;
            solvedCube.setData(sa.getCube().getData());
            solvedCube.showCube();
            cout << endl;
            vector<int> obj = sa.getObjectiveFunctions();
            Plot::plotObjectiveFunctions(obj);
            break;
        }
        case 2: {
            int maxSidewaysMoves;
            cout << "Input maximum sideways moves: ";
            if (!(cin >> maxSidewaysMoves) || maxSidewaysMoves < 0) {
                cout << "Invalid input. Using default value of 100." << endl;
                maxSidewaysMoves = 100;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            SidewaysMove sm = SidewaysMove(cube, maxSidewaysMoves);
            start = high_resolution_clock::now();
            sm.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            cout << "Final Cube:" << endl;
            solvedCube.setData(sm.getCube().getData());
            solvedCube.showCube();
            cout << endl;
            vector<int> obj = sm.getObjectiveFunctions();
            Plot::plotObjectiveFunctions(obj);
            break;
        }
        case 3: {
            int max_restart;
            cout << "Input maximum restarts: ";
            if (!(cin >> max_restart) || max_restart < 0) {
                cout << "Invalid input. Using default value of 1000." << endl;
                max_restart = 1000;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            RandomRestart rr = RandomRestart(cube, max_restart);
            start = high_resolution_clock::now();
            rr.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            cout << "Final Cube:" << endl;
            solvedCube.setData(rr.getCube().getData());
            solvedCube.showCube();
            cout << endl;
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
            cout << "Final Cube:" << endl;
            solvedCube.setData(st.getCube().getData());
            solvedCube.showCube();
            cout << endl;
            vector<int> obj = st.getObjectiveFunctions();
            Plot::plotObjectiveFunctions(obj);
            break;
        }
        case 5: {
            SimulatedAnnealing sa = SimulatedAnnealing();
            start = high_resolution_clock::now();
            sa.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            cout << "Final Cube:" << endl;
            solvedCube.setData(sa.getCube().getData());
            solvedCube.showCube();
            cout << endl;
            vector<int> obj = sa.getObjectiveFunctions();
            vector<float> accProb = sa.getAcceptanceProbabilities();
            Plot::plotObjectiveFunctions(obj);
            Plot::plotAcceptanceProbabilities(accProb);
            break;
        }
        case 6: {
            int population_size, iterations, threshold;
            cout << "Input population size: ";
            if (!(cin >> population_size) || population_size <= 0) {
                cout << "Invalid input. Using default value of 100." << endl;
                population_size = 100;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Input iterations: ";
            if (!(cin >> iterations) || iterations <= 0) {
                cout << "Invalid input. Using default value of 1000." << endl;
                iterations = 1000;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Input threshold (0-100): ";
            if (!(cin >> threshold) || threshold < 0 || threshold > 100) {
                cout << "Invalid input. Using default value of 10." << endl;
                threshold = 10;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            Genetic gen = Genetic(cube, iterations, population_size, threshold);
            start = high_resolution_clock::now();
            gen.solve();
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            cout << "Execution time: " << duration.count() << " ms" << endl;
            cout << "Final Cube:" << endl;
            solvedCube.setData(gen.getCube().getData());
            solvedCube.showCube();
            cout << endl;
            vector<int> max_obj = gen.getMaxObjectiveFunctions();
            vector<int> avg_obj = gen.getAvgObjectiveFunctions();
            Plot::plotMaxObjectiveFunctions(max_obj);
            Plot::plotAvgObjectiveFunctions(avg_obj);
            break;
        }
        case 7: {
            cout << "Base cube or solved cube?" << endl;
            cout << "1. Base cube" << endl;
            cout << "2. Solved cube" << endl;
            int choice;
            if (!(cin >> choice) || choice < 1 || choice > 2) {
                cout << "Invalid input. Using base cube." << endl;
                choice = 1;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Visualisasi" << endl;
            if (choice == 1) {
                cube.showCube();
                CubeVisualizer::visualize(argc, argv, cube);
            }
            else {
                solvedCube.showCube();
                CubeVisualizer::visualize(argc, argv, solvedCube);
            }
            break;
        }
        case 8: {
            MagicFive newCube;
            cube.setData(newCube.getData());
            cube.showCube();
            break;
        }
        case 9: {
            exit(0);
            break;
        }
        default: {
            break;
        }
        }
    }

    return 0;
}