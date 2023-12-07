//
// Created by valen on 09/11/2023.
//

#include "cell1.h"

#include <stdlib.h>

t_d_cell * create_cell(int value, int max_levels){
    t_d_cell *cell = malloc(sizeof(t_d_cell));
    cell->value = value;
    cell->next = malloc(sizeof (t_d_cell) * max_levels);
    cell->max_levels = max_levels;
    return cell;
}
