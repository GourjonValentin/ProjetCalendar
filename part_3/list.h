//
// Created by Tristan on 16/11/2023.
//

#ifndef PROJETCALENDAR_LIST_H
#define PROJETCALENDAR_LIST_H

#include "cell.h"
#include "struct.h"

// PARTIE 1

typedef struct s_d_list {
    t_d_cell **heads;
    int max_levels;
} t_d_list;

t_d_list * create_list();



void print_level(t_d_list *list, int level);

void print_list(t_d_list *list);

void print_aligned_level(t_d_list *list, int level); // todo : adapt to new type

void print_aligned_list(t_d_list *list); // todo : adapt to new type

void insert_sorted(t_d_list *list, t_agenda_entry *ag_entry);

void insert_sorted_at_level(t_d_list *list, t_d_cell* cell, int level); // todo : adapt to new type

t_agenda_entry* search(t_d_list *list);
#endif //PROJETCALENDAR_LIST1_H
