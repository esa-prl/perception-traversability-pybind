# perception-traversability-pybind
This repository provides Python bindings for the rock [perception-traversability](https://github.com/esa-prl/perception-traversability).
## Installation instructions
Please install the following packages to use this repo:
On macOS this can be done with:
```
brew install cmake opencv pcl eigen
```
Subsequently, we can install the Python module using pip:
```
pip install -e --user .
```
## Usage instructions
Below you can find a sample code snippet on how to use this Python module:
```
from traversability_pybind import Traversability
traversability = Traversability()

# Defaults from HDPR config:
# https://github.com/esa-prl/bundles-rover/blob/master/config/orogen/traversability::Task.yml
# Size of the kernel used in the laplacian to detect rocks edges
laplacian_kernel_size = 9
# Threshold of the laplacian to detect rocks edges. It is not zet tied to a physical property.
laplacian_threshold = 100
# First obstacle dilation iterations
obstacle_iterations = 2
# Kernel size to dilate obstacle first time [cells]
obstacle_kernel_size = 3)
# Second obstacle dilation iterations (area surrounding an obstacle)
obstacle_vicinity_iterations = 3
# Kernel size to dilate obstacle second time [cells]
obstacle_vicinity_kernel_size = int(self.config.get("obstacle_vicinity_kernel_size", 3))
# in meters, needed for obstacle dilation
robot_size = self.config.get("robot_size", 0.6)
# Obstacles the rover can tolerate when there is no sinkage [m]
rover_obstacle_clearance = self.config.get("rover_obstacle_clearance", 0.2)
# Slope the rover can travel in nominal case [rad]
rover_slope_gradeability = self.config.get("rover_slope_gradeability", 15/180*np.pi)
# How many normal cell a slope map cell will contain
slope_map_scale = int(self.config.get("slope_map_scale", 3))
# Final traversability map dilation iterations
dilation_iterations = int(self.config.get("dilation_iterations", 2))

# Resolution of each cell in meters
map_resolution = 0.1

traversability.configure_traversability(map_resolution, slope_map_scale,
                                        rover_slope_gradeability, rover_obstacle_clearance,
                                        laplacian_kernel_size, laplacian_threshold,
                                        obstacle_kernel_size, obstacle_iterations,
                                        obstacle_vicinity_kernel_size, obstacle_vicinity_iterations,
                                        robot_size, dilation_iterations)
               
# Dummy Digital Elevation Map (DEM)                        
dem = np.ones(shape=(100, 100))
traversability.set_elevation_map(rec_dem.reshape((-1), order='C').tolist(),
                                 rec_dem.shape[0], rec_dem.shape[1])
traversability_map = np.array(traversability.compute_traversability_eigen())
```