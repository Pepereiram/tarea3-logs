#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Función para leer el archivo CSV
vector<vector<string>> readCSV(const std::string& filename) {
    ifstream file(filename);
    vector<vector<string>> data;
    string line, cell;

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<string> row;
            stringstream lineStream(line);

            while (getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }
            data.push_back(row);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return data;
}

// Función para buscar un string en el CSV
bool searchCSV(const vector<vector<string>>& data, const string& target) {
    for (const auto& row : data) {
        for (const auto& cell : row) {
            if (cell == target) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string filename = "data.csv";
    vector<std::vector<std::string>> csvData = readCSV(filename);

    string target = "busqueda";
    if (searchCSV(csvData, target)) {
        cout << "El string '" << target << "' fue encontrado en el archivo CSV." << endl;
    } else {
        cout << "El string '" << target << "' no fue encontrado en el archivo CSV." << endl;
    }

    return 0;
}