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
time_result** test_search_time_for_given_func(t_d_list *list, int (*search_function)(t_d_list *, int)) {

    time_result **results = malloc(sizeof(time_result) * 3);

    for (int i = 0; i < 3; i++) {
        time_result * res = malloc(sizeof(time_result));
        double mean = 0;
        int n = 1000 * pow(10, i);
        res->n = n;

        for (int j = 0; j < n; j++) {
            int value = rand() % (int)(pow(2, list->max_levels) - 1);
            startTimer();
            search_function(list, value);
            stopTimer();
            mean += getTimeAsMsecs();
        }
        printf("Total time for n = %d : %f\n", n, mean);
        res->total_time = mean;

        mean /= n;
        printf("Mean time for n = %d : %f\n", n, mean);
        res->mean_time = mean;
        printf("\n");
    }
    return results;
}

void test_search_time(int n_levels) {
    t_d_list *L;
    time_result** classic_results, **optimized_results;
    L = create_filled_list(n_levels);
    //print_aligned_list(L);

    printf("Comparing search time for classic and optimized search algorithms for a list of size %d\n", n_levels);
    printf("Times are in milliseconds\n");
    printf("\n");
    printf("Classic search: \n");
    classic_results = test_search_time_for_given_func(L, &classic_search);
    printf("\n");
    printf("Optimized search: \n");
    optimized_results = test_search_time_for_given_func(L, &optimized_search);


}