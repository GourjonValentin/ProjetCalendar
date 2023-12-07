//
// Created by valen on 09/11/2023.
//

#include "list1.h"
#include "cell1.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// PARTIE 1

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
    return index;
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
            i_prev = -1;
        } else {
            i_prev = index_of(prev->value, *list);
        }
        i_curr = index_of(cell->value, *list);
        delta_i = i_curr - i_prev - 1;
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
    }
    delta_i = index_of(999999999999, *list) - i_curr - 1;
    for (int i = 0; i < delta_i * 9 + delta_i * n_max; i++) {
        printf("-");
    }
    printf("-->NULL\n");
}


void print_aligned_list(t_d_list *list) {
    for (int i = 0; i < list->max_levels; i++) {
        print_aligned_level(list, i);
    }
}


// PARTIE 2

int level_of(int index, int n_levels) {
    // Fonction qui calcule le niveau d'une cellule à partir de son index
    int level = 0;
    while (index % 2 == 0 && level < n_levels) {
        index /= 2;
        level++;
    }
    return level;
}

t_d_list * create_filled_list(int n_levels){
    /* Création d'une liste a partir du principe suivant :
     * Soit n_levels le nombre de niveaux de la liste
     * La liste stocke toutes les valeurs de 0 à 2^n_levels - 1
     * Chaque niveau pointera une cellule sur deux du niveau précédent
     * Le niveau 0 pointera sur toutes les cellules
     * */
    t_d_list *list = create_list(n_levels);
    int n_cells = pow(2, n_levels) - 1;
    int n_levels_cell = 0;

    // Création des cellules
    t_d_cell **cells = malloc(sizeof(t_d_cell *) * n_cells);
    for (int i = 1; i <= n_cells; i++) {

        // calcul du nombre de niveaux de la cellule
        n_levels_cell = level_of(i, n_levels) + 1;
        cells[i-1] = create_cell(i, n_levels_cell);
    }

    // Insertion des cellules dans la liste
    for (int i = 0; i < n_cells; i++) {
        insert_sorted(list, cells[i]);
    }

    // Libération de la mémoire
    free(cells);

    return list;
}

int classic_search(t_d_list *list, int value) {
    int index = 0;
    t_d_cell *cell = list->heads[0];
    while (cell != NULL) {
        if (cell->value == value) {
            return index;
        }
        index++;
        cell = cell->next[0];
    }
    return -1;
}

int optimized_search(t_d_list *list, int value) {
    int index = 0;
    int level = list->max_levels - 1;
    t_d_cell *prev = NULL;
    t_d_cell *cell = list->heads[level];
    while (level >= 0) {
        while (cell != NULL && cell->value < value) {
            index += pow(2, level);
            prev = cell;
            cell = cell->next[level];
        }
        if (cell != NULL && cell->value == value) {
            return index;
        }
        level--;
        if (prev != NULL) {
            cell = prev->next[level];
        } else {
            cell = list->heads[level];
        }
    }
    return -1;
}
