cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(fer-irg)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw")

### Testing and setting the environment ###
# add_executable(ex00-0 src/ex00/main.cpp)
# add_executable(ex00-1 src/ex00/opengl-tutorial-01.cpp)
# add_executable(ex00-2 src/ex00/bresenham.cpp)
# add_executable(ex00-3 src/ex00/ref_vs_pointer.cpp)
# add_executable(ex00-4 src/ex00/ref_vs_pointer_2.cpp)
# add_executable(ex00-5 src/ex00/ooup_virtual_tables.cpp)
# add_executable(ex00-6 src/ex00/70_gotcha.cpp)
# add_executable(ex00-7 src/ex00/vtables.cpp)
# add_executable(ex00-8 src/ex00/playground.cpp)
# add_executable(mc-01 src/ex00/book-mc-01.cpp)
# add_executable(ex00-9 src/ex00/linalg_playground.cpp)

##########################
### "A" version of lab ###
##########################

# Exercise 1A
#add_executable(ex01a-1 src/ex01a/1.cpp)
#add_executable(ex01a-2 src/ex01a/2.cpp)
#add_executable(ex01a-3 src/ex01a/3.cpp)

# Exercise 2A
#add_executable(ex02a src/ex02a/1.cpp)

# Exercise 4A
#add_executable(ex04a src/ex04a/3d_object_demo.cpp)

##########################
### "B" version of lab ###
##########################

# Exercise 1B
add_executable(linalg-demo-01 src/linalg/demo_01.cpp)
add_executable(linalg-demo-02 src/linalg/demo_02.cpp)
add_executable(ex01b-1 src/ex01b/1.cpp)
add_executable(ex01b-2 src/ex01b/2.cpp)
add_executable(ex01b-3 src/ex01b/3.cpp)

# Exercise 2B
add_executable(ex02b src/ex02b/triangle_demo.cpp)

# Exercise 3B
add_executable(ex03b src/ex03b/line_demo.cpp)

# Exercise 4B
add_executable(ex04b src/ex04b/convex_polygon_demo.cpp)

# Well, this is is the CLI way:
#   g++ -Wall -o test bresenham.cpp -lglut -lGL -lGLU
#   g++ -Wall -o test opengl-tutorial-01.cpp -lglut -lGL -lGLU
#   g++ -Wall -o test main.cpp -lglut -lGL -lGLU -lglfw
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw 3vjezba/convex_polygon_demo.cpp -o 3.out
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw 4vjezba/demo.cpp -o 4.out