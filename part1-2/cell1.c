//
// Created by valen on 09/11/2023.
//

#include "cell1.h"

#include <stdlib.h>

t_d_cell1 * create_cell1(int value, int max_levels){
    t_d_cell1 *cell = malloc(sizeof(t_d_cell1));
    cell->value = value;
    cell->next = malloc(sizeof (t_d_cell1) * max_levels);
    cell->max_levels = max_levels;
    return cell;
}
