//
// Created by valen on 11/11/2023.
//

#include "struct.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "list.h"

char* scanString(void){
    char *string = malloc(sizeof(char)*100);
    fflush(stdin);
    scanf("%s", string); //fixme : use fgets instead mb ?

    string = realloc(string, sizeof(char)*strlen(string)+1);
    return string;
}

char* string_to_low(char* string) {
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] >= 65 && string[i] <= 90) {
            string[i] += 32;
        }
    }
    return string;
}

void print_event_from_contact(t_agenda_entry *ag_entry){
    printf("%s ",ag_entry->contact->first_name);
    printf("%s\n",ag_entry->contact->last_name);
    if (ag_entry->events == NULL){
        printf("No events for this contact\n");
        return;
    }
    t_event_list *temp = ag_entry->events;
    while (temp != NULL){
        printf("Name : %s\n\r",temp->event->name);
        printf("Date : %d/%d/%d\n\r",temp->event->date.day,temp->event->date.month,temp->event->date.year);
        printf("Time : %dh%dm\n\r",temp->event->time.hour,temp->event->time.minute);
        printf("Duration : %dh%dm\n\r",temp->event->duration.hour,temp->event->duration.minute);
        temp = temp->next;
    }
}

t_contact *create_contact(char* first_name, char* last_name){
    t_contact *contact = malloc(sizeof(t_contact));
    contact->first_name = malloc(sizeof(char)*strlen(first_name)+1);
    contact->last_name = malloc(sizeof(char)*strlen(last_name)+1);
    contact->first_name = strcpy(contact->first_name,string_to_low(first_name));
    contact->last_name = strcpy(contact->last_name, string_to_low(last_name));
    return contact;
}

t_event *create_event(t_date date, t_time time, t_time duration, char *name){
    t_event *event = malloc(sizeof(t_event));
    event->date = date;
    event->time = time;
    event->duration = duration;
    event->name = malloc(sizeof(char)*strlen(name)+1);
    event->name = strcpy(event->name,name);
    return event;
}

t_agenda_entry* create_agenda_entry(t_contact *contact) {
    t_agenda_entry *agenda_entry = malloc(sizeof(t_agenda_entry));
    agenda_entry->contact = contact;
    agenda_entry->events = NULL;
    return agenda_entry;
}

void add_event_to_contact(t_event *event,t_agenda_entry *agenda_entry){
    if (agenda_entry->events == NULL){
        t_event_list *event_list = malloc(sizeof(t_event_list));
        event_list->event = event;
        event_list->next = NULL;
        agenda_entry->events = event_list;
        return;
    }
    t_event_list *event_list = malloc(sizeof(t_event_list));
    event_list->event = event;
    event_list->next = agenda_entry->events;
    agenda_entry->events = event_list;
}


void create_event_for_contact(t_agenda_entry *agenda_entry){
    printf("Name of the event: \n");
    char *name = scanString();
    int day = -1;
    int month = 1;
    int year = -1;
    int hour = -1;
    int minute = -1;
    int duration_hour = -1;
    int duration_minute = -1;
    char term;

    do {
        printf("Day : \n");
        if (scanf("%d%c",&day, &term) != 2 || term != '\n') {
            printf("Saisie invalide\n");
            fflush(stdin);
            day = -1;
        }
    } while (day < 1 || day > 31);
    do {
        printf("Month : \n");
        if (scanf("%d%c",&month, &term) != 2 || term != '\n') {
            printf("Saisie invalide\n");
            fflush(stdin);
            month = -1;
        }
    } while (month < 1 || month > 12);
    do {
        printf("Year : \n");
        if (scanf("%d%c",&year, &term) != 2 || term != '\n') {
            printf("Saisie invalide\n");
            fflush(stdin);
            year = -1;
        }
    } while (year < 2023);
    do {
        printf("Hour : \n");
        if (scanf("%d%c",&hour, &term) != 2 || term != '\n') {
            printf("Saisie invalide\n");
            fflush(stdin);
            hour = -1;
        }
    } while (hour < 0 || hour > 23);
    do {
        printf("Minute : \n");
        if (scanf("%d%c",&minute, &term) != 2 || term != '\n') {
            printf("Saisie invalide\n");
            fflush(stdin);
            minute = -1;
        }
    } while (minute < 0 || minute > 59);
    do {
        printf("Duration hour : \n");
        if (scanf("%d%c",&duration_hour, &term) != 2 || term != '\n') {
            printf("Saisie invalide\n");
            fflush(stdin);
            duration_hour = -1;
        }
    } while (duration_hour < 0 || duration_hour > 23);
    do {
        printf("Duration minute : \n");
        if (scanf("%d%c",&duration_minute, &term) != 2 || term != '\n') {
            printf("Saisie invalide\n");
            fflush(stdin);
            duration_minute = -1;
        }
    } while (duration_minute < 0 || duration_minute > 59);
    t_date date = {day,month,year};
    t_time time = {hour,minute};
    t_time duration = {duration_hour,duration_minute};
    add_event_to_contact(create_event(date,time,duration,name),agenda_entry);
}

void del_event_from_contact(t_agenda_entry *agenda_entry, char *name){
    if (agenda_entry->events == NULL){
        printf("No events for this contact");
        return;
    }
    t_event_list *temp = agenda_entry->events;
    if (strcmp(temp->event->name,name) == 0){
        agenda_entry->events = temp->next;
        free(temp);
        return;
    }
    while (temp->next != NULL){
        if (strcmp(temp->next->event->name,name) == 0){
            t_event_list *temp2 = temp->next;
            temp->next = temp->next->next;
            free(temp2);
            return;
        }
        temp = temp->next;
    }
    printf("No event with this name");
}

