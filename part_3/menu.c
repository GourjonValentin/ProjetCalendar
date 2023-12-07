//
// Created by valen on 19/11/2023.
//

#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cell.h"
#include "list.h"
#include "struct.h"

void menu() {
    printf("Welcome to the calendar\n");
    int choice = 0;
    t_d_list *calendar = create_list();
    while (choice != -1) {
        printf("What do you want to do ?\n");
        printf("1 : Search for a contact\n");
        printf("2 : See all events for a contact\n");
        printf("3 : Add a contact\n");
        printf("4 : Add an event for a contact\n");
        printf("5 : Delete an event\n");
        printf("6 : Save events to ta file\n");
        printf("7 : Load events from a file\n");
        printf("8 : See insertion performance\n");
        printf("9 : Exit app\n");

        scanf("%d", &choice);}
        assert(choice >= 1 && choice <= 9);
}