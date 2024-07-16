#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Función para leer el archivo CSV con solo una columna
vector<string> readCSV(const string& filename) {
    ifstream file(filename);
    vector<string> data;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            // Verificar que la línea no esté vacía antes de agregarla al vector
            if (!line.empty()) {
                data.push_back(line);
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return data;
}


// Función para buscar un string en el vector de strings
bool searchCSV(const vector<string>& data, const string& target) {
    for (const string& row : data) {
        if (row == target) {
            return true;
        }
    }
    return false;
}
