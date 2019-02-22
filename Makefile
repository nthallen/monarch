# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Wiles/sw/le-dasng

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Wiles/sw/le-dasng

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake.exe -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake.exe -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake.exe -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local

.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake.exe -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: install/strip

.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake.exe -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake.exe -P cmake_install.cmake
.PHONY : install/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/Wiles/sw/le-dasng/CMakeFiles /home/Wiles/sw/le-dasng/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/Wiles/sw/le-dasng/CMakeFiles 0
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
# Target rules for targets named gmock_main

# Build rule for target.
gmock_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gmock_main
.PHONY : gmock_main

# fast build rule for target.
gmock_main/fast:
	$(MAKE) -f googletest-build/googlemock/CMakeFiles/gmock_main.dir/build.make googletest-build/googlemock/CMakeFiles/gmock_main.dir/build
.PHONY : gmock_main/fast

#=============================================================================
# Target rules for targets named gmock

# Build rule for target.
gmock: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gmock
.PHONY : gmock

# fast build rule for target.
gmock/fast:
	$(MAKE) -f googletest-build/googlemock/CMakeFiles/gmock.dir/build.make googletest-build/googlemock/CMakeFiles/gmock.dir/build
.PHONY : gmock/fast

#=============================================================================
# Target rules for targets named gtest

# Build rule for target.
gtest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest
.PHONY : gtest

# fast build rule for target.
gtest/fast:
	$(MAKE) -f googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build.make googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build
.PHONY : gtest/fast

#=============================================================================
# Target rules for targets named gtest_main

# Build rule for target.
gtest_main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 gtest_main
.PHONY : gtest_main

# fast build rule for target.
gtest_main/fast:
	$(MAKE) -f googletest-build/googlemock/gtest/CMakeFiles/gtest_main.dir/build.make googletest-build/googlemock/gtest/CMakeFiles/gtest_main.dir/build
.PHONY : gtest_main/fast

#=============================================================================
# Target rules for targets named dasio

# Build rule for target.
dasio: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 dasio
.PHONY : dasio

# fast build rule for target.
dasio/fast:
	$(MAKE) -f dasio/src/CMakeFiles/dasio.dir/build.make dasio/src/CMakeFiles/dasio.dir/build
.PHONY : dasio/fast

#=============================================================================
# Target rules for targets named tmclt

# Build rule for target.
tmclt: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tmclt
.PHONY : tmclt

# fast build rule for target.
tmclt/fast:
	$(MAKE) -f dasio/test/CMakeFiles/tmclt.dir/build.make dasio/test/CMakeFiles/tmclt.dir/build
.PHONY : tmclt/fast

#=============================================================================
# Target rules for targets named test_socket

# Build rule for target.
test_socket: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_socket
.PHONY : test_socket

# fast build rule for target.
test_socket/fast:
	$(MAKE) -f dasio/test/CMakeFiles/test_socket.dir/build.make dasio/test/CMakeFiles/test_socket.dir/build
.PHONY : test_socket/fast

#=============================================================================
# Target rules for targets named test_timeout

# Build rule for target.
test_timeout: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_timeout
.PHONY : test_timeout

# fast build rule for target.
test_timeout/fast:
	$(MAKE) -f dasio/test/CMakeFiles/test_timeout.dir/build.make dasio/test/CMakeFiles/test_timeout.dir/build
.PHONY : test_timeout/fast

#=============================================================================
# Target rules for targets named test_not

# Build rule for target.
test_not: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_not
.PHONY : test_not

# fast build rule for target.
test_not/fast:
	$(MAKE) -f dasio/test/CMakeFiles/test_not.dir/build.make dasio/test/CMakeFiles/test_not.dir/build
.PHONY : test_not/fast

#=============================================================================
# Target rules for targets named echosrvr

# Build rule for target.
echosrvr: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 echosrvr
.PHONY : echosrvr

# fast build rule for target.
echosrvr/fast:
	$(MAKE) -f dasio/test/CMakeFiles/echosrvr.dir/build.make dasio/test/CMakeFiles/echosrvr.dir/build
.PHONY : echosrvr/fast

#=============================================================================
# Target rules for targets named test_unix_name

# Build rule for target.
test_unix_name: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_unix_name
.PHONY : test_unix_name

# fast build rule for target.
test_unix_name/fast:
	$(MAKE) -f dasio/test/CMakeFiles/test_unix_name.dir/build.make dasio/test/CMakeFiles/test_unix_name.dir/build
.PHONY : test_unix_name/fast

#=============================================================================
# Target rules for targets named tmsrvr

# Build rule for target.
tmsrvr: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tmsrvr
.PHONY : tmsrvr

# fast build rule for target.
tmsrvr/fast:
	$(MAKE) -f dasio/test/CMakeFiles/tmsrvr.dir/build.make dasio/test/CMakeFiles/tmsrvr.dir/build
.PHONY : tmsrvr/fast

#=============================================================================
# Target rules for targets named nl

# Build rule for target.
nl: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nl
.PHONY : nl

# fast build rule for target.
nl/fast:
	$(MAKE) -f nl/src/CMakeFiles/nl.dir/build.make nl/src/CMakeFiles/nl.dir/build
.PHONY : nl/fast

#=============================================================================
# Target rules for targets named tm

# Build rule for target.
tm: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tm
.PHONY : tm

# fast build rule for target.
tm/fast:
	$(MAKE) -f tm/src/CMakeFiles/tm.dir/build.make tm/src/CMakeFiles/tm.dir/build
.PHONY : tm/fast

#=============================================================================
# Target rules for targets named cmdgen

# Build rule for target.
cmdgen: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cmdgen
.PHONY : cmdgen

# fast build rule for target.
cmdgen/fast:
	$(MAKE) -f cmdgen/CMakeFiles/cmdgen.dir/build.make cmdgen/CMakeFiles/cmdgen.dir/build
.PHONY : cmdgen/fast

#=============================================================================
# Target rules for targets named oui

# Build rule for target.
oui: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 oui
.PHONY : oui

# fast build rule for target.
oui/fast:
	$(MAKE) -f oui/src/CMakeFiles/oui.dir/build.make oui/src/CMakeFiles/oui.dir/build
.PHONY : oui/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... list_install_components"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... install"
	@echo "... gmock_main"
	@echo "... gmock"
	@echo "... gtest"
	@echo "... gtest_main"
	@echo "... dasio"
	@echo "... tmclt"
	@echo "... test_socket"
	@echo "... test_timeout"
	@echo "... test_not"
	@echo "... echosrvr"
	@echo "... test_unix_name"
	@echo "... tmsrvr"
	@echo "... nl"
	@echo "... tm"
	@echo "... cmdgen"
	@echo "... oui"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

