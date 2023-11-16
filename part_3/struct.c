//
// Created by valen on 11/11/2023.
//

#include "struct.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

char* scanString(void){
    char *string = malloc(sizeof(char)*100);
    scanf("%s", string);
    realloc(string, sizeof(char)*strlen(string));
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
    printf("%s",ag_entry->contact->first_name);
    printf("%s",ag_entry->contact->last_name);
    if (ag_entry->events == NULL){
        printf("No events for this contact");
        return;
    }
    t_event_list *temp = ag_entry->events;
    while (temp != NULL){
        printf("Name : %s\n",temp->event->name);
        printf("Date : %d/%d/%d\n",temp->event->date.day,temp->event->date.month,temp->event->date.year);
        printf("Time : %d:%d\n",temp->event->time.hour,temp->event->time.minute);
        printf("Duration : %d:%d\n",temp->event->duration.hour,temp->event->duration.minute);
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

t_agenda_entry* create_agenda_entry(char* first_name, char* last_name){
    t_agenda_entry *agenda_entry = malloc(sizeof(t_agenda_entry));
    agenda_entry->contact = create_contact(first_name, last_name);
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