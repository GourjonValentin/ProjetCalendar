//
// Created by Tristan on 16/11/2023.
//

#ifndef PROJETCALENDAR_LIST_H
#define PROJETCALENDAR_LIST_H

#include "cell.h"
#include "struct.h"

// PARTIE 1

typedef struct s_d_list {
    t_d_cell1 **heads;
    int max_levels;
} t_d_list1;

t_d_list1 * create_list();



void print_level(t_d_list1 *list, int level);

void print_list(t_d_list1 *list);

void print_aligned_level(t_d_list1 *list, int level); // todo : adapt to new type

void print_aligned_list(t_d_list1 *list); // todo : adapt to new type

void insert_sorted(t_d_list1 *list, t_agenda_entry *ag_entry);

void insert_sorted_at_level(t_d_list1 *list, t_d_cell1* cell, int level); // todo : adapt to new type

t_agenda_entry *search_if_contact_exist(t_d_list1 list, char *first_name, char *last_name);

t_agenda_entry* search(t_d_list1 *list);
#endif //PROJETCALENDAR_LIST1_H
