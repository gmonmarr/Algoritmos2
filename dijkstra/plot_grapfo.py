import matplotlib.pyplot as plt
import networkx as nx
import sys

# Function to read the adjacency matrix from a txt file
def leer_matriz_adyacencia(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()

    # Skip the first line (header "Matriz de adyacencia:")
    matriz = []
    for line in lines[1:]:
        fila = list(map(int, line.split()))
        matriz.append(fila)

    return matriz

# Function to create edges list from adjacency matrix
def crear_aristas_desde_matriz(matriz):
    edges = []
    for i in range(len(matriz)):
        for j in range(i + 1, len(matriz)):  # Avoid duplicate edges in undirected graph
            if matriz[i][j] != 0:  # There is an edge with a weight
                edges.append((i, j, matriz[i][j]))
    return edges

# Function to create and save the graph as an image
def create_graph(edges, photo_name):
    G = nx.Graph()
    
    # Add edges to the graph
    G.add_weighted_edges_from(edges)

    # Create a figure with a higher DPI (resolution) and larger size for better readability
    plt.figure(figsize=(12, 12), dpi=200)

    # Use Kamada-Kawai layout for force-directed node arrangement
    pos = nx.kamada_kawai_layout(G)  # Kamada-Kawai layout minimizes energy for better distribution

    # Draw the graph with smaller node sizes and larger node labels for better readability
    nx.draw(G, pos, with_labels=True, node_size=500, font_size=14, font_weight='bold', node_color='lightblue')

    # Get and draw edge labels (weights)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_size=12)

    # Save the graph as an image with higher resolution
    plt.savefig(photo_name, format="PNG", bbox_inches='tight')

    # Close the plot to avoid displaying it
    plt.close()

# Main execution
if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python script.py <path_to_txt_file> <photo_name>")
        sys.exit(1)

    # Read the file path and the output photo name from the command-line arguments
    file_path = sys.argv[1]
    photo_name = sys.argv[2] + ".png"  # Append .png if the user doesn't provide an extension

    # Read the adjacency matrix from the txt file
    matriz = leer_matriz_adyacencia(file_path)

    # Convert the adjacency matrix into a list of edges
    edges = crear_aristas_desde_matriz(matriz)

    # Call the function to create and save the graph as an image
    create_graph(edges, photo_name)

    print(f"Graph saved as {photo_name}")
