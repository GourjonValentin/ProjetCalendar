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
    char *name;
} t_event;

typedef struct event_list {
    t_event *event;
    struct event_list *next;
} t_event_list;

typedef struct contact {
    char *first_name;
    char *last_name;
    t_event_list *events;
} t_contact;



#endif //PROJETCALENDAR_STRUCT_H
