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
add_executable(ex01a-1 src/ex01a/1.cpp)
add_executable(ex01a-2 src/ex01a/2.cpp)
add_executable(ex01a-3 src/ex01a/3.cpp)

# Exercise 2A
add_executable(ex02a src/ex02a/1.cpp)

# Exercise 4A
add_executable(ex04a src/ex04a/3d_object_demo.cpp)

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

# Exercise 6B
add_executable(ex06b-1 src/ex06b/demo1.cpp)  # task 6.1
add_executable(ex06b-2 src/ex06b/demo2.cpp)  # task 6.2
add_executable(ex06b-3 src/ex06b/demo3.cpp)  # task 6.3

# Exercise 7B
add_executable(ex07b-1 src/ex07b/demo1.cpp)  # task 7.1
add_executable(ex07b-2 src/ex07b/demo2.cpp)  # task 7.2

# Exercise 8B
add_executable(ex08b src/ex08b/bezier_demo.cpp)

# Excercise 10B
add_executable(ex10b src/ex10b/raytracing_demo.cpp)

# Excercise 11B
add_executable(ex11b-mandelbrot src/ex11b/mandelbrot/mandelbrot_demo.cpp)
add_executable(ex11b-ifs src/ex11b/ifs-fractals/ifs_demo.cpp)

# Well, this is is the CLI way:
#1# g++ -Wall -o test bresenham.cpp -lglut -lGL -lGLU
#   g++ -Wall -o test opengl-tutorial-01.cpp -lglut -lGL -lGLU
#   g++ -Wall -o test main.cpp -lglut -lGL -lGLU -lglfw
#2# g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw 3vjezba/convex_polygon_demo.cpp -o 3.out
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw 4vjezba/demo.cpp -o 4.out
#3# g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw src/ex06b/demo1.cpp -o ex06b-1.out
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw src/ex06b/demo2.cpp -o ex06b-2.out
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw src/ex06b/demo3.cpp -o ex06b-3.out
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw src/ex07b/demo1.cpp -o ex07b-1.out
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw src/ex07b/demo2.cpp -o ex07b-2.out
#   g++ -std=c++17 -Wall -Wextra -Werror -lglut -lGL -lGLU -lglfw src/ex08b/bezier_demo.cpp -o ex08b.out