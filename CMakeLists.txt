cmake_minimum_required(VERSION 3.20)

# +=============================================+
# +============+ Setup Basic Infos +============+
# +=============================================+
set(PROJECT_NAME HeatSimulation)
project(${PROJECT_NAME} LANGUAGES CXX CUDA)
set(EXECUTABLE_NAME ${PROJECT_NAME})
# Change default build/lib directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/obj")

# +=============================================+
# +====+ Setup Headers, Sources and macros +====+
# +=============================================+
option(GPU "Enable GPU acceleration" OFF)
set(GPU ON)

if (GPU)
    add_compile_definitions(GPU_ENABLED)
    file(GLOB HEADERS src/*.hpp src/*.cuh)
    file(GLOB SOURCES src/*.cpp src/*.cu)
    message(STATUS "GPU acceleration option detected")
else ()
    file(GLOB HEADERS src/*.hpp)
    file(GLOB SOURCES src/*.cpp)
    message(STATUS "GPU acceleration option not detected - Skipping")
endif ()

# +=============================================+
# +=========+ Setup libraries targets +=========+
# +=============================================+
set(LIBRARY_NAME Engine)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# +=============================================+
# +========+ Setup libraries headers +==========+
# +=============================================+
set(INCLUDE_HEADERS lib/csv.h)

add_library(${LIBRARY_NAME} STATIC ${INCLUDE_HEADERS} ${HEADERS} ${SOURCES})
target_link_libraries(${LIBRARY_NAME} ${SDL2_LIBRARIES})
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
set_target_properties(${LIBRARY_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON CUDA_ARCHITECTURES 50 75 80)

# +=============================================+
# +========+ Setup compilers options +==========+
# +=============================================+
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3")

# +=============================================+
# +=========+ Build the executable +============+
# +=============================================+
add_executable(${EXECUTABLE_NAME} src/main.cpp)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CUDA_SEPARABLE_COMPILATION ON)
add_dependencies(${EXECUTABLE_NAME} ${LIBRARY_NAME})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})