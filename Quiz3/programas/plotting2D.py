import matplotlib.pyplot as plt
import numpy as np

# Function to read coordinates from a file
def read_coordinates(filename):
    coordinates = []
    with open(filename, 'r') as file:
        for line in file:
            x, y = map(float, line.split())
            coordinates.append((x, y))
    return np.array(coordinates)

# Load the coordinates from the files
before_coords = read_coordinates('before.txt')
after_coords = read_coordinates('after.txt')

# Create the plot for the "before" state
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.scatter(before_coords[:, 0], before_coords[:, 1], color='blue')
plt.title('Before')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)

# Create the plot for the "after" state
plt.subplot(1, 2, 2)
plt.scatter(after_coords[:, 0], after_coords[:, 1], color='red')
plt.title('After')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)

# Adjust layout and show the plots
plt.tight_layout()
plt.show()
