#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
// Inluir el archivo de cabecera bloom.h
#include "bloom.h"

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

vector<long long> extraerPrimos() {
    vector<long long> extraccion;
    ifstream file("primos.csv");

    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string valor;
        while (getline(ss, valor, ',')) {
            int numero = stoll(valor);  
            extraccion.push_back(numero);
        }
    }

    file.close();
    return extraccion;
}



int main() {
    /*
    vector<Combination> combinations = generateCombinations(N_values, p_values);
    vector<long long> v_primos = extraerPrimos();

    BloomFilter bloom_prueba(0,1,v_primos);

    // Imprimir las combinaciones
    for (const auto& combination : combinations) {
        cout << "N: " << combination.N << ", p: " << combination.p << endl;
    }
    */
   // Bloom de prueba
   // Hacemos un print anunciando el inicio de la prueba
    cout << "Inicio de la prueba" << endl;
    vector<long long> v_primos = extraerPrimos();
    cout << "Se añade primo en bloom" << endl;
    BloomFilter prueba(10, 1, v_primos);
    
    string sprueba = "5 STAR CHRISTMAS";
    // Hacemos un print anunciando la adición de un sprueba
    cout << "Añadiendo string al bloom " << sprueba << endl;
    prueba.add(sprueba);
    cout << "**********************" << endl;
    // Imprimimos el primer primo
    cout << "primo[0] " << v_primos[0] << endl;
    cout << prueba.hash(sprueba, v_primos[0]) << endl;
    // calculamos k, la cantidad de funciones hash
    double m = 1<<16;
    double n = 1024;
    ll kk = ceil( (m/n) * log(2));
    cout <<  "k: "<< kk << endl; 

    return 0;
}

// how to compile: g++ -std=c++11 main.cpp -o mainPenguin


// Nos damos un valor de m (bits del filtro).
// Calculamos k (número de funciones hash) con la fórmula k = (m/n) * ln(2)
// Para calcular la probabilidad de falsos positivos, usamos la siguiente fórmula
// P = (1 - e^(-kn/m))^k

// Valores de N = {1024, 4096, 194481, 65536}
//           |N| ∈ {2^10,2^12,2^14,2^16}
// Con esto podemos calcular el valor de m, que son los bits del arreglo