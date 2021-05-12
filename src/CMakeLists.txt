find_package(SFML COMPONENTS graphics system window REQUIRED)

add_executable(
    ${PROJECT_NAME} 
    "main.cpp" 
    "quadtree.h" 
    "quadtree.cpp"
    "particle.h"
    "particle.cpp"
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-system sfml-window)
