//
// Created by valen on 11/11/2023.
//

#ifndef PROJETCALENDAR_STRUCT_H
#define PROJETCALENDAR_STRUCT_H

typedef struct date {
    int day;
    int month;
    int year;
} t_date;

typedef struct time {
    int hour;
    int minute;
} t_time;

typedef struct event {
    t_date date;
    t_time time;
    t_time duration;
    char *name;
} t_event;

typedef struct event_list {
    t_event *event;
    struct event_list *next;
} t_event_list;

typedef struct contact {
    char *first_name;
    char *last_name;
} t_contact;

typedef struct agenda_entry {
    t_contact *contact;
    t_event_list *events;
} t_agenda_entry;

char* scanString(void);
void print_event_from_contact(t_agenda_entry *ag_entry);

char* string_to_low(char* string);
t_contact *create_contact(char* first_name, char* last_name);
t_event *create_event(t_date date, t_time time, t_time duration, char *name);
t_agenda_entry *create_agenda_entry(char* first_name, char* last_name);
void add_event_to_contact(t_event *event, t_agenda_entry *agenda_entry);
void create_event_for_contact(t_agenda_entry *agenda_entry);



#endif //PROJETCALENDAR_STRUCT_H
