#include <iostream>
#include <vector>
#include <cmath>

// Definir las posibles combinaciones de N y p
std::vector<int> N_values = {1024, 4096, 194481, 65536};
std::vector<double> p_values = {0, 0.25, 0.5, 0.75, 1.0};

struct Combination {
    int N;
    double p;
};

std::vector<Combination> generateCombinations(const std::vector<int>& N_values,
                                              const std::vector<double>& p_values) {
    std::vector<Combination> combinations;
    for (int N : N_values) {
        for (double p : p_values) {
            combinations.push_back({N, p});
        }
    }
    return combinations;
}

int main() {
    std::vector<Combination> combinations = generateCombinations(N_values, p_values);

    // Imprimir las combinaciones
    for (const auto& combination : combinations) {
        std::cout << "N: " << combination.N << ", p: " << combination.p << std::endl;
    }

    return 0;
}