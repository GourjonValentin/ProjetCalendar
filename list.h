//
// Created by valen on 09/11/2023.
//

#ifndef PROJETCALENDAR_LIST_H
#define PROJETCALENDAR_LIST_H

#include "cell.h"

// s_d_list est une liste à niveaux multiples

typedef struct s_d_list {
    t_d_cell **heads;
    int max_levels;
} t_d_list;

t_d_list * create_list(int max_levels);

void insert_head_at_level(t_d_list *list, t_d_cell* cell, int level);

void insert_head(t_d_list *list, t_d_cell* cell);

void print_level(t_d_list *list, int level);

void print_list(t_d_list *list);

void print_aligned_level(t_d_list *list, int level);

void print_aligned_list(t_d_list *list);

void insert_sorted(t_d_list *list, t_d_cell* cell);

void insert_sorted_at_level(t_d_list *list, t_d_cell* cell, int level);

#endif //PROJETCALENDAR_LIST_H
