import ikpy
import numpy as np
from ikpy import plot_utils

# Read the geometry of the robot
rovi_chain = ikpy.chain.Chain.from_urdf_file("urdf.xml")

# Define the identity matrix for 3 dimensions
i3 = [[1, 0, 0],[0, 1, 0],[0, 0, 1]]

#Set target position vector as xyz coordinates
target_vector = [ 0.1, -0.2, 0.1]
# Convert it into a 4 by 4 matrix
frame_matrix = geometry_utils.to_transformation_matrix(target_vector,i3)
#compute the angles of the joints
rovi_chain.inverse_kinematics(target_frame)
