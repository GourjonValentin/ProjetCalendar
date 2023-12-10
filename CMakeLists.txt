cmake_minimum_required(VERSION 3.24)
project(ProjetCalendar C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetCalendar
        main.c
        #plot/pbPlots.c
        #plot/pbPlots.h
        #plot/supportLib.c
        #plot/supportLib.h
        part_3/struct.c
        part_3/struct.h
        part_3/cell.c part_3/list.c
        part_3/insertion_test.c
        part_3/insertion_test.h
        part_3/menu.c
        part_3/menu.h)
