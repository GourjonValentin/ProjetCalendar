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

void save_calendar(t_d_list* agenda){
    printf("Quel nom voulez-vous donner au fichier ?(sans extension)\n");
    printf("ATTENTION : Si le fichier existe déjà, il sera écrasé\n");
    char *name = scanString();
    char *path = malloc(sizeof(char) * 100);
    strcpy(path, name);
    strcat(path, ".txt");

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    t_d_cell *temp = agenda->heads[0];
    while (temp != NULL) {
        fprintf(file, "User\n%s %s\n", temp->ag_entry->contact->first_name, temp->ag_entry->contact->last_name);
        t_event_list *temp_event = temp->ag_entry->events;
        while (temp_event != NULL) {
            fprintf(file, "Event\n%s\n", temp_event->event->name);
            fprintf(file, "%d/%d/%d\n", temp_event->event->date.day, temp_event->event->date.month, temp_event->event->date.year);
            fprintf(file, "%d/%d\n", temp_event->event->time.hour, temp_event->event->time.minute);
            fprintf(file, "%d/%d\n", temp_event->event->duration.hour, temp_event->event->duration.minute);
            temp_event = temp_event->next;
        }
        temp = temp->next[0];
    }
    fclose(file);
}

void load_calendar(t_d_list* agenda) {
    printf("Quel fichier voulez-vous charger ?(sans extension)\n");
    char *name = scanString();
    char *path = malloc(sizeof(char) * 100);
    strcpy(path, name);
    strcat(path, ".txt");

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    char* type;
    type = malloc(sizeof(char) * 10);
    char *first_name, *last_name;
    first_name = malloc(sizeof(char) * 100);
    last_name = malloc(sizeof(char) * 100);
    char *name_event;
    name_event = malloc(sizeof(char) * 100);
    int day, month, year;
    int hour, minute;
    int duration_hour, duration_minute;

    t_agenda_entry *agenda_entry;
    while (fscanf(file, "%s", type) != EOF) {

        if (strcmp(type, "User") == 0) {
            fscanf(file, "%s %s", first_name, last_name);
            agenda_entry = search_if_contact_exist(agenda, first_name, last_name);
            if (NULL == agenda_entry) {
                t_contact *newContact = create_contact(first_name, last_name);
                agenda_entry = create_agenda_entry(newContact);
                insert_sorted(agenda, agenda_entry);
            }
        }

        if (strcmp(type, "Event") == 0) {
            fscanf(file, "%s", name_event);
            fscanf(file, "%d/%d/%d", &day, &month, &year);
            fscanf(file, "%d/%d", &hour, &minute);
            fscanf(file, "%d/%d", &duration_hour, &duration_minute);
            t_date date = {day, month, year};
            t_time time = {hour, minute};
            t_time duration = {duration_hour, duration_minute};
            t_event *event = create_event(date, time, duration, name_event);
            add_event_to_contact(event, agenda_entry);
        }
    }
    fclose(file);
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
                save_calendar(calendar);
                break;
            case 6:
                printf("Load events from a file\n");
                load_calendar(calendar);
                break;
            case 7:
                printf("See insertion performance\n");
                break;
            case 8:
                printf("Exit app\n");
                choice = -1;
                break;
            default:
                printf("Error\n");
                break;

        }
    }
}