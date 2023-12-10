//
// Created by valen on 09/11/2023.
//

#include "stdlib.h"
#include "stdio.h"

#include "part1-2/menu1.h"
#include "part_3/menu.h"


int main(){
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("voulez vous avoir acces a : \n");
    printf("partie 1/2: 1\n");
    printf("partie  3 : 2\n");
    printf("exit : 3\n");
    int choice = 0;
    scanf(" %d",&choice);
    if (choice == 1){
        menu1();
    } else if (choice == 2){
        menu();
    } else if (choice == 3){
        printf("exit\n");
        return 0;
    }
    return 0;
}
