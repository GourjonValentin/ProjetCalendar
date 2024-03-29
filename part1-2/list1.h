//
// Created by valen on 09/11/2023.
//

#ifndef PROJETCALENDAR_LIST1_H
#define PROJETCALENDAR_LIST1_H

#include "cell1.h"

// PARTIE 1

typedef struct s_d_list {
    t_d_cell1 **heads;
    int max_levels;
} t_d_list1;

t_d_list1 * create_list1(int max_levels);

void insert_head_at_level1(t_d_list1 *list, t_d_cell1* cell, int level);

void insert_head1(t_d_list1 *list, t_d_cell1* cell);

void print_level1(t_d_list1 *list, int level);

void print_list1(t_d_list1 *list);

void print_aligned_level1(t_d_list1 *list, int level);

void print_aligned_list1(t_d_list1 *list);

void insert_sorted1(t_d_list1 *list, t_d_cell1* cell);

void insert_sorted_at_level1(t_d_list1 *list, t_d_cell1* cell, int level);

// PARTIE 2

t_d_list1 * create_filled_list1(int n_levels);

int classic_search1(t_d_list1 *list, int value);

int optimized_search1(t_d_list1 *list, int value);

#endif //PROJETCALENDAR_LIST1_H
