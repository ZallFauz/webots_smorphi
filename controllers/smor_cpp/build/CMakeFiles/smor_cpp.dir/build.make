# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zall/webots_project/youbot/controllers/smor_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zall/webots_project/youbot/controllers/smor_cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/smor_cpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/smor_cpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/smor_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/smor_cpp.dir/flags.make

CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o: CMakeFiles/smor_cpp.dir/flags.make
CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o: ../smor_cpp.cpp
CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o: CMakeFiles/smor_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zall/webots_project/youbot/controllers/smor_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o -MF CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o.d -o CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o -c /home/zall/webots_project/youbot/controllers/smor_cpp/smor_cpp.cpp

CMakeFiles/smor_cpp.dir/smor_cpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smor_cpp.dir/smor_cpp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zall/webots_project/youbot/controllers/smor_cpp/smor_cpp.cpp > CMakeFiles/smor_cpp.dir/smor_cpp.cpp.i

CMakeFiles/smor_cpp.dir/smor_cpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smor_cpp.dir/smor_cpp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zall/webots_project/youbot/controllers/smor_cpp/smor_cpp.cpp -o CMakeFiles/smor_cpp.dir/smor_cpp.cpp.s

CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o: CMakeFiles/smor_cpp.dir/flags.make
CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o: ../src/SlaveMsgHandler.cpp
CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o: CMakeFiles/smor_cpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zall/webots_project/youbot/controllers/smor_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o -MF CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o.d -o CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o -c /home/zall/webots_project/youbot/controllers/smor_cpp/src/SlaveMsgHandler.cpp

CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zall/webots_project/youbot/controllers/smor_cpp/src/SlaveMsgHandler.cpp > CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.i

CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zall/webots_project/youbot/controllers/smor_cpp/src/SlaveMsgHandler.cpp -o CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.s

# Object files for target smor_cpp
smor_cpp_OBJECTS = \
"CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o" \
"CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o"

# External object files for target smor_cpp
smor_cpp_EXTERNAL_OBJECTS =

smor_cpp: CMakeFiles/smor_cpp.dir/smor_cpp.cpp.o
smor_cpp: CMakeFiles/smor_cpp.dir/src/SlaveMsgHandler.cpp.o
smor_cpp: CMakeFiles/smor_cpp.dir/build.make
smor_cpp: CMakeFiles/smor_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zall/webots_project/youbot/controllers/smor_cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable smor_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smor_cpp.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/zall/webots_project/youbot/controllers/smor_cpp/build/smor_cpp /home/zall/webots_project/youbot/controllers/smor_cpp

# Rule to build all files generated by this target.
CMakeFiles/smor_cpp.dir/build: smor_cpp
.PHONY : CMakeFiles/smor_cpp.dir/build

CMakeFiles/smor_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/smor_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/smor_cpp.dir/clean

CMakeFiles/smor_cpp.dir/depend:
	cd /home/zall/webots_project/youbot/controllers/smor_cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zall/webots_project/youbot/controllers/smor_cpp /home/zall/webots_project/youbot/controllers/smor_cpp /home/zall/webots_project/youbot/controllers/smor_cpp/build /home/zall/webots_project/youbot/controllers/smor_cpp/build /home/zall/webots_project/youbot/controllers/smor_cpp/build/CMakeFiles/smor_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/smor_cpp.dir/depend

