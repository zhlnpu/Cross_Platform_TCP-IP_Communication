# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/li/dev/co-design-core-add-hololens/clion-client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tcpClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcpClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcpClient.dir/flags.make

CMakeFiles/tcpClient.dir/main.cpp.o: CMakeFiles/tcpClient.dir/flags.make
CMakeFiles/tcpClient.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcpClient.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcpClient.dir/main.cpp.o -c /home/li/dev/co-design-core-add-hololens/clion-client/main.cpp

CMakeFiles/tcpClient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpClient.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/li/dev/co-design-core-add-hololens/clion-client/main.cpp > CMakeFiles/tcpClient.dir/main.cpp.i

CMakeFiles/tcpClient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpClient.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/li/dev/co-design-core-add-hololens/clion-client/main.cpp -o CMakeFiles/tcpClient.dir/main.cpp.s

CMakeFiles/tcpClient.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/tcpClient.dir/main.cpp.o.requires

CMakeFiles/tcpClient.dir/main.cpp.o.provides: CMakeFiles/tcpClient.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcpClient.dir/build.make CMakeFiles/tcpClient.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/tcpClient.dir/main.cpp.o.provides

CMakeFiles/tcpClient.dir/main.cpp.o.provides.build: CMakeFiles/tcpClient.dir/main.cpp.o


CMakeFiles/tcpClient.dir/ClientApp.cpp.o: CMakeFiles/tcpClient.dir/flags.make
CMakeFiles/tcpClient.dir/ClientApp.cpp.o: ../ClientApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tcpClient.dir/ClientApp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcpClient.dir/ClientApp.cpp.o -c /home/li/dev/co-design-core-add-hololens/clion-client/ClientApp.cpp

CMakeFiles/tcpClient.dir/ClientApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpClient.dir/ClientApp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/li/dev/co-design-core-add-hololens/clion-client/ClientApp.cpp > CMakeFiles/tcpClient.dir/ClientApp.cpp.i

CMakeFiles/tcpClient.dir/ClientApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpClient.dir/ClientApp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/li/dev/co-design-core-add-hololens/clion-client/ClientApp.cpp -o CMakeFiles/tcpClient.dir/ClientApp.cpp.s

CMakeFiles/tcpClient.dir/ClientApp.cpp.o.requires:

.PHONY : CMakeFiles/tcpClient.dir/ClientApp.cpp.o.requires

CMakeFiles/tcpClient.dir/ClientApp.cpp.o.provides: CMakeFiles/tcpClient.dir/ClientApp.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcpClient.dir/build.make CMakeFiles/tcpClient.dir/ClientApp.cpp.o.provides.build
.PHONY : CMakeFiles/tcpClient.dir/ClientApp.cpp.o.provides

CMakeFiles/tcpClient.dir/ClientApp.cpp.o.provides.build: CMakeFiles/tcpClient.dir/ClientApp.cpp.o


CMakeFiles/tcpClient.dir/ServerConnection.cpp.o: CMakeFiles/tcpClient.dir/flags.make
CMakeFiles/tcpClient.dir/ServerConnection.cpp.o: ../ServerConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tcpClient.dir/ServerConnection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcpClient.dir/ServerConnection.cpp.o -c /home/li/dev/co-design-core-add-hololens/clion-client/ServerConnection.cpp

CMakeFiles/tcpClient.dir/ServerConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpClient.dir/ServerConnection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/li/dev/co-design-core-add-hololens/clion-client/ServerConnection.cpp > CMakeFiles/tcpClient.dir/ServerConnection.cpp.i

CMakeFiles/tcpClient.dir/ServerConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpClient.dir/ServerConnection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/li/dev/co-design-core-add-hololens/clion-client/ServerConnection.cpp -o CMakeFiles/tcpClient.dir/ServerConnection.cpp.s

CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.requires:

.PHONY : CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.requires

CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.provides: CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.requires
	$(MAKE) -f CMakeFiles/tcpClient.dir/build.make CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.provides.build
.PHONY : CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.provides

CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.provides.build: CMakeFiles/tcpClient.dir/ServerConnection.cpp.o


# Object files for target tcpClient
tcpClient_OBJECTS = \
"CMakeFiles/tcpClient.dir/main.cpp.o" \
"CMakeFiles/tcpClient.dir/ClientApp.cpp.o" \
"CMakeFiles/tcpClient.dir/ServerConnection.cpp.o"

# External object files for target tcpClient
tcpClient_EXTERNAL_OBJECTS =

tcpClient: CMakeFiles/tcpClient.dir/main.cpp.o
tcpClient: CMakeFiles/tcpClient.dir/ClientApp.cpp.o
tcpClient: CMakeFiles/tcpClient.dir/ServerConnection.cpp.o
tcpClient: CMakeFiles/tcpClient.dir/build.make
tcpClient: CMakeFiles/tcpClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tcpClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcpClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcpClient.dir/build: tcpClient

.PHONY : CMakeFiles/tcpClient.dir/build

CMakeFiles/tcpClient.dir/requires: CMakeFiles/tcpClient.dir/main.cpp.o.requires
CMakeFiles/tcpClient.dir/requires: CMakeFiles/tcpClient.dir/ClientApp.cpp.o.requires
CMakeFiles/tcpClient.dir/requires: CMakeFiles/tcpClient.dir/ServerConnection.cpp.o.requires

.PHONY : CMakeFiles/tcpClient.dir/requires

CMakeFiles/tcpClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcpClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcpClient.dir/clean

CMakeFiles/tcpClient.dir/depend:
	cd /home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/li/dev/co-design-core-add-hololens/clion-client /home/li/dev/co-design-core-add-hololens/clion-client /home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug /home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug /home/li/dev/co-design-core-add-hololens/clion-client/cmake-build-debug/CMakeFiles/tcpClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcpClient.dir/depend

