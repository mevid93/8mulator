# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.0.0)
project(8mulator VERSION 0.1.0 LANGUAGES C CXX)

# GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add subdirectories
add_subdirectory(dependencies/glfw)

# Add sources to SOURCES variable
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "dependencies/glad/src/glad.c"
)

# add files to executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command
target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

include_directories(dependencies/glad/include)
include_directories(dependencies/irrKlang/include)

# link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/dependencies/irrKlang/lib/libIrrKlang.so)

# copy resources folder to build folder
file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_SOURCE_DIR}/build)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
