cmake_minimum_required(VERSION 3.22...4.0)

project(mnemos)

# Set C++ as project's default language
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine and game layers subdirectories
add_subdirectory(engine)
add_subdirectory(game)