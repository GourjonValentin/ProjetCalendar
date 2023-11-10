//
// Created by valen on 09/11/2023.
//

#include "stdlib.h"
#include "stdio.h"
#include "list.h"
#include "cell.h"
#include "testing.h"

int main(){

    t_d_list *L;
    int n = 16;
    L = create_filled_list(n);
    //print_aligned_list(L);

    printf("Comparing search time for classic and optimized search algorithms for a list of size %d\n", n);
    printf("Times are in milliseconds\n");
    printf("\n");
    printf("Classic search: \n");
    test_search_time(L, &classic_search);
    printf("\n");
    printf("Optimized search: \n");
    test_search_time(L, &optimized_search);

    return 0;



};
