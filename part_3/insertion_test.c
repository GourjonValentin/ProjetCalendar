//
// Created by valen on 16/11/2023.
//

#include "insertion_test.h"
#include "struct.h"
#include "cell.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion_test() {
    t_d_list * agenda = create_list();
    char *input = malloc(sizeof(char) * 100);
    input = "init";
    while (strcmp(input, "stop") != 0){
        printf("Enter command\n(insert, stop)\n");
        input = scanString();
        if (strcmp(input, "insert") == 0){
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

        print_list(agenda);


    }
    printf("End of insertion test\n");
    return;
}
