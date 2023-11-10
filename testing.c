//
// Created by valen on 10/11/2023.
//

#include "testing.h"
#include "list.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Test protocol :
// 1. Create a list of size 16
// 2. Search for a random value in the list
// 3. Repeat 2. 1000 times / 10000 times / 100000 times

// function that execute the above protocol for a given search function
void test_search_time_for_given_func(t_d_list *list, int (*search_function)(t_d_list *, int)) {
    for (int i = 0; i < 3; i++) {
        double mean = 0;
        int n = 1000 * pow(10, i);

        for (int j = 0; j < n; j++) {
            int value = rand() % (int)(pow(2, list->max_levels) - 1);
            startTimer();
            search_function(list, value);
            stopTimer();
            mean += getTimeAsMsecs();
        }
        printf("Total time for n = %d : %f\n", n, mean);
        mean /= n;
        printf("Mean time for n = %d : %f\n", n, mean);
        printf("\n");
    }
}

void test_search_time(int n_levels) {
    t_d_list *L;
    L = create_filled_list(n_levels);
    //print_aligned_list(L);

    printf("Comparing search time for classic and optimized search algorithms for a list of size %d\n", n_levels);
    printf("Times are in milliseconds\n");
    printf("\n");
    printf("Classic search: \n");
    test_search_time_for_given_func(L, &classic_search);
    printf("\n");
    printf("Optimized search: \n");
    test_search_time_for_given_func(L, &optimized_search);
}