//
// Created by valen on 09/11/2023.
//

#include "stdlib.h"
#include "stdio.h"
#include "list.h"
#include "cell.h"

int main(){

    t_d_list *L;
    L = create_filled_list(5);
    print_aligned_list(L);
    return 0;
};
