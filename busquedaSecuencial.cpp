#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Función para leer el archivo CSV
std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> data;
    std::string line, cell;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::vector<std::string> row;
            std::stringstream lineStream(line);

            while (std::getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }
            data.push_back(row);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return data;
}

// Función para buscar un string en el CSV
bool searchCSV(const std::vector<std::vector<std::string>>& data, const std::string& target) {
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
    std::string filename = "data.csv";
    std::vector<std::vector<std::string>> csvData = readCSV(filename);

    std::string target = "busqueda";
    if (searchCSV(csvData, target)) {
        std::cout << "El string '" << target << "' fue encontrado en el archivo CSV." << std::endl;
    } else {
        std::cout << "El string '" << target << "' no fue encontrado en el archivo CSV." << std::endl;
    }

    return 0;
}