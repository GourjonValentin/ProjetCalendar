//
// Created by valen on 09/11/2023.
//

#include "structure.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_d_cell * create_cell(int value, int max_levels){
    t_d_cell *cell = malloc(sizeof(t_d_cell));
    cell->value = value;
    cell->next = malloc(sizeof (t_d_cell) * max_levels);
    cell->max_levels = max_levels;
    return cell;
}

t_d_list * create_list(int max_levels) {
    t_d_list *list = malloc(sizeof(t_d_list));
    list->heads = malloc(sizeof(t_d_cell *) * max_levels);
    list->max_levels = max_levels;
    for (int i = 0; i < max_levels; i++) {
        list->heads[i] = NULL;
    }
    return list;
}

void insert_head_at_level(t_d_list *list, t_d_cell* cell, int level) {
    if (level < 0 || level >= list->max_levels) {
        printf("Error: level %d does not exist\n", level);
        return;
    }
    if (list->heads[level] == NULL) {
        list->heads[level] = cell;
        cell->next[level] = NULL;
        return;
    }
    t_d_cell *temp = list->heads[level];
    list->heads[level] = cell;
    cell->next[level] = temp;
}

void insert_head(t_d_list *list, t_d_cell* cell) {
    for (int i = 0; i < cell->max_levels; i++) {
        insert_head_at_level(list, cell, i);
    }
}

void insert_sorted_at_level(t_d_list *list, t_d_cell* cell, int level){
    if (level < 0 || level >= list->max_levels) {
        printf("Error: level %d does not exist\n", level);
        return;
    }
    if (list->heads[level] == NULL) {
        list->heads[level] = cell;
        cell->next[level] = NULL;
        return;
    }
    t_d_cell *prev = list->heads[level];
    t_d_cell *temp = prev->next;
    while (temp->next != NULL){
        if (cell->value < temp->value){
            cell->next = &temp;
            prev->next = &cell;
        }else{
            prev = prev->next;
            temp = temp->next;
            }
        }
        if (temp->next == NULL){
            temp->next = &cell;
        }
    }

void insert_sorted(t_d_list *list, t_d_cell* cell) {
    for (int i = 0; i < cell->max_levels; i++) {
        insert_sorted_at_level(list, cell, i);
    }
}

void print_level(t_d_list *list, int level) {
    if (level < 0 || level >= list->max_levels) {
        printf("Error: level %d does not exist\n", level);
        return;
    }
    t_d_cell *cell = list->heads[level];
    printf("[list head_%d]", level);
    while (cell != NULL) {
        printf("-->[ %d|@-]", cell->value);
        cell = cell->next[level];
    }
    printf("-->NULL\n");
}

void print_list(t_d_list *list) {
    for (int i = 0; i < list->max_levels; i++) {
        print_level(list, i);
    }
}

int n_digit(int n) {
    return floor(log10(abs(n))) + 1;
}

int index_of(int val, t_d_list list) {
    int index = 0;
    t_d_cell *cell = list.heads[0];
    while (cell != NULL) {
        if (cell->value == val) {
            return index;
        }
        index++;
        cell = cell->next[0];
    }
    return -1;
}

void print_aligned_level(t_d_list *list, int level) {
    if (level < 0 || level >= list->max_levels) {
        printf("Error: level %d does not exist\n", level);
        return;
    }
    int max_n = pow(2, list->max_levels)-1;
    int n_max = n_digit(max_n); // longueur max du chiffre
    int n_cell = 0;
    int i_prev = 0;
    int i_curr = 0;
    int delta_i = 0;
    t_d_cell *prev = NULL;
    t_d_cell *cell = list->heads[level];
    printf("[list head_%d]", level);
    while (cell != NULL) {
        if (prev == NULL) {
            i_prev = 0;
        } else {
            i_prev = index_of(prev->value, *list);
        }
        i_curr = index_of(cell->value, *list);
        delta_i = i_curr - i_prev;
        for (int i = 0; i < delta_i * 9 + delta_i * n_max; i++) {
            printf("-");
        }
        n_cell = n_digit(cell->value);
        printf("-->[ ");
        for (int i = 0; i < n_max - n_cell; i++) {
            printf(" ");
        }
        printf("%d|@-]", cell->value);
        prev = cell;
        cell = cell->next[level];
        printf("%d", delta_i);

    }
    printf("-->NULL\n");
}


void print_aligned_list(t_d_list *list) {
    for (int i = 0; i < list->max_levels; i++) {
        print_aligned_level(list, i);
    }
}
