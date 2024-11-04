#include "plot.hpp"

void Plot::plotObjectiveFunctions(const vector<int>& objective_functions) {
    plt::clf();
    plt::plot(objective_functions);
    plt::title("Objective Functions");
    plt::xlabel("Iterations");
    plt::ylabel("Objective Function");
    string filename = "./output/objective_functions.png";
    plt::save(filename);
}

void Plot::plotMaxObjectiveFunctions(const vector<int>& objective_functions) {
    plt::clf();
    plt::plot(objective_functions);
    plt::title("Max Objective Functions");
    plt::xlabel("Iterations");
    plt::ylabel("Objective Function");
    string filename = "./output/max_objective_functions.png";
    plt::save(filename);
}

void Plot::plotAvgObjectiveFunctions(const vector<int>& objective_functions) {
    plt::clf();
    plt::plot(objective_functions);
    plt::title("Average Objective Functions");
    plt::xlabel("Iterations");
    plt::ylabel("Objective Function");
    string filename = "./output/avg_objective_functions.png";
    plt::save(filename);
}

void Plot::plotAcceptanceProbabilities(const vector<float>& acceptance_probabilities) {
    plt::clf();
    plt::plot(acceptance_probabilities);
    plt::title("Acceptance Probabilities");
    plt::xlabel("Iterations");
    plt::ylabel("Acceptance Probability");
    string filename = "./output/acceptance_probabilities.png";
    plt::save(filename);
}