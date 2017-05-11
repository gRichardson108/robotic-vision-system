import ikpy
import numpy as np
import serial
from ikpy import plot_utils, geometry_utils,link

#The position of the end effector when the robot is pointed straight up into the air.
# This is the default position.
extended_length = 22.4 + 27.9 + 27.9 + 19.1
erection_vector = np.array([0, 0, -extended_length])
"""Link in URDF representation.
    :param name: The name of the link
    :type name: string
    :param bounds: Optional : The bounds of the link. Defaults to None
    :type bounds: tuple
    :param translation_vector: The translation vector. (In URDF, attribute "xyz" of the "origin" element)
    :type translation_vector: numpy.array
    :param orientation: The orientation of the link. (In URDF, attribute "rpy" of the "origin" element)
    :type orientation: numpy.array
    :param rotation: The rotation axis of the link. (In URDF, attribute "xyz" of the "axis" element)
    :type rotation: numpy.array
    :param angle_representation: Optionnal : The representation used by the angle. Currently supported representations : rpy. Defaults to rpy, the URDF standard.
    :type angle_representation: string
    :param use_symbolic_matrix: wether the transformation matrix is stored as a Numpy array or as a Sympy symbolic matrix.
    :type use_symbolic_matrix: bool
    :returns: The link object
    :rtype: URDFLink
    """
#That's from the docs. I'm assuming that bounds is a tuple of upper and lower bounds
#along the rotation axis. Units? I think maybe radians???

base = link.URDFLink(name="base",
    translation_vector=np.array([0,0,-22.4]),
    orientation=np.array([0,0,0]),
    rotation=np.array([0,0,1]),
    bounds=(None, None))

shoulder = link.URDFLink(name="shoulder",
    translation_vector=np.array([0,0,-27.9]),
    orientation=np.array([0,0,0]),
    rotation=np.array([0,1,0]),
    bounds=(None, None))

elbow = link.URDFLink(name="elbow",
    translation_vector=np.array([0,0,-27.9]),
    orientation=np.array([0,0,0]),
    rotation=np.array([0,1,0]),
    bounds=(None, None))

wrist = link.URDFLink(name="wrist",
    translation_vector=np.array([0,0,-19.1]),
    orientation=np.array([0,0,0]),
    rotation=np.array([0,1,0]),
    bounds=(None, None))


# Read the geometry of the robot
# rovi_chain = ikpy.chain.Chain.from_urdf_file("urdf.xml", base_elements=["foot_link"], base_element_type="link", active_links_mask=None, name="rovi")

#manually define the geometry of the robot
rovi_chain = ikpy.chain.Chain([base,shoulder,elbow,wrist])

# rovi_chain.plot()
# Define the identity matrix for 3 dimensions
i3 = [[1, 0, 0],[0, 1, 0],[0, 0, 1]]


#Set target position vector as xyz coordinates
#this should move approx 1 motor
target_vector = [0, extended_length-22.4-, -22.4]
# Convert it into a 4 by 4 matrix
# target_vector=[50,50,-23]
frame_matrix = geometry_utils.to_transformation_matrix(target_vector,i3)
#compute the angles of the joints
print rovi_chain.inverse_kinematics(frame_matrix)
