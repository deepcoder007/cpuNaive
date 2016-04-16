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
# Target rules for targets named regression2

# Build rule for target.
regression2: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 regression2
.PHONY : regression2

# fast build rule for target.
regression2/fast:
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/build
.PHONY : regression2/fast

src/AlgoAnt.o: src/AlgoAnt.cpp.o
.PHONY : src/AlgoAnt.o

# target to build an object file
src/AlgoAnt.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAnt.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAnt.cpp.o
.PHONY : src/AlgoAnt.cpp.o

src/AlgoAnt.i: src/AlgoAnt.cpp.i
.PHONY : src/AlgoAnt.i

# target to preprocess a source file
src/AlgoAnt.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAnt.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAnt.cpp.i
.PHONY : src/AlgoAnt.cpp.i

src/AlgoAnt.s: src/AlgoAnt.cpp.s
.PHONY : src/AlgoAnt.s

# target to generate assembly for a file
src/AlgoAnt.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAnt.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAnt.cpp.s
.PHONY : src/AlgoAnt.cpp.s

src/AlgoAnt2.o: src/AlgoAnt2.cpp.o
.PHONY : src/AlgoAnt2.o

# target to build an object file
src/AlgoAnt2.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAnt2.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAnt2.cpp.o
.PHONY : src/AlgoAnt2.cpp.o

src/AlgoAnt2.i: src/AlgoAnt2.cpp.i
.PHONY : src/AlgoAnt2.i

# target to preprocess a source file
src/AlgoAnt2.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAnt2.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAnt2.cpp.i
.PHONY : src/AlgoAnt2.cpp.i

src/AlgoAnt2.s: src/AlgoAnt2.cpp.s
.PHONY : src/AlgoAnt2.s

# target to generate assembly for a file
src/AlgoAnt2.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAnt2.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAnt2.cpp.s
.PHONY : src/AlgoAnt2.cpp.s

src/AlgoAntSystem.o: src/AlgoAntSystem.cpp.o
.PHONY : src/AlgoAntSystem.o

# target to build an object file
src/AlgoAntSystem.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAntSystem.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAntSystem.cpp.o
.PHONY : src/AlgoAntSystem.cpp.o

src/AlgoAntSystem.i: src/AlgoAntSystem.cpp.i
.PHONY : src/AlgoAntSystem.i

# target to preprocess a source file
src/AlgoAntSystem.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAntSystem.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAntSystem.cpp.i
.PHONY : src/AlgoAntSystem.cpp.i

src/AlgoAntSystem.s: src/AlgoAntSystem.cpp.s
.PHONY : src/AlgoAntSystem.s

# target to generate assembly for a file
src/AlgoAntSystem.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAntSystem.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAntSystem.cpp.s
.PHONY : src/AlgoAntSystem.cpp.s

src/AlgoAntSystem2.o: src/AlgoAntSystem2.cpp.o
.PHONY : src/AlgoAntSystem2.o

# target to build an object file
src/AlgoAntSystem2.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAntSystem2.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAntSystem2.cpp.o
.PHONY : src/AlgoAntSystem2.cpp.o

src/AlgoAntSystem2.i: src/AlgoAntSystem2.cpp.i
.PHONY : src/AlgoAntSystem2.i

# target to preprocess a source file
src/AlgoAntSystem2.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAntSystem2.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAntSystem2.cpp.i
.PHONY : src/AlgoAntSystem2.cpp.i

src/AlgoAntSystem2.s: src/AlgoAntSystem2.cpp.s
.PHONY : src/AlgoAntSystem2.s

# target to generate assembly for a file
src/AlgoAntSystem2.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoAntSystem2.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoAntSystem2.cpp.s
.PHONY : src/AlgoAntSystem2.cpp.s

src/AlgoRandomAnt.o: src/AlgoRandomAnt.cpp.o
.PHONY : src/AlgoRandomAnt.o

# target to build an object file
src/AlgoRandomAnt.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoRandomAnt.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoRandomAnt.cpp.o
.PHONY : src/AlgoRandomAnt.cpp.o

src/AlgoRandomAnt.i: src/AlgoRandomAnt.cpp.i
.PHONY : src/AlgoRandomAnt.i

# target to preprocess a source file
src/AlgoRandomAnt.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoRandomAnt.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoRandomAnt.cpp.i
.PHONY : src/AlgoRandomAnt.cpp.i

src/AlgoRandomAnt.s: src/AlgoRandomAnt.cpp.s
.PHONY : src/AlgoRandomAnt.s

