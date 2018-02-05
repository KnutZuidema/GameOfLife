cmake_minimum_required(VERSION 3.8)
project(GameOfLife)
set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDEDIR ${PROJECT_SOURCE_DIR}/lib/sfml/include CACHE PATH "SFML headers")
set(SFML_LIBRARYDIR ${PROJECT_SOURCE_DIR}/lib/sfml/lib CACHE PATH "SFML libraries")
set(BOOST_INCLUDEDIR ${PROJECT_SOURCE_DIR}/lib/boost/bin/include CACHE PATH "Boost headers")
set(BOOST_LIBRARYDIR ${PROJECT_SOURCE_DIR}/lib/boost/bin/lib CACHE PATH "Boost libraries")

include_directories(${SFML_INCLUDEDIR} ${BOOST_INCLUDEDIR})
link_directories(${SFML_LIBRARYDIR} ${BOOST_LIBRARYDIR})

add_executable(GameOfLife ./src/main.cpp ./src/Cell.cpp ./src/Grid.cpp)
target_link_libraries(GameOfLife sfml-graphics sfml-window sfml-system boost_program_options)
