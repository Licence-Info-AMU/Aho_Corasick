/* 
 * File:   utils.c
 * Author: Gaëtan
 *
 * Created on 28 septembre 2017, 19:07
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

//Copy a char ** on a new char**
char ** copy_argv(char** argv,int start,int size){
    // allocate memory and copy strings
    char** new_argv = malloc((size-start) * sizeof (char *));
    if(new_argv==NULL){
        perror("malloc");
        exit(1);
    }
    for(int i = 0; i < size-start; ++i){
        size_t length = strlen(argv[i+start])+1;
        new_argv[i] = malloc(length* sizeof(char *));
        memcpy(new_argv[i], argv[i+start], length);
    }
    return new_argv;
}

//show a char** contain
void show_argv(char** argv,int size){
	//show argv contain or a string tab
    for(int i = 0; i < size; ++i){
        printf("%s\n", argv[i]);
    }
}

//Free a char**
void free_argv(char** argv,int size){
    for(int i = 0; i < size; ++i){
        free(argv[i]);
    }
    free(argv);
}

void free_tabIntInt(int ** tabInt, int size){
	for(int i = 0; i < size; ++i){
        free(tabInt[i]);
    }
    free(tabInt);
}

// string comparison function : linux man qsort
static int cmpstringp(const void *p1, const void *p2){
   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

//sort a char **
void sort_words(char ** words,int size){
	qsort(words, size, sizeof(char*), cmpstringp);
}

//initialisation with argv of words table
char ** init_words(char ** argv,int start,int end){
    char **words=copy_argv(argv,start,end);
    sort_words(words,end-start);
    return words;
}
