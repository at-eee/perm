cmake_minimum_required(VERSION 3.10.2)

project(perm)

add_executable(generator.out src/generator.c)
add_executable(input_checker.out src/input_checker.c)
add_executable(perm_processing.out src/perm_processing.c)
add_executable(rdg.out src/random_data_gen.c)