# target to generate assembly for a file
src/AlgoRandomAnt.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/AlgoRandomAnt.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/AlgoRandomAnt.cpp.s
.PHONY : src/AlgoRandomAnt.cpp.s

src/Graph.o: src/Graph.cpp.o
.PHONY : src/Graph.o

# target to build an object file
src/Graph.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/Graph.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/Graph.cpp.o
.PHONY : src/Graph.cpp.o

src/Graph.i: src/Graph.cpp.i
.PHONY : src/Graph.i

# target to preprocess a source file
src/Graph.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/Graph.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/Graph.cpp.i
.PHONY : src/Graph.cpp.i

src/Graph.s: src/Graph.cpp.s
.PHONY : src/Graph.s

# target to generate assembly for a file
src/Graph.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/Graph.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/Graph.cpp.s
.PHONY : src/Graph.cpp.s

src/debug.o: src/debug.cpp.o
.PHONY : src/debug.o

# target to build an object file
src/debug.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/debug.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/debug.cpp.o
.PHONY : src/debug.cpp.o

src/debug.i: src/debug.cpp.i
.PHONY : src/debug.i

# target to preprocess a source file
src/debug.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/debug.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/debug.cpp.i
.PHONY : src/debug.cpp.i

src/debug.s: src/debug.cpp.s
.PHONY : src/debug.s

# target to generate assembly for a file
src/debug.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/debug.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/debug.cpp.s
.PHONY : src/debug.cpp.s

src/keyValueStore.o: src/keyValueStore.cpp.o
.PHONY : src/keyValueStore.o

# target to build an object file
src/keyValueStore.cpp.o:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/keyValueStore.cpp.o
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/keyValueStore.cpp.o
.PHONY : src/keyValueStore.cpp.o

src/keyValueStore.i: src/keyValueStore.cpp.i
.PHONY : src/keyValueStore.i

# target to preprocess a source file
src/keyValueStore.cpp.i:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/keyValueStore.cpp.i
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/keyValueStore.cpp.i
.PHONY : src/keyValueStore.cpp.i

src/keyValueStore.s: src/keyValueStore.cpp.s
.PHONY : src/keyValueStore.s

# target to generate assembly for a file
src/keyValueStore.cpp.s:
	$(MAKE) -f CMakeFiles/regression.dir/build.make CMakeFiles/regression.dir/src/keyValueStore.cpp.s
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/keyValueStore.cpp.s
.PHONY : src/keyValueStore.cpp.s

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

src/regression2.o: src/regression2.cpp.o
.PHONY : src/regression2.o

# target to build an object file
src/regression2.cpp.o:
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/regression2.cpp.o
.PHONY : src/regression2.cpp.o

src/regression2.i: src/regression2.cpp.i
.PHONY : src/regression2.i

# target to preprocess a source file
src/regression2.cpp.i:
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/regression2.cpp.i
.PHONY : src/regression2.cpp.i

src/regression2.s: src/regression2.cpp.s
.PHONY : src/regression2.s

# target to generate assembly for a file
src/regression2.cpp.s:
	$(MAKE) -f CMakeFiles/regression2.dir/build.make CMakeFiles/regression2.dir/src/regression2.cpp.s
.PHONY : src/regression2.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... regression"
	@echo "... regression2"
	@echo "... src/AlgoAnt.o"
	@echo "... src/AlgoAnt.i"
	@echo "... src/AlgoAnt.s"
	@echo "... src/AlgoAnt2.o"
	@echo "... src/AlgoAnt2.i"
	@echo "... src/AlgoAnt2.s"
	@echo "... src/AlgoAntSystem.o"
	@echo "... src/AlgoAntSystem.i"
	@echo "... src/AlgoAntSystem.s"
	@echo "... src/AlgoAntSystem2.o"
	@echo "... src/AlgoAntSystem2.i"
	@echo "... src/AlgoAntSystem2.s"
	@echo "... src/AlgoRandomAnt.o"
	@echo "... src/AlgoRandomAnt.i"
	@echo "... src/AlgoRandomAnt.s"
	@echo "... src/Graph.o"
	@echo "... src/Graph.i"
	@echo "... src/Graph.s"
	@echo "... src/debug.o"
	@echo "... src/debug.i"
	@echo "... src/debug.s"
	@echo "... src/keyValueStore.o"
	@echo "... src/keyValueStore.i"
	@echo "... src/keyValueStore.s"
	@echo "... src/regression.o"
	@echo "... src/regression.i"
	@echo "... src/regression.s"
	@echo "... src/regression2.o"
	@echo "... src/regression2.i"
	@echo "... src/regression2.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

