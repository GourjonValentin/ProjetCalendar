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

void print_event_from_contact(t_contact *contact){
    printf("%s",contact->first_name);
    printf("%s",contact->last_name);
    if (contact->events == NULL){
        printf("No events for this contact");
        return;
    }
    t_event_list *temp = contact->events;
    while (temp != NULL){
        printf("Name : %s",temp->event->name);
        printf("Date : %d/%d/%d",temp->event->date.day,temp->event->date.month,temp->event->date.year);
        printf("Time : %d:%d",temp->event->time.hour,temp->event->time.minute);
        printf("Duration : %d:%d",temp->event->duration.hour,temp->event->duration.minute);
        temp = temp->next;
    }
}