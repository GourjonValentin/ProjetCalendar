//
// Created by Tristan on 16/11/2023.
//

#ifndef PROJETCALENDAR_LIST_H
#define PROJETCALENDAR_LIST_H

#include "cell.h"

// PARTIE 1

typedef struct s_d_list {
    t_d_cell **heads;
    int max_levels;
} t_d_list;

t_d_list * create_list(int max_levels);

void insert_head_at_level(t_d_list *list, t_d_cell* cell, int level); // fixme : type of cell

void insert_head(t_d_list *list, t_d_cell* cell); // fixme : type of cell

void print_level(t_d_list *list, int level); // todo : adapt to new type

void print_list(t_d_list *list); // todo : adapt to new type

void print_aligned_level(t_d_list *list, int level); // todo : adapt to new type

void print_aligned_list(t_d_list *list); // todo : adapt to new type

void insert_sorted(t_d_list *list, t_d_cell* cell); // todo : adapt to new type

void insert_sorted_at_level(t_d_list *list, t_d_cell* cell, int level); // todo : adapt to new type

// PARTIE 2

t_d_list * create_filled_list(int n_levels); // todo : adapt to new type

int classic_search(t_d_list *list, int value); // todo : adapt to new type

int optimized_search(t_d_list *list, int value); // todo : adapt to new type

#endif //PROJETCALENDAR_LIST_H
