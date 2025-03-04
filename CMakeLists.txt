cmake_minimum_required(VERSION 3.30)
project(bcit_comp2510_c_project C)

set(CMAKE_C_STANDARD 11)

add_executable(bcit_comp2510_c_project main.c
        patient.c
        dsm.c
        patient.h
        dsm.h
        list.h
        list.c
        test.c
        test.h
        file_m.h
        file_m.c
)
