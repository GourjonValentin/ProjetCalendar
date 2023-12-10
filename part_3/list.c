//
// Created by Tristan on 16/11/2023.
//

#include "list.h"
#include "cell.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// PARTIE 3

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


void print_aligned_list1(t_d_list *list) {
    for (int i = 0; i < list->max_levels; i++) {
        print_aligned_level1(list, i);
    }
}
*/



// Recherche avec complétion automatique
t_agenda_entry* search(t_d_list *agenda) {
    if (agenda == NULL) {
        printf("Error : agenda is NULL\n");
        return NULL;
    }
    int i = 1;
    int lvl_max = agenda->max_levels;
    t_d_cell *head = agenda->heads[lvl_max - 1];
    t_d_cell *cell = head;
    do {
        if (i == 1) {
            "Quelle est la première lettre du nom de la personne recherchée ?\n";
        } else if (i == 2) {
            "Quelles sont les deux premières lettres du nom de la personne recherchée ?\n";
        } else if (i == 3) {
            "Quelles sont les trois premières lettres du nom de la personne recherchée ?\n";
        } else {
            "Quel est le nom de la personne recherchée ?\n";
        }

        int j = 0;
        while (cell != NULL  && (i == 0 ? 1 : strncmp(cell->ag_entry->contact->last_name, head->ag_entry->contact->last_name, i-1) == 0)) {
            j++;
            if (j == 0) {
                printf("Voici les possibilités :\n");
            }
            if (i == 1) {
                printf("%d : %.1s\n", j, cell->ag_entry->contact->last_name);
            } else if (i == 2) {
                printf("%d : %.2s\n", j, cell->ag_entry->contact->last_name);
            } else if (i == 3) {
                printf("%d : %.3s\n", j, cell->ag_entry->contact->last_name);
            } else {
                printf("%d : %s %s\n", j, cell->ag_entry->contact->last_name, cell->ag_entry->contact->first_name);
            }
            cell = cell->next[lvl_max - i];

        }

        int choice = 0;
        printf("Quel est votre choix ?\n");
        scanf("%d", &choice);
        if (choice < 1 || choice > j) {
            printf("Erreur : choix invalide\n");
            return search(agenda);
        }
        for (int k = 0; k < choice - 1; k++) {
            head = head->next[lvl_max - i];
        }
        cell = head;
        if (i == 4) {
            return cell->ag_entry;
        }
        i++;

    } while (i < 5);
    return NULL; // should never happen
}

t_agenda_entry *search_if_contact_exist(t_d_list list, char *first_name, char *last_name){
    t_d_cell *temp = list.heads[0];
    while (temp != NULL){
        if (strcmp(temp->ag_entry->contact->first_name,first_name) == 0 && strcmp(temp->ag_entry->contact->last_name,last_name) == 0){
            return temp->ag_entry;
        }
        temp = temp->next[0];
    }
    return NULL;
}