//
// Created by Tristan on 16/11/2023.
//

#include "cell.h"

#include <stdlib.h>

t_d_cell * create_cell(t_contact* contact, int max_levels){
    t_d_cell *cell = malloc(sizeof(t_d_cell));
    cell->contact = contact;
    cell->next = malloc(sizeof (t_d_cell) * max_levels);
    cell->max_levels = max_levels;
    return cell;
}
