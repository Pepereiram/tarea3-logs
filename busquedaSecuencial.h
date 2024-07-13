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
            data.push_back(line);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return data;
}


// vector<vector<string>> readCSV(const string& filename) {
//     ifstream file(filename);
//     vector<vector<string>> data;
//     string line, cell;

//     if (file.is_open()) {
//         while (getline(file, line)) {
//             vector<string> row;
//             stringstream lineStream(line);

//             while (getline(lineStream, cell, ',')) {
//                 row.push_back(cell);
//             }
//             data.push_back(row);
//         }
//         file.close();
//     } else {
//         cerr << "Unable to open file: " << filename << endl;
//     }

//     return data;
// }

// Función para buscar un string en el vector de strings
bool searchCSV(const vector<string>& data, const string& target) {
    for (const string& row : data) {
        if (row == target) {
            return true;
        }
    }
    return false;
}
