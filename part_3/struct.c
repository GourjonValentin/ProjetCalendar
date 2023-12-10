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
    contact->first_name = string_to_low(first_name);
    contact->last_name = string_to_low(last_name);
    return contact;
}

t_event *create_event(t_date date, t_time time, t_time duration, char *name){
    t_event *event = malloc(sizeof(t_event));
    event->date = date;
    event->time = time;
    event->duration = duration;
    event->name = name;
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

int search_if_contact_exist(t_d_list *list, char *first_name, char *last_name){
    t_d_cell *temp = list->heads[0];
    while (temp != NULL){
        if (strcmp(temp->ag_entry->contact->first_name,first_name) == 0 && strcmp(temp->ag_entry->contact->last_name,last_name) == 0){
            return 1;
        }
        temp = temp->next[0];
    }
    return 0;
}

void create_event_for_contact(t_d_list *list,t_agenda_entry *agenda_entry){
    if (search_if_contact_exist(list,agenda_entry->contact->first_name,agenda_entry->contact->last_name) == 0){
        t_contact *newContact = create_contact(agenda_entry->contact->first_name,agenda_entry->contact->last_name);
        insert_sorted(list,create_agenda_entry(newContact));
    }
    printf("Enter the date of the event (dd/mm/yyyy) :");
    t_date date;
    scanf("%d/%d/%d",&date.day,&date.month,&date.year);
    printf("Enter the time of the event (hh:mm) :");
    t_time time;
    scanf("%d:%d",&time.hour,&time.minute);
    printf("Enter the duration of the event (hh:mm) :");
    t_time duration;
    scanf("%d:%d",&duration.hour,&duration.minute);
    printf("Enter the name of the event :");
    char *name = scanString();
    t_event *event = create_event(date, time, duration, name);
    add_event_to_contact(event,agenda_entry);
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