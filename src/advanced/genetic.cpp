#include "genetic.hpp"

Genetic::Genetic() : Solver() {
    iterations = 1000;
    population_size = 100;
    threshold = 10;
}

Genetic::Genetic(int iterations, int population_size, int threshold) : Solver() {
    this->iterations = iterations;
    this->population_size = population_size;
    this->threshold = threshold;
}

Genetic::Genetic(const MagicFive& other) : Solver(other) {
    iterations = 1000;
    population_size = 100;
    threshold = 10;
}

Genetic::Genetic(const MagicFive& other, int iterations, int population_size, int threshold) : Solver(other) {
    this->iterations = iterations;
    this->population_size = population_size;
    this->threshold = threshold;
}

Genetic::~Genetic() {}

vector<int> Genetic::getMaxObjectiveFunctions() {
    return max_objective_functions;
}

vector<int> Genetic::getAvgObjectiveFunctions() {
    return avg_objective_functions;
}

void Genetic::setMaxObjectiveFunctions(const vector<int>& new_objective_functions) {
    max_objective_functions = new_objective_functions;
}

void Genetic::setAvgObjectiveFunctions(const vector<int>& new_objective_functions) {
    avg_objective_functions = new_objective_functions;
}

void Genetic::appendMaxObjectiveFunction(int new_objective_function) {
    max_objective_functions.push_back(new_objective_function);
}

void Genetic::appendAvgObjectFunction(int new_objective_function) {
    avg_objective_functions.push_back(new_objective_function);
}

int Genetic::getIterations() {
    return iterations;
}

void Genetic::setIterations(int iterations) {
    this->iterations = iterations;
}

int Genetic::getPopulationSize() {
    return population_size;
}

void Genetic::setPopulationSize(int population_size) {
    this->population_size = population_size;
}

vector<MagicFive> Genetic::generatePopulations() {
    vector<MagicFive> populations;
    for (int i = 0; i < population_size; i++) {
        populations.push_back(MagicFive().generateRandomCube());
    }
    return populations;
}

MagicFive Genetic::selection(vector<MagicFive>& populations) {
    vector<int> fitnesses;
    for (const auto& population : populations) {
        fitnesses.push_back(population.fitnessFunction());
    }

    int total_fitness = accumulate(fitnesses.begin(), fitnesses.end(), 0);
    int random_fitness = rand() % total_fitness;

    int sum = 0;
    for (int i = 0; i < populations.size(); i++) {
        sum += fitnesses[i];
        if (sum >= random_fitness) {
            return populations[i];
        }
    }

    return populations[0];
}

MagicFive Genetic::crossover(const MagicFive& parent1, const MagicFive& parent2) {
    vector<int> parent1_flat = MagicFive::matrixToList(parent1.getData());
    vector<int> parent2_flat = MagicFive::matrixToList(parent2.getData());

    int length = parent1_flat.size();
    vector<int> child_flat = parent1_flat;

    int start = rand() % length;
    int end = rand() % length;

    if (start > end) {
        swap(start, end);
    }

    for (int i = start; i < end; ++i) {
        int parent2_value = parent2_flat[i];
        int child_value = child_flat[i];

        if (parent2_value != child_value) {
            auto it = find(child_flat.begin(), child_flat.end(), parent2_value);
            if (it != child_flat.end()) {
                int index = distance(child_flat.begin(), it);
                child_flat[index] = child_value;
            }
            child_flat[i] = parent2_value;
        }
    }

    vector<vector<int>> child_data = MagicFive::listToMatrix(child_flat);

    return MagicFive(child_data);
}

MagicFive Genetic::mutation(const MagicFive& child) {
    vector<int> child_flat = MagicFive::matrixToList(child.getData());
    int rotate_count = rand() % 125;

    rotate(child_flat.begin(), child_flat.begin() + rotate_count, child_flat.end());

    vector<vector<int>> child_data = MagicFive::listToMatrix(child_flat);

    return MagicFive(child_data);
}

void Genetic::solve() {
    vector<MagicFive> populations = generatePopulations();
    bool found = false;

    for (int i = 0; i < iterations; i++) {
        vector<MagicFive> new_populations;
        int max_objective_function = -109;
        int avg_objective_function = 0;
        for (int j = 0; j < population_size; j++) {
            MagicFive parent1 = selection(populations);
            MagicFive parent2 = selection(populations);

            MagicFive child1 = crossover(parent1, parent2);
            MagicFive child2 = crossover(parent2, parent1);

            int child1_mutation = rand() % 100;
            if (child1_mutation < threshold) {
                child1 = mutation(child1);
            }

            new_populations.push_back(child1);

            int child2_mutation = rand() % 100;
            if (child2_mutation < threshold) {
                child2 = mutation(child2);
            }

            new_populations.push_back(child2);

            if (child1.fitnessFunction() == 109 || child2.fitnessFunction() == 109) {
                found = true;
            }

            max_objective_function = max(max_objective_function, max(child1.objectiveFunction(), child2.objectiveFunction()));
            avg_objective_function += (child1.objectiveFunction() + child2.objectiveFunction());
        }

        avg_objective_function /= (population_size * 2);

        appendMaxObjectiveFunction(max_objective_function);
        appendAvgObjectFunction(avg_objective_function);

        populations = new_populations;

        if (found) {
            break;
        }
    }

    MagicFive best_cube = *max_element(populations.begin(), populations.end(), [](const MagicFive& a, const MagicFive& b) {
        return a.fitnessFunction() < b.fitnessFunction();
        });

    cube.setData(best_cube.getData());

    cout << "Solution found in " << iterations << " iterations." << endl;
    cout << "Objective function: " << best_cube.objectiveFunction() << endl;
}