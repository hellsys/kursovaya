# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\sasha\CLionProjects\kursovaya_2sem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\sasha\CLionProjects\kursovaya_2sem\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/kursovaya_2sem.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/kursovaya_2sem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kursovaya_2sem.dir/flags.make

CMakeFiles/kursovaya_2sem.dir/main.c.obj: CMakeFiles/kursovaya_2sem.dir/flags.make
CMakeFiles/kursovaya_2sem.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sasha\CLionProjects\kursovaya_2sem\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/kursovaya_2sem.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\kursovaya_2sem.dir\main.c.obj -c C:\Users\sasha\CLionProjects\kursovaya_2sem\main.c

CMakeFiles/kursovaya_2sem.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kursovaya_2sem.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\sasha\CLionProjects\kursovaya_2sem\main.c > CMakeFiles\kursovaya_2sem.dir\main.c.i

CMakeFiles/kursovaya_2sem.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kursovaya_2sem.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\sasha\CLionProjects\kursovaya_2sem\main.c -o CMakeFiles\kursovaya_2sem.dir\main.c.s

# Object files for target kursovaya_2sem
kursovaya_2sem_OBJECTS = \
"CMakeFiles/kursovaya_2sem.dir/main.c.obj"

# External object files for target kursovaya_2sem
kursovaya_2sem_EXTERNAL_OBJECTS =

kursovaya_2sem.exe: CMakeFiles/kursovaya_2sem.dir/main.c.obj
kursovaya_2sem.exe: CMakeFiles/kursovaya_2sem.dir/build.make
kursovaya_2sem.exe: CMakeFiles/kursovaya_2sem.dir/linklibs.rsp
kursovaya_2sem.exe: CMakeFiles/kursovaya_2sem.dir/objects1.rsp
kursovaya_2sem.exe: CMakeFiles/kursovaya_2sem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\sasha\CLionProjects\kursovaya_2sem\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable kursovaya_2sem.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\kursovaya_2sem.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kursovaya_2sem.dir/build: kursovaya_2sem.exe
.PHONY : CMakeFiles/kursovaya_2sem.dir/build

CMakeFiles/kursovaya_2sem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\kursovaya_2sem.dir\cmake_clean.cmake
.PHONY : CMakeFiles/kursovaya_2sem.dir/clean

CMakeFiles/kursovaya_2sem.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\sasha\CLionProjects\kursovaya_2sem C:\Users\sasha\CLionProjects\kursovaya_2sem C:\Users\sasha\CLionProjects\kursovaya_2sem\cmake-build-debug C:\Users\sasha\CLionProjects\kursovaya_2sem\cmake-build-debug C:\Users\sasha\CLionProjects\kursovaya_2sem\cmake-build-debug\CMakeFiles\kursovaya_2sem.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kursovaya_2sem.dir/depend

