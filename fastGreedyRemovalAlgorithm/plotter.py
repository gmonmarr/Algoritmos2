# Este archivo grafica los archivos .pof originales y reducidos en 2D o 3D.
# Se espera que los archivos .pof originales estén en una carpeta y los archivos .pof reducidos estén en otra.
# se debe correr con el siguiente comando: python plotter.py <original_folder> <reduced_folder>

import os
import sys
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# Function to read coordinates from a file
def read_coordinates(filename):
    coordinates = []
    with open(filename, 'r') as file:
        first_line = file.readline().strip()
        if first_line.startswith('#'):
            # Skip the first line if it starts with '#'
            print(f"Skipping first line in {filename}: {first_line}")
        else:
            # If the first line does not start with '#', process it as data
            values = list(map(float, first_line.split()))
            coordinates.append(values)
        
        for line in file:
            values = list(map(float, line.split()))
            coordinates.append(values)
    
    return np.array(coordinates)

# Function to determine the dimensionality of the coordinates
def determine_dimension(coordinates):
    return coordinates.shape[1]

# Function to plot and save 2D coordinates
def plot_2d(original_coords, reduced_coords, title_suffix, save_path):
    plt.figure(figsize=(12, 6))  # Increased the figure size to avoid cutting off labels
    
    plt.subplot(1, 2, 1)
    plt.scatter(original_coords[:, 0], original_coords[:, 1], color='blue')
    plt.title(f'Original {title_suffix}')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.grid(True)
    
    plt.subplot(1, 2, 2)
    plt.scatter(reduced_coords[:, 0], reduced_coords[:, 1], color='red')
    plt.title(f'Reduced {title_suffix}')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.grid(True)
    
    plt.tight_layout(rect=[0, 0, 1, 0.95])  # Adjust layout to prevent cutting off
    plt.savefig(save_path, bbox_inches='tight')  # bbox_inches='tight' ensures no part of the plot is cut off
    plt.close()

# Function to plot and save 3D coordinates
def plot_3d(original_coords, reduced_coords, title_suffix, save_path):
    fig = plt.figure(figsize=(14, 8))  # Increased the figure size to avoid cutting off labels
    
    ax1 = fig.add_subplot(121, projection='3d')
    ax1.scatter(original_coords[:, 0], original_coords[:, 1], original_coords[:, 2], color='blue')
    ax1.set_title(f'Original {title_suffix}')
    ax1.set_xlabel('X')
    ax1.set_ylabel('Y')
    ax1.set_zlabel('Z')
    ax1.grid(True)
    ax1.view_init(elev=30, azim=45)
    
    ax2 = fig.add_subplot(122, projection='3d')
    ax2.scatter(reduced_coords[:, 0], reduced_coords[:, 1], reduced_coords[:, 2], color='red')
    ax2.set_title(f'Reduced {title_suffix}')
    ax2.set_xlabel('X')
    ax2.set_ylabel('Y')
    ax2.set_zlabel('Z')
    ax2.grid(True)
    ax2.view_init(elev=30, azim=45)
    
    plt.tight_layout(rect=[0, 0, 1, 0.95])  # Adjust layout to prevent cutting off
    plt.savefig(save_path, bbox_inches='tight')  # bbox_inches='tight' ensures no part of the plot is cut off
    plt.close()

# Main function to process all matching files in the given folders
def main(original_folder, reduced_folder):
    # Create the images subdirectory within the reduced_folder
    images_dir = os.path.join(reduced_folder, 'images')
    os.makedirs(images_dir, exist_ok=True)

    for filename in os.listdir(original_folder):
        if filename.endswith('.pof') and filename.startswith('ZCAT'):
            base_name = filename.split('.')[0]
            reduced_filename = f"reduced_{base_name}.pof"
            
            original_file = os.path.join(original_folder, filename)
            reduced_file = os.path.join(reduced_folder, reduced_filename)
            
            if not os.path.exists(reduced_file):
                print(f"Reduced file not found for {original_file}. Skipping...")
                continue
            
            original_coords = read_coordinates(original_file)
            reduced_coords = read_coordinates(reduced_file)
            
            dimension = determine_dimension(original_coords)
            title_suffix = base_name
            
            save_path = os.path.join(images_dir, f"{base_name}.png")
            
            if dimension == 2:
                plot_2d(original_coords, reduced_coords, title_suffix, save_path)
            elif dimension == 3:
                plot_3d(original_coords, reduced_coords, title_suffix, save_path)
            else:
                print(f"Unsupported dimension ({dimension}) in file: {original_file}. Skipping...")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <original_folder> <reduced_folder>")
        sys.exit(1)
    
    original_folder = sys.argv[1]
    reduced_folder = sys.argv[2]
    
    if not os.path.isdir(original_folder):
        print(f"Error: {original_folder} is not a valid directory.")
        sys.exit(1)
    
    if not os.path.isdir(reduced_folder):
        print(f"Error: {reduced_folder} is not a valid directory.")
        sys.exit(1)
    
    main(original_folder, reduced_folder)
