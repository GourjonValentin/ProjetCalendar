//
// Created by valen on 11/11/2023.
//

#include "struct.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

char* scanString(void){
    char *string = malloc(sizeof(char)*100);
    scanf("%s", string);
    realloc(string, sizeof(char)*strlen(string));
    return string;
}