//
// Created by Tristan on 16/11/2023.
//

#include "list.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// PARTIE 1

t_d_list * create_list() {
    int max_levels = 4; // levels = {0, 1, 2, 3}
    t_d_list *list = malloc(sizeof(t_d_list));
    list->heads = malloc(sizeof(t_d_cell *) * max_levels);
    list->max_levels = max_levels;
    for (int i = 0; i < max_levels; i++) {
        list->heads[i] = NULL;
    }
    return list;
}


/*
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

*/

void deleting_node_at_level(t_d_list* list, t_agenda_entry* ag_entry, int level) {
    t_d_cell* temp = list->heads[level];
    t_d_cell* prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->ag_entry->contact->last_name, ag_entry->contact->last_name) == 0 && strcmp(temp->ag_entry->contact->first_name, ag_entry->contact->first_name ) == 0) {
            if (prev == NULL) {
                list->heads[level] = temp->next[level];
            } else {
                prev->next[level] = temp->next[level];
            }
            return;
        }
        prev = temp;
        temp = temp->next[level];
    }
}

void deleting_node(t_d_list* list, t_agenda_entry* ag_entry) {
    for (int i = 0; i < list->max_levels; i++) {
        deleting_node_at_level(list, ag_entry, i);
    }
}

void insert_sorted_at_level(t_d_list *list, t_d_cell* cell, int level){ // fixme : ici level commence à 0
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
    if (strcmp(temp->ag_entry->contact->last_name, cell->ag_entry->contact->last_name) > 0) {
        list->heads[level] = cell;
        cell->next[level] = temp;
        return;
    }
    while (temp->next[level] != NULL && strcmp(temp->next[level]->ag_entry->contact->last_name, cell->ag_entry->contact->last_name) < 0) {
        temp = temp->next[level];
    }
    cell->next[level] = temp->next[level];
    temp->next[level] = cell;
}


void insert_sorted(t_d_list *list, t_agenda_entry *ag_entry) {

    // fixme : cellule insérée au mauvais niveau
    // Calcul du level de la cellule
    int level = list -> max_levels - 1; // On part du niveau max puis on décroit si il existe déja
    t_d_cell *temp, *del = NULL; // Cellule temporaire pour parcourir la liste pour la comparaison
    int cmp, cmp2, final_level = 0;

    while (level > 0 && final_level == 0) { // Comparaison à chaque level
        temp = list->heads[level]; // On part de la tête du level
        if (temp == NULL) {
            final_level = level;
            continue;
        }

        cmp = -1; // On initialise la comparaison à -1 pour entrer dans la boucle
        while (temp != NULL && cmp < 0) { // Comparaison avec chaque cellule du level
            cmp = strncmp(temp->ag_entry->contact->last_name, ag_entry->contact->last_name, list->max_levels - level); // Comparaison des x premiers caractères uniquement (1,2, 3, 4)

            if (cmp == 0) { // Résultat de la comparaison des x premiers caractères
                cmp2 = strcmp(temp->ag_entry->contact->last_name, ag_entry->contact->last_name); // comparaison de tout le nom pour vérifer s'il faut décaler la cellule temp

                if (cmp2 == 0) { // resultat de la comparaison des noms
                    cmp2 = strcmp(temp->ag_entry->contact->first_name, ag_entry->contact->first_name); // comparaison de tout le prénom pour vérifer s'il faut décaler la cellule temp

                    if (cmp2 == 0) { // Comparaison des prénoms si noms identiques
                        printf("Error : contact already exists with this name\n");
                        return;
                    }

                } if (cmp2 >= 1) { // Si le nom de la cellule temp est supérieur à celui de la cellule à insérer ( et que les x premières lettre correspondent)
                    del = temp; // marquage de la cellule temp pour la supprimer et la réinsérer
                    final_level = level;
                    break; // On sort de la boucle car on a trouvé la position de la cellule à insérer
                }

            } else if (cmp >= 1) { // Si le nom de la cellule temp est inférieur à celui de la cellule à insérer (uniquement sur les x premières lettres)
                final_level = level;
                break; // On sort de la boucle car on a trouvé la position de la cellule à insérer
            }
            temp = temp->next[level-1]; // Passage à la cellule suivante
        }

        if (temp == NULL && cmp != 0) { // Si on est arrivé à la fin de la liste
            final_level = level;
        }

        level --; // Passage au level inférieur si rien trouvé
    }

    // Création de la cellule
    t_d_cell* cell = create_cell(ag_entry, final_level + 1);
    for (int i = 0; i < final_level + 1; i++) { // level commence à 0 ici
        insert_sorted_at_level(list, cell, i);
    }

    if (del != NULL) {
        deleting_node(list, del->ag_entry);
        insert_sorted(list, del->ag_entry);
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
        printf("-->[ %s_%s|@-]", cell->ag_entry->contact->last_name, cell->ag_entry->contact->first_name);
        cell = cell->next[level];
    }
    printf("-->NULL\n");
}

void print_list(t_d_list *list) {
    for (int i = 0; i < list->max_levels; i++) {
        print_level(list, i);
    }
}

/*

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
     * *\/
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
*/