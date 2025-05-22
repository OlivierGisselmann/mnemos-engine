project(engine)

# Get all source files
file(GLOB_RECURSE ENGINE_SOURCES LIST_DIRECTORIES=ON *.[hc]pp)

# Create static library from sources
add_library(${PROJECT_NAME} STATIC ${ENGINE_SOURCES})

# Include headers from this directory and all its childrens
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if(UNIX)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
endif()