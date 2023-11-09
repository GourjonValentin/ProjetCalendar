//
// Created by valen on 09/11/2023.
//

#include "stdlib.h"
#include "stdio.h"
#include "list.h"

int main(){

    t_d_list *L;
    L = create_list(5);
    print_aligned_list(L);
    t_d_cell *C0;
    C0 = create_cell(6, 2);
    insert_head(L, C0);
    print_aligned_list(L);
    t_d_cell *C;
    C = create_cell(5, 5);
    insert_head(L, C);
    print_aligned_list(L);
    C = create_cell(2, 3);
    insert_head(L, C);
    print_aligned_list(L);
    return 0;
};
