#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;


//extrae numeros primos del archivo primos.csv
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

int main(){
    vector<long long> prueba = extraerPrimos();
    cout << prueba[0] << endl;
    cout << prueba[10000]<< endl; 
    return 0;
}
// g++ -std=c++11 obtenerPrimos.cpp -o op