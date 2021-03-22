cmake_minimum_required(VERSION 3.13.4)
project(mandelbrot-walker C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

find_package(OpenCL REQUIRED)

add_executable(mandelbrot-walker
        openCL_driver/openCL_driver.c
        openCL_driver/openCL_driver.h
        main.c
        mandelbrot/mandelbrot.c
        mandelbrot/mandelbrot.h
        colors/colors.c
        colors/colors.h
        config.h
        explorer.c
        explorer.h
        config)

target_link_libraries(mandelbrot-walker OpenCL::OpenCL)
target_link_libraries(mandelbrot-walker SDL2)
