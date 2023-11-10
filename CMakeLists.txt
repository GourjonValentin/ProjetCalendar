cmake_minimum_required(VERSION 3.26)
project(ProjetCalendar C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetCalendar
        main.c
        list.c
        list.h
        cell.c
        cell.h
        testing.c
        testing.h
        timer.c
        timer.h
        plot/pbPlots.c
        plot/pbPlots.h
        plot/supportLib.c
        plot/supportLib.h
)
