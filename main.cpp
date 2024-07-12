#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Definir las posibles combinaciones de N y p
vector<int> N_values = {1024, 4096, 194481, 65536};
vector<double> p_values = {0, 0.25, 0.5, 0.75, 1.0};

struct Combination {
    int N;
    double p;
};

vector<Combination> generateCombinations(const vector<int>& N_values,
                                              const vector<double>& p_values) {
    vector<Combination> combinations;
    for (int N : N_values) {
        for (double p : p_values) {
            combinations.push_back({N, p});
        }
    }
    return combinations;
}

int main() {
    vector<Combination> combinations = generateCombinations(N_values, p_values);

    // Imprimir las combinaciones
    for (const auto& combination : combinations) {
        cout << "N: " << combination.N << ", p: " << combination.p << endl;
    }

    return 0;
}