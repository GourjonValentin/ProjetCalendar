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
    t_d_cell *temp = list->heads[level];
    if (temp->value > cell->value) {
        list->heads[level] = cell;
        cell->next[level] = temp;
        return;
    }
    while (temp->next[level] != NULL && temp->next[level]->value < cell->value) {
        temp = temp->next[level];
    }
    cell->next[level] = temp->next[level];
    temp->next[level] = cell;
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
