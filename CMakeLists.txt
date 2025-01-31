cmake_minimum_required(VERSION 3.30)
project(bcit_comp2510_c_project C)

set(CMAKE_C_STANDARD 11)

add_executable(bcit_comp2510_c_project main.c
        patient.c
        dsm.c
        ui.c)
