//
// Created by valen on 06/12/2023.
//

#include "menu1.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell1.h"
#include "list1.h"
#include "testing1.h"


void menu1() {
    printf("Bienvenue sur le calendrier\n");
    int level = 0;
    // Test partie 2
    printf("Quel est le nombre de niveaux de la liste ?\n");
    scanf("%d", &level);

    t_d_list1 *L = create_filled_list1(level);
    int choice = 0;
    do {
        printf("Que voulez-vous faire ?\n");
        printf("1 : Afficher la liste\n");
        printf("2 : Afficher la liste alignee\n");
        printf("3 : Effectuer une recherche\n");
        printf("4 : Comparaison des recherches\n");
        printf("5 : Changer le niveau de la liste\n");
        printf("6 : Comparaison entre les niveaux\n");
        printf("7 : Quitter\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                print_list1(L);
                break;
            case 2:
                print_aligned_list1(L);
                break;
            case 3:
                printf("Quelle valeur voulez-vous chercher ?\n");
                int value;
                scanf("%d", &value);
                printf("Recherche classique : ");
                printf("position %s\n", classic_search1(L, value) == -1 ? "Non trouve" : "trouve");
                printf("Recherche optimisee : ");
                printf("position %s\n", optimized_search1(L, value) == -1 ? "Non trouve" : "trouve");
                break;
            case 4:
                test_search_time(level);
                break;
            case 5:
                printf("Quel est le nouveau niveau de la liste ?\n");
                scanf("%d", &level);
                L = create_filled_list1(level);
                break;
            case 6:

            case 7:
                printf("Au revoir !\n");
                choice = -1;
                break;
            default:
                printf("Choix invalide\n");
                choice = 0;
                break;
        }
    } while (choice != -1);
}

