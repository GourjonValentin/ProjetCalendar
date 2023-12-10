//
// Created by valen on 09/11/2023.
//

#ifndef PROJETCALENDAR_CELL1_H
#define PROJETCALENDAR_CELL1_H

typedef struct s_d_cell1 {
    int value;
    struct s_d_cell1 **next;
    int max_levels;
} t_d_cell1;

t_d_cell1 * create_cell1(int value, int max_levels);

#endif //PROJETCALENDAR_CELL1_H
