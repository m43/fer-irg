cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(first)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lglut -lGL -lGLU -lglfw") # -Werror might be too much at this moment

### Testing and setting the environment ###
# add_executable(ex00-0 src/ex00/main.cpp)
# add_executable(ex00-1 src/ex00/opengl-tutorial-01.cpp)
# add_executable(ex00-2 src/ex00/bresenham.cpp)
# add_executable(ex00-3 src/ex00/ref_vs_pointer.cpp)
# add_executable(ex00-4 src/ex00/ref_vs_pointer_2.cpp)

# Exercise 1A
add_executable(ex01a-1 src/ex01a/1.cpp)
add_executable(ex01a-2 src/ex01a/2.cpp)
add_executable(ex01a-3 src/ex01a/3.cpp)

# Exercise 2A
add_executable(ex02a src/ex02a/1.cpp)

# Excercise 1B
add_executable(ex01b-1 src/linalg/demo_01.cpp)

# Well, this is is the CLI way:
#   g++ -Wall -o test bresenham.cpp -lglut -lGL -lGLU
#   g++ -Wall -o test opengl-tutorial-01.cpp -lglut -lGL -lGLU
#   g++ -Wall -o test main.cpp -lglut -lGL -lGLU -lglfw
