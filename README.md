# tarea3-logs
 La tarea 3 de logs 2024, otoño

# Tareas por hacer

* En filtro de bloom, hacer la wea de los primos. (**Tommy**)
* Investigar como manipular CSV en C++. (**Pepe**)
* Hacer búsqueda secuencial de un str en el CSV. (**Pepe**)
* Calcular valores de p y m en función de N. (**Tommy**)
* Investigar la probabilidad de fallo teorica. (**(Metal)Pipe**)
* Crear funciones de experimentos para cada combinacion de (|N|,p). (**Prox reunión**)
* Crear archivo del informe en Overleaf. (**(Metal)Pipe**)


## Manipulación de CSV en C++

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
```

### Explicación del código
* Función readCSV:
    * Abre el archivo CSV usando std::ifstream.
    * Usa un std::vector<std::vector<std::string>> para almacenar los datos del archivo.
    * Lee cada línea del archivo usando std::getline.
    * Usa un std::stringstream para dividir la línea en celdas separadas por comas.
    * Almacena cada celda en un vector de cadenas (row).
    * Añade cada fila (row) al vector de datos (data).
    * Cierra el archivo después de leerlo.

* Función searchCSV:
    * Esta función toma como parámetros el vector de datos leído del CSV (data) y el string que se desea buscar (target).
    * Recorre cada fila (row) del vector data.
    * Dentro de cada fila, recorre cada celda (cell).
    * Si encuentra una celda que coincide con el string objetivo (target), retorna true.
    * Si termina de recorrer todas las celdas sin encontrar el string, retorna false.

* Función main:
    * Define el nombre del archivo CSV.
    * Llama a la función readCSV para leer el archivo y obtener los datos.
    * Define el string objetivo (target) que se desea buscar.
    * Llama a la función searchCSV y muestra un mensaje indicando si el string fue encontrado o no en el archivo CSV.