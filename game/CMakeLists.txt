project(game)

# Get all source files
file(GLOB_RECURSE GAME_SOURCES LIST_DIRECTORIES=ON *.[hc]pp)

# Create executable from game sources
add_executable(${PROJECT_NAME} ${GAME_SOURCES})

# Link the engine library to this executable
if(UNIX)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE engine ${X11_LIBRARIES})
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE engine)
endif()