# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction

# Include any dependencies generated for this target.
include CMakeFiles/BG_Subtract.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BG_Subtract.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BG_Subtract.dir/flags.make

CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o: CMakeFiles/BG_Subtract.dir/flags.make
CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o: bg_sub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o"
	/usr/lib64/ccache/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o -c /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction/bg_sub.cpp

CMakeFiles/BG_Subtract.dir/bg_sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BG_Subtract.dir/bg_sub.cpp.i"
	/usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction/bg_sub.cpp > CMakeFiles/BG_Subtract.dir/bg_sub.cpp.i

CMakeFiles/BG_Subtract.dir/bg_sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BG_Subtract.dir/bg_sub.cpp.s"
	/usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction/bg_sub.cpp -o CMakeFiles/BG_Subtract.dir/bg_sub.cpp.s

CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.requires:

.PHONY : CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.requires

CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.provides: CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.requires
	$(MAKE) -f CMakeFiles/BG_Subtract.dir/build.make CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.provides.build
.PHONY : CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.provides

CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.provides.build: CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o


# Object files for target BG_Subtract
BG_Subtract_OBJECTS = \
"CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o"

# External object files for target BG_Subtract
BG_Subtract_EXTERNAL_OBJECTS =

BG_Subtract: CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o
BG_Subtract: CMakeFiles/BG_Subtract.dir/build.make
BG_Subtract: /usr/local/lib/libopencv_shape.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_stitching.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_superres.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_videostab.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_objdetect.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_calib3d.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_features2d.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_flann.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_highgui.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_ml.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_photo.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_video.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_videoio.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_imgproc.so.3.2.0
BG_Subtract: /usr/local/lib/libopencv_core.so.3.2.0
BG_Subtract: CMakeFiles/BG_Subtract.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BG_Subtract"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BG_Subtract.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BG_Subtract.dir/build: BG_Subtract

.PHONY : CMakeFiles/BG_Subtract.dir/build

CMakeFiles/BG_Subtract.dir/requires: CMakeFiles/BG_Subtract.dir/bg_sub.cpp.o.requires

.PHONY : CMakeFiles/BG_Subtract.dir/requires

CMakeFiles/BG_Subtract.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BG_Subtract.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BG_Subtract.dir/clean

CMakeFiles/BG_Subtract.dir/depend:
	cd /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction /home/garret/Documents/school/2017_spring/COMP491/robotic-vision-system/vision/backgroundSubtraction/CMakeFiles/BG_Subtract.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BG_Subtract.dir/depend
