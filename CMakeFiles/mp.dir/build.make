# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /snap/clion/175/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/175/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft"

# Include any dependencies generated for this target.
include CMakeFiles/mp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mp.dir/flags.make

CMakeFiles/mp.dir/main.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/main.cpp.o: main.cpp
CMakeFiles/mp.dir/main.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mp.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/main.cpp.o -MF CMakeFiles/mp.dir/main.cpp.o.d -o CMakeFiles/mp.dir/main.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/main.cpp"

CMakeFiles/mp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/main.cpp" > CMakeFiles/mp.dir/main.cpp.i

CMakeFiles/mp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/main.cpp" -o CMakeFiles/mp.dir/main.cpp.s

CMakeFiles/mp.dir/Engine.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/Engine.cpp.o: Engine.cpp
CMakeFiles/mp.dir/Engine.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mp.dir/Engine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/Engine.cpp.o -MF CMakeFiles/mp.dir/Engine.cpp.o.d -o CMakeFiles/mp.dir/Engine.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Engine.cpp"

CMakeFiles/mp.dir/Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/Engine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Engine.cpp" > CMakeFiles/mp.dir/Engine.cpp.i

CMakeFiles/mp.dir/Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/Engine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Engine.cpp" -o CMakeFiles/mp.dir/Engine.cpp.s

CMakeFiles/mp.dir/ArcCam.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/ArcCam.cpp.o: ArcCam.cpp
CMakeFiles/mp.dir/ArcCam.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mp.dir/ArcCam.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/ArcCam.cpp.o -MF CMakeFiles/mp.dir/ArcCam.cpp.o.d -o CMakeFiles/mp.dir/ArcCam.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/ArcCam.cpp"

CMakeFiles/mp.dir/ArcCam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/ArcCam.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/ArcCam.cpp" > CMakeFiles/mp.dir/ArcCam.cpp.i

CMakeFiles/mp.dir/ArcCam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/ArcCam.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/ArcCam.cpp" -o CMakeFiles/mp.dir/ArcCam.cpp.s

CMakeFiles/mp.dir/FPCam.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/FPCam.cpp.o: FPCam.cpp
CMakeFiles/mp.dir/FPCam.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mp.dir/FPCam.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/FPCam.cpp.o -MF CMakeFiles/mp.dir/FPCam.cpp.o.d -o CMakeFiles/mp.dir/FPCam.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/FPCam.cpp"

CMakeFiles/mp.dir/FPCam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/FPCam.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/FPCam.cpp" > CMakeFiles/mp.dir/FPCam.cpp.i

CMakeFiles/mp.dir/FPCam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/FPCam.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/FPCam.cpp" -o CMakeFiles/mp.dir/FPCam.cpp.s

CMakeFiles/mp.dir/Steve.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/Steve.cpp.o: Steve.cpp
CMakeFiles/mp.dir/Steve.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mp.dir/Steve.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/Steve.cpp.o -MF CMakeFiles/mp.dir/Steve.cpp.o.d -o CMakeFiles/mp.dir/Steve.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Steve.cpp"

CMakeFiles/mp.dir/Steve.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/Steve.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Steve.cpp" > CMakeFiles/mp.dir/Steve.cpp.i

CMakeFiles/mp.dir/Steve.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/Steve.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Steve.cpp" -o CMakeFiles/mp.dir/Steve.cpp.s

CMakeFiles/mp.dir/Block.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/Block.cpp.o: Block.cpp
CMakeFiles/mp.dir/Block.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mp.dir/Block.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/Block.cpp.o -MF CMakeFiles/mp.dir/Block.cpp.o.d -o CMakeFiles/mp.dir/Block.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Block.cpp"

CMakeFiles/mp.dir/Block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/Block.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Block.cpp" > CMakeFiles/mp.dir/Block.cpp.i

CMakeFiles/mp.dir/Block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/Block.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Block.cpp" -o CMakeFiles/mp.dir/Block.cpp.s

CMakeFiles/mp.dir/Chunk.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/Chunk.cpp.o: Chunk.cpp
CMakeFiles/mp.dir/Chunk.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mp.dir/Chunk.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/Chunk.cpp.o -MF CMakeFiles/mp.dir/Chunk.cpp.o.d -o CMakeFiles/mp.dir/Chunk.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Chunk.cpp"

CMakeFiles/mp.dir/Chunk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/Chunk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Chunk.cpp" > CMakeFiles/mp.dir/Chunk.cpp.i

CMakeFiles/mp.dir/Chunk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/Chunk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/Chunk.cpp" -o CMakeFiles/mp.dir/Chunk.cpp.s

CMakeFiles/mp.dir/TextureManager.cpp.o: CMakeFiles/mp.dir/flags.make
CMakeFiles/mp.dir/TextureManager.cpp.o: TextureManager.cpp
CMakeFiles/mp.dir/TextureManager.cpp.o: CMakeFiles/mp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mp.dir/TextureManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mp.dir/TextureManager.cpp.o -MF CMakeFiles/mp.dir/TextureManager.cpp.o.d -o CMakeFiles/mp.dir/TextureManager.cpp.o -c "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/TextureManager.cpp"

CMakeFiles/mp.dir/TextureManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mp.dir/TextureManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/TextureManager.cpp" > CMakeFiles/mp.dir/TextureManager.cpp.i

CMakeFiles/mp.dir/TextureManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mp.dir/TextureManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/TextureManager.cpp" -o CMakeFiles/mp.dir/TextureManager.cpp.s

# Object files for target mp
mp_OBJECTS = \
"CMakeFiles/mp.dir/main.cpp.o" \
"CMakeFiles/mp.dir/Engine.cpp.o" \
"CMakeFiles/mp.dir/ArcCam.cpp.o" \
"CMakeFiles/mp.dir/FPCam.cpp.o" \
"CMakeFiles/mp.dir/Steve.cpp.o" \
"CMakeFiles/mp.dir/Block.cpp.o" \
"CMakeFiles/mp.dir/Chunk.cpp.o" \
"CMakeFiles/mp.dir/TextureManager.cpp.o"

# External object files for target mp
mp_EXTERNAL_OBJECTS =

mp: CMakeFiles/mp.dir/main.cpp.o
mp: CMakeFiles/mp.dir/Engine.cpp.o
mp: CMakeFiles/mp.dir/ArcCam.cpp.o
mp: CMakeFiles/mp.dir/FPCam.cpp.o
mp: CMakeFiles/mp.dir/Steve.cpp.o
mp: CMakeFiles/mp.dir/Block.cpp.o
mp: CMakeFiles/mp.dir/Chunk.cpp.o
mp: CMakeFiles/mp.dir/TextureManager.cpp.o
mp: CMakeFiles/mp.dir/build.make
mp: CMakeFiles/mp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable mp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mp.dir/build: mp
.PHONY : CMakeFiles/mp.dir/build

CMakeFiles/mp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mp.dir/clean

CMakeFiles/mp.dir/depend:
	cd "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft" "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft" "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft" "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft" "/home/keith/Coding/Computer Graphics/mcfinal2/fp-minecraft/CMakeFiles/mp.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/mp.dir/depend

