import re
import matplotlib.pyplot as plt

def parse_results(file_path):
    """
    Parsea los resultados de un archivo de texto y devuelve un diccionario con los datos.

    Parameters
    ----------
    file_path : str
        La ruta al archivo de texto con los resultados.
    
    Returns
    -------
    dict
        Un diccionario con los resultados parseados
    """

    results = {}
    with open(file_path, 'r') as file:
        lines = file.readlines()
        current_N = None
        for line in lines:
            line = line.strip()
            if line.startswith("(|N|"):
                match = re.match(r"\(\|N\|\: (\d+), p: ([0-1](?:\.\d+)?)\)", line)
                if match:
                    current_N = int(match.group(1))
                    p = float(match.group(2))
                    if current_N not in results:
                        results[current_N] = {'p': [], 'seq_times': [], 'bloom_times': [], 'false_positive_rates': []}
                    results[current_N]['p'].append(p)
            elif line.startswith("Tiempo promedio busqueda secuencial para:"):
                seq_time = float(line.split(":")[1].strip())
                results[current_N]['seq_times'].append(seq_time)
            elif line.startswith("Tiempo promedio filtro de Bloom:"):
                bloom_time = float(line.split(":")[1].strip())
                results[current_N]['bloom_times'].append(bloom_time)
            elif line.startswith("Porcentaje falsos positivos:"):
                false_positive_rate = float(line.split(":")[1].strip())
                results[current_N]['false_positive_rates'].append(false_positive_rate)
    return results


def plot_results(results):
    """
    Grafica los resultados obtenidos de la función parse_results.

    Parameters
    ----------
    results : dict
        Un diccionario con los resultados parseados
    
    Returns
    -------
    None
    """
    for N, data in results.items():
        p_values = data['p']
        seq_times = data['seq_times']
        bloom_times = data['bloom_times']
        
        plt.figure(figsize=(10, 6))
        plt.plot(p_values, seq_times, label='Búsqueda Secuencial', marker='o')
        plt.plot(p_values, bloom_times, label='Filtro de Bloom', marker='o')
        
        plt.title(f'Tiempos de Búsqueda vs p para |N| = {N}')
        plt.xlabel('p')
        plt.ylabel('Tiempo promedio (s)')
        plt.legend()
        plt.grid(True)
        plt.show()


# Main
if __name__ == '__main__':

    # Obtenemos los resultados
    results = parse_results('resultados.txt')
    # Graficamos los resultados
    plot_results(results)
    # Anunciamos el fin del programa
    print("Fin del programa")