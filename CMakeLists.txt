cmake_minimum_required(VERSION 3.26)
project(ProjetCalendar C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetCalendar
        main.c
        part1-2/list.c
        part1-2/list.h
        part1-2/cell.c
        part1-2/cell.h
        part1-2/testing.c
        part1-2/testing.h
        part1-2/timer.c
        part1-2/timer.h
        plot/pbPlots.c
        plot/pbPlots.h
        plot/supportLib.c
        plot/supportLib.h
        part_3/struct.c
        part_3/struct.h
)
