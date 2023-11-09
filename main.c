//
// Created by valen on 09/11/2023.
//

#include "stdlib.h"
#include "stdio.h"
#include "structure.h"

int main(){

    t_d_list *L;
    L = create_list(5);
    t_d_cell *C;
    C = create_cell(5, 5);
    insert_sorted(L, C);
    C = create_cell(2, 3);
    insert_sorted(L, C);
    print_list(L);
    return 0;
};
