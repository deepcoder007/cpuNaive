# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:
.PHONY : .NOTPARALLEL

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
CMAKE_SOURCE_DIR = /home/vibhanshu/BTP/cpuNaive

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vibhanshu/BTP/cpuNaive

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vibhanshu/BTP/cpuNaive/CMakeFiles /home/vibhanshu/BTP/cpuNaive/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/vibhanshu/BTP/cpuNaive/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named CPUNAIVE

# Build rule for target.
CPUNAIVE: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 CPUNAIVE
.PHONY : CPUNAIVE

# fast build rule for target.
CPUNAIVE/fast:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/build
.PHONY : CPUNAIVE/fast

#=============================================================================
# Target rules for targets named regression

# Build rule for target.
regression: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 regression
.PHONY : regression

# fast build rule for target.
regression/fast:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/build
.PHONY : regression/fast

#=============================================================================
# Target rules for targets named regression_multithread

# Build rule for target.
regression_multithread: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 regression_multithread
.PHONY : regression_multithread

# fast build rule for target.
regression_multithread/fast:
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/build
.PHONY : regression_multithread/fast

src/Graph.o: src/Graph.cpp.o
.PHONY : src/Graph.o

# target to build an object file
src/Graph.cpp.o:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/Graph.cpp.o
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/Graph.cpp.o
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/Graph.cpp.o
.PHONY : src/Graph.cpp.o

src/Graph.i: src/Graph.cpp.i
.PHONY : src/Graph.i

# target to preprocess a source file
src/Graph.cpp.i:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/Graph.cpp.i
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/Graph.cpp.i
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/Graph.cpp.i
.PHONY : src/Graph.cpp.i

src/Graph.s: src/Graph.cpp.s
.PHONY : src/Graph.s

# target to generate assembly for a file
src/Graph.cpp.s:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/Graph.cpp.s
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/Graph.cpp.s
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/Graph.cpp.s
.PHONY : src/Graph.cpp.s

src/debug.o: src/debug.cpp.o
.PHONY : src/debug.o

# target to build an object file
src/debug.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/debug.cpp.o
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/debug.cpp.o
.PHONY : src/debug.cpp.o

src/debug.i: src/debug.cpp.i
.PHONY : src/debug.i

# target to preprocess a source file
src/debug.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/debug.cpp.i
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/debug.cpp.i
.PHONY : src/debug.cpp.i

src/debug.s: src/debug.cpp.s
.PHONY : src/debug.s

# target to generate assembly for a file
src/debug.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/debug.cpp.s
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/debug.cpp.s
.PHONY : src/debug.cpp.s

src/keyValueStore.o: src/keyValueStore.cpp.o
.PHONY : src/keyValueStore.o

# target to build an object file
src/keyValueStore.cpp.o:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/keyValueStore.cpp.o
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/keyValueStore.cpp.o
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/keyValueStore.cpp.o
.PHONY : src/keyValueStore.cpp.o

src/keyValueStore.i: src/keyValueStore.cpp.i
.PHONY : src/keyValueStore.i

# target to preprocess a source file
src/keyValueStore.cpp.i:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/keyValueStore.cpp.i
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/keyValueStore.cpp.i
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/keyValueStore.cpp.i
.PHONY : src/keyValueStore.cpp.i

src/keyValueStore.s: src/keyValueStore.cpp.s
.PHONY : src/keyValueStore.s

# target to generate assembly for a file
src/keyValueStore.cpp.s:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/keyValueStore.cpp.s
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/keyValueStore.cpp.s
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/keyValueStore.cpp.s
.PHONY : src/keyValueStore.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/CPUNAIVE.dir/build.make CMakeFiles/CPUNAIVE.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/regression.o: src/regression.cpp.o
.PHONY : src/regression.o

# target to build an object file
src/regression.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/regression.cpp.o
.PHONY : src/regression.cpp.o

src/regression.i: src/regression.cpp.i
.PHONY : src/regression.i

# target to preprocess a source file
src/regression.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/regression.cpp.i
.PHONY : src/regression.cpp.i

src/regression.s: src/regression.cpp.s
.PHONY : src/regression.s

# target to generate assembly for a file
src/regression.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/regression.cpp.s
.PHONY : src/regression.cpp.s

src/regression_multithread.o: src/regression_multithread.cpp.o
.PHONY : src/regression_multithread.o

# target to build an object file
src/regression_multithread.cpp.o:
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/regression_multithread.cpp.o
.PHONY : src/regression_multithread.cpp.o

src/regression_multithread.i: src/regression_multithread.cpp.i
.PHONY : src/regression_multithread.i

# target to preprocess a source file
src/regression_multithread.cpp.i:
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/regression_multithread.cpp.i
.PHONY : src/regression_multithread.cpp.i

src/regression_multithread.s: src/regression_multithread.cpp.s
.PHONY : src/regression_multithread.s

# target to generate assembly for a file
src/regression_multithread.cpp.s:
	$(MAKE) -f CMakeFiles/regression_multithread.dir/build.make CMakeFiles/regression_multithread.dir/src/regression_multithread.cpp.s
.PHONY : src/regression_multithread.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... CPUNAIVE"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... regression"
	@echo "... regression_multithread"
	@echo "... src/Graph.o"
	@echo "... src/Graph.i"
	@echo "... src/Graph.s"
	@echo "... src/debug.o"
	@echo "... src/debug.i"
	@echo "... src/debug.s"
	@echo "... src/keyValueStore.o"
	@echo "... src/keyValueStore.i"
	@echo "... src/keyValueStore.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/regression.o"
	@echo "... src/regression.i"
	@echo "... src/regression.s"
	@echo "... src/regression_multithread.o"
	@echo "... src/regression_multithread.i"
	@echo "... src/regression_multithread.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

