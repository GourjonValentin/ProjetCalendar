//
// Created by Tristan on 16/11/2023.
//

#include "cell.h"

#include <stdlib.h>

t_d_cell * create_cell(t_agenda_entry * ag_entry, int max_levels){
    t_d_cell *cell = malloc(sizeof(t_d_cell));
    cell->ag_entry = ag_entry;
    cell->next = malloc(sizeof (t_d_cell) * max_levels);
    cell->max_levels = max_levels;
    return cell;
}
