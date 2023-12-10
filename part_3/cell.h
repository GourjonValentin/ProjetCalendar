//
// Created by Tristan on 16/11/2023.
//

#ifndef PROJETCALENDAR_CELL_H
#define PROJETCALENDAR_CELL_H
#include "struct.h"

typedef struct s_d_cell {
    t_agenda_entry * ag_entry;
    struct s_d_cell **next;
    int max_levels;
} t_d_cell;

t_d_cell * create_cell(t_agenda_entry* ag_entry, int max_levels);

#endif //PROJETCALENDAR_CELL1_H
