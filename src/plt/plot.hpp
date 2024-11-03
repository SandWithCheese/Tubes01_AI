#ifndef PLOT_HPP
#define PLOT_HPP

#include "matplotlibcpp.h"
#include <vector>

using namespace std;
namespace plt = matplotlibcpp;

class Plot {
public:
    static void plotObjectiveFunctions(const vector<int>& objective_functions);
    static void plotMaxObjectiveFunctions(const vector<int>& objective_functions);
    static void plotAvgObjectiveFunctions(const vector<int>& objective_functions);
    static void plotAcceptanceProbabilities(const vector<float>& acceptance_probabilities);
};

#endif
