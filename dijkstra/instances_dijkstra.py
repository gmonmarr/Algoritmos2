import random
import sys

def generar_grafo(num_nodos, num_aristas, peso_maximo=30):
    # Inicializa una lista de adyacencia
    grafo = {i: [] for i in range(num_nodos)}
    aristas_creadas = set()

    while len(aristas_creadas) < num_aristas:
        nodo1 = random.randint(0, num_nodos - 1)
        nodo2 = random.randint(0, num_nodos - 1)

        if nodo1 != nodo2 and (nodo1, nodo2) not in aristas_creadas and (nodo2, nodo1) not in aristas_creadas:
            peso = random.randint(10, peso_maximo)
            grafo[nodo1].append((nodo2, peso))
            grafo[nodo2].append((nodo1, peso))
            aristas_creadas.add((nodo1, nodo2))

    return grafo

def imprimir_matriz_adyacencia(grafo, file_name):
    num_nodos = len(grafo)
    matriz = [[0 for _ in range(num_nodos)] for _ in range(num_nodos)]
    
    # Crear la matriz de adyacencia
    for nodo, conexiones in grafo.items():
        for vecino, peso in conexiones:
            matriz[nodo][vecino] = peso
            matriz[vecino][nodo] = peso  # Grafo no dirigido

    # Guardar la matriz en un archivo de texto
    with open(file_name, 'w') as f:
        f.write("Matriz de adyacencia:\n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")

if __name__ == "__main__":
    if len(sys.argv) < 4:
        print("Usage: python script.py <num_nodos> <num_aristas> <output_filename>")
        sys.exit(1)

    num_nodos = int(sys.argv[1])
    num_aristas = int(sys.argv[2])
    file_name = sys.argv[3]  # Nombre del archivo de salida pasado por el usuario

    # Generar y guardar el grafo en un archivo
    grafo = generar_grafo(num_nodos, num_aristas)
    imprimir_matriz_adyacencia(grafo, file_name)
