# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/hexagonaled/Graphics/freeglut-3.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hexagonaled/Graphics/freeglut-3.0.0

# Include any dependencies generated for this target.
include CMakeFiles/Lorenz.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lorenz.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lorenz.dir/flags.make

CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o: CMakeFiles/Lorenz.dir/flags.make
CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o: progs/demos/Lorenz/lorenz.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hexagonaled/Graphics/freeglut-3.0.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o   -c /home/hexagonaled/Graphics/freeglut-3.0.0/progs/demos/Lorenz/lorenz.c

CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hexagonaled/Graphics/freeglut-3.0.0/progs/demos/Lorenz/lorenz.c > CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.i

CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hexagonaled/Graphics/freeglut-3.0.0/progs/demos/Lorenz/lorenz.c -o CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.s

CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.requires:

.PHONY : CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.requires

CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.provides: CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.requires
	$(MAKE) -f CMakeFiles/Lorenz.dir/build.make CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.provides.build
.PHONY : CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.provides

CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.provides.build: CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o


# Object files for target Lorenz
Lorenz_OBJECTS = \
"CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o"

# External object files for target Lorenz
Lorenz_EXTERNAL_OBJECTS =

bin/Lorenz: CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o
bin/Lorenz: CMakeFiles/Lorenz.dir/build.make
bin/Lorenz: /usr/lib/i386-linux-gnu/libGLU.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libGL.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libSM.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libICE.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libX11.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libXext.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libXxf86vm.so
bin/Lorenz: lib/libglut.so.3.10.0
bin/Lorenz: /usr/lib/i386-linux-gnu/libGL.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libSM.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libICE.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libX11.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libXext.so
bin/Lorenz: /usr/lib/i386-linux-gnu/libXxf86vm.so
bin/Lorenz: CMakeFiles/Lorenz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hexagonaled/Graphics/freeglut-3.0.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/Lorenz"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lorenz.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lorenz.dir/build: bin/Lorenz

.PHONY : CMakeFiles/Lorenz.dir/build

CMakeFiles/Lorenz.dir/requires: CMakeFiles/Lorenz.dir/progs/demos/Lorenz/lorenz.c.o.requires

.PHONY : CMakeFiles/Lorenz.dir/requires

CMakeFiles/Lorenz.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lorenz.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lorenz.dir/clean

CMakeFiles/Lorenz.dir/depend:
	cd /home/hexagonaled/Graphics/freeglut-3.0.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hexagonaled/Graphics/freeglut-3.0.0 /home/hexagonaled/Graphics/freeglut-3.0.0 /home/hexagonaled/Graphics/freeglut-3.0.0 /home/hexagonaled/Graphics/freeglut-3.0.0 /home/hexagonaled/Graphics/freeglut-3.0.0/CMakeFiles/Lorenz.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Lorenz.dir/depend

