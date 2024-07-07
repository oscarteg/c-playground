cmake_minimum_required(VERSION 3.10)

# Specify the project name and language
project(MultiCompile C)

# Set the compiler to Clang
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 99)  # Set to C99 standard (adjust as needed)

# Set the source directory
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# Gather all .c files in the src directory
file(GLOB SRC_FILES "${SRC_DIR}/*.c")

# Add a single executable that includes all source files
# add_executable(all_in_one ${SRC_FILES})

# Specify the compile flags (adjust as needed)
set(COMPILE_FLAGS -Wall -Wextra -pedantic -Wunused-parameter)

# Apply the compile flags to the all_in_one target
# target_compile_options(all_in_one PRIVATE ${COMPILE_FLAGS})

# Loop over each source file and compile it individually
foreach(SRC_FILE ${SRC_FILES})
  # Get the file name without the directory or extension
  get_filename_component(FILE_NAME ${SRC_FILE} NAME_WE)

  # Add an executable for each source file
  add_executable(${FILE_NAME} ${SRC_FILE})

  # Apply the compile flags to each individual target
  target_compile_options(${FILE_NAME} PRIVATE ${COMPILE_FLAGS})
endforeach()
