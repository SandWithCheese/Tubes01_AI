#include "plot.hpp"

void Plot::plotObjectiveFunctions(const vector<int>& objective_functions) {
    plt::plot(objective_functions);
    plt::title("Objective Functions");
    plt::xlabel("Iterations");
    plt::ylabel("Objective Function");
    plt::show();
}

void Plot::plotMaxObjectiveFunctions(const vector<int>& objective_functions) {
    plt::plot(objective_functions);
    plt::title("Max Objective Functions");
    plt::xlabel("Iterations");
    plt::ylabel("Objective Function");
    plt::show();
}

void Plot::plotAvgObjectiveFunctions(const vector<int>& objective_functions) {
    plt::plot(objective_functions);
    plt::title("Average Objective Functions");
    plt::xlabel("Iterations");
    plt::ylabel("Objective Function");
    plt::show();
}

void Plot::plotAcceptanceProbabilities(const vector<float>& acceptance_probabilities) {
    plt::plot(acceptance_probabilities);
    plt::title("Acceptance Probabilities");
    plt::xlabel("Iterations");
    plt::ylabel("Acceptance Probability");
    plt::show();
}