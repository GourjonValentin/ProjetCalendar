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

void insertion(t_d_list *agenda) {
    printf("Inserting\n");
    char *first_name, *last_name;
    printf("Enter first name\n");
    first_name = scanString();
    printf("Enter last name\n");
    last_name = scanString();
    t_contact *contact = create_contact(first_name, last_name);
    t_agenda_entry *ag_entry = create_agenda_entry(contact);
    insert_sorted(agenda, ag_entry);
    printf("Inserted\n");
}

void searching(t_d_list *agenda) {
    printf("Searching\n");
    t_agenda_entry* result = search(agenda);
    if (result == NULL) {
        printf("No result\n");
    } else {
        printf("Result : %s %s\n", result->contact->first_name, result->contact->last_name);
        printf("Events : \n");
        print_event_from_contact(result);
    }

}

void add_event(t_d_list* agenda) {
    // Nom et prénom du contact
    char *first_name, *last_name;
    printf("Enter first name\n");
    first_name = scanString();
    printf("Enter last name\n");
    last_name = scanString();


    // Recherche si contact existe déjà
    t_agenda_entry *agenda_entry = search_if_contact_exist(agenda, first_name, last_name);
    if (NULL == agenda_entry){
        t_contact *newContact = create_contact(first_name,last_name);
        agenda_entry = create_agenda_entry(newContact);
        insert_sorted(agenda,agenda_entry);
    }
    // Ajout de l'event
    create_event_for_contact(agenda_entry);
}

void del_event(t_d_list* agenda){
    // Nom et prénom du contact
    char *first_name, *last_name;
    printf("Enter first name\n");
    first_name = scanString();
    printf("Enter last name\n");
    last_name = scanString();

    t_agenda_entry *agenda_entry = search_if_contact_exist(agenda, first_name, last_name);
    if (NULL == agenda_entry) {
        printf("This contact doesn't exist\n");
    }
    else {
        //afficher les events
        print_event_from_contact(agenda_entry);

        //demander le nom de l'event à supprimer
        printf("Enter the name of the event you want to delete\n");
        char *name = scanString();
        t_event_list *temp = agenda_entry->events;
        t_event_list *prev = NULL;
        while (temp != NULL) {
            if (strcmp(temp->event->name, name) == 0) {
                if (prev == NULL) {
                    agenda_entry->events = temp->next;
                } else {
                    prev->next = temp->next;
                }
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        printf("This event doesn't exist\n");
    }
}

void menu() {
    printf("Welcome to the calendar\n");
    int choice = 0;
    t_d_list *calendar = create_list();
    while (choice != -1) {
        printf("What do you want to do ?\n");
        printf("1 : Search for a contact\n");
        printf("2 : Add a contact\n");
        printf("3 : Add an event for a contact\n");
        printf("4 : Delete an event\n");
        printf("5 : Save events to ta file\n");
        printf("6 : Load events from a file\n");
        printf("7 : See insertion performance\n");
        printf("8 : Exit app\n");

        scanf("%d", &choice);
        assert(choice >= 1 && choice <= 9);
        switch (choice) {
            case 1:
                printf("Search for a contact\n");
                searching(calendar);
                break;
            case 2:
                printf("Add a contact\n");
                insertion(calendar);
                break;
            case 3:
                printf("Add an event for a contact\n");
                add_event(calendar);
                break;
            case 4:
                printf("Delete an event\n");
                del_event(calendar);
                break;
            case 5:
                printf("Save events to ta file\n");
                break;
            case 6:
                printf("Load events from a file\n");
                break;
            case 7:
                printf("See insertion performance\n");
                break;
            case 8:
                printf("Exit app\n");
                break;
            default:
                printf("Error\n");
                break;

        }
    }
}