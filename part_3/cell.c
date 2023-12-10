//
// Created by Tristan on 16/11/2023.
//

#include "cell.h"

#include <stdlib.h>

t_d_cell1 * create_cell(t_agenda_entry * ag_entry, int max_levels){
    t_d_cell1 *cell = malloc(sizeof(t_d_cell1));
    cell->ag_entry = ag_entry;
    cell->next = malloc(sizeof (t_d_cell1) * max_levels);
    cell->max_levels = max_levels;
    return cell;
}
