cmake_minimum_required(VERSION 3.15)

# 1. Define the project name and metadata
project(job-scheduler 
    VERSION 1.0.0 
    LANGUAGES CXX
)

# 2. Set the C++ standard globally
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. Create an executable target and specify source files
add_executable(my-redis 
    src/main.cpp
)

# C++ 20 jthread
add_compile_options(-fexperimental-library)

# 4. Include directories (where your .h header files live)
target_include_directories(my-redis PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)