#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;
// Inluir el archivo de cabecera bloom.h
#include "bloom.h"
#include "busquedaSecuencial.h"
typedef vector<vector<string>> CSVData;

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

// Función para generar conjuntos de datos en proporción P de elementos que están en el filtro
// y 1-P de elementos que no están en el filtro
vector<string> generateData(double P, int n, CSVData& babys, CSVData& films) {
    vector<string> data;
    for (int i = 0; i < n; ++i) {
        string s = "string" + to_string(i);
        if (bloom.lookup(s) && (rand() % 100) < P * 100) {
            data.push_back(s);
        } else if (!bloom.lookup(s) && (rand() % 100) < (1 - P) * 100) {
            data.push_back(s);
        }
    }
    return data;
}




int main() {
    cout << "------------------------- INICIO -------------------------" << endl;
    // Creamos las combinaciones de N y p
    vector<Combination> combinations = generateCombinations(N_values, p_values);
    // Extraemos los primos
    vector<long long> primos = extraerPrimos();
    // Leemos los CSV de Popular-Baby-Names-Final.csv y Film-Names.csv
    CSVData babys = readCSV("Popular-Baby-Names-Final.csv");
    CSVData films = readCSV("Film-Names.csv");
    // En un ciclo, para cada combinación de N y p, generamos un conjunto de datos
    // con proporción p de elementos en babys y 1-p de elementos en films
    
    for(const Combination& comb : combinations){
        cout << "Test para N: " << comb.N << " p: " << comb.p << endl;
        // Creamos 
        vector<string> babyBloom = bloomData(comb.N, comb.p, babys);
        // Creamos los conjuntos de datos
        vector<string> data = generateData(comb.N, comb.p, babyBloom, films);
        // Elegir m y k en funcion de N 
        // m = -N * ln(p) / (ln(2))^2
        // k = m / N * ln(2)
        // inicializar filtrro de bloom
        BloomFilter bloom(comb.N, comb.p, primos);
      
  

        // Generamos el conjunto de datos
        // vector<string> data = generateData(bloom, comb.p, 1000);
        // Agregamos los elementos al filtro
        // for (const string& s : data) {
        //     bloom.add(s);
        // }
        // Calculamos la probabilidad de falsos positivos
        // double P = bloom.calculateFalsePositiveProbability();
        // cout << "Probabilidad de falsos positivos: " << P << endl;
    }

    return 0;
}

// how to compile: g++ -std=c++11 main.cpp -o mainPenguin


// Nos damos un valor de m (bits del filtro).
// Calculamos k (número de funciones hash) con la fórmula k = (m/n) * ln(2)
// Para calcular la probabilidad de falsos positivos, usamos la siguiente fórmula
// P = (1 - e^(-kn/m))^k
