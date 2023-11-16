//
// Created by valen on 09/11/2023.
//

#ifndef PROJETCALENDAR_CELL_H
#define PROJETCALENDAR_CELL_H

typedef struct s_d_cell {
    int value;
    struct s_d_cell **next;
    int max_levels;
} t_d_cell;

t_d_cell * create_cell(int value, int max_levels);

#endif //PROJETCALENDAR_CELL_H
