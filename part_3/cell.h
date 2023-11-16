//
// Created by Tristan on 16/11/2023.
//

#ifndef PROJETCALENDAR_CELL_H
#define PROJETCALENDAR_CELL_H
#include "struct.h"

typedef struct s_d_cell {
    t_contact* contact;
    struct s_d_cell **next;
    int max_levels;
} t_d_cell;

t_d_cell * create_cell(t_contact* contact, int max_levels);

#endif //PROJETCALENDAR_CELL_H
