# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (8mulator)

# GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add subdirectories
add_subdirectory(lib/glfw)
include_directories(lib/glfw)
include_directories(lib/glfw/deps)
include_directories(lib/glfw/include)

# Add sources to SOURCES variable
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "lib/glad/src/glad.c"
)

# add files to executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command
target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

include_directories(lib/glad/include)
include_directories(lib/irrKlang/include)

# link libraries
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/irrKlang/bin/linux-gcc-64/libIrrKlang.so)
