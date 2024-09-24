import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

# Function to read coordinates from a file
def read_coordinates(filename):
    coordinates = []
    with open(filename, 'r') as file:
        for line in file:
            x, y, z = map(float, line.split())
            coordinates.append((x, y, z))
    return np.array(coordinates)

# Load the coordinates from the files
before_coords = read_coordinates('before.txt')
after_coords = read_coordinates('after.txt')

# Create the plot for the "before" state
fig = plt.figure(figsize=(12, 6))

ax1 = fig.add_subplot(121, projection='3d')
ax1.scatter(before_coords[:, 0], before_coords[:, 1], before_coords[:, 2], color='blue')
ax1.set_title('Before')
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_zlabel('Z')
ax1.grid(True)
# Rotate the plot
ax1.view_init(elev=30, azim=45)  # Adjust elev and azim to change the viewing angle

# Create the plot for the "after" state
ax2 = fig.add_subplot(122, projection='3d')
ax2.scatter(after_coords[:, 0], after_coords[:, 1], after_coords[:, 2], color='red')
ax2.set_title('After')
ax2.set_xlabel('X')
ax2.set_ylabel('Y')
ax2.set_zlabel('Z')
ax2.grid(True)
# Rotate the plot
ax2.view_init(elev=30, azim=45)  # Adjust elev and azim to change the viewing angle

# Adjust layout and show the plots
plt.tight_layout()
plt.show()
