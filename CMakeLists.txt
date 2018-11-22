cmake_minimum_required(VERSION 3.12)
project(lab_7 C)

set(CMAKE_C_STANDARD 11)

add_executable(czyt_pis czyt_pis.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -lm")

set (sources czytelnia.h czytelnia.c)

add_library(czytelnia ${sources} )


TARGET_LINK_LIBRARIES(czyt_pis czytelnia)