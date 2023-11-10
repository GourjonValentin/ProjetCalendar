//
// Created by valen on 10/11/2023.
//

#ifndef PROJETCALENDAR_TESTING_H
#define PROJETCALENDAR_TESTING_H

#include "timer.h"
#include "list.h"


// Test protocol :
// 1. Create a list of size 16
// 2. Search for a random value in the list
// 3. Repeat 2. 1000 times / 10000 times / 100000 times

// function that execute the above protocol for a given search function
void test_search_time(t_d_list *list, int (*search_function)(t_d_list *, int));



#endif //PROJETCALENDAR_TESTING_H
