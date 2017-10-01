/* 
 * File:   utils.c
 * Author: Gaëtan
 *
 * Created on 28 septembre 2017, 19:07
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strings.h"

void init_Strings(Strings * strings){
	strings->size = 0;
}

void init_Strings_with_size(Strings * strings,int size){
	strings->size = size;
	strings->tabStr = malloc((strings->size) * sizeof (char *));
	if(strings->tabStr==NULL){
        perror("malloc strings->tabstr Strings");
        exit(1);
   }
}

int count_occurence_in_str(char * str,const char separator){
	int count = 0;
	for (int i=0; str[i]; i++)
		count += (str[i] == separator);	
	return count;
}

Strings convert_str_into_TabStr_by_separator(char * str,const char separator){
	char *token = NULL;
	char* str_copy = malloc(strlen(str) + 1);
	strcpy(str_copy,str);
	Strings strings;
	int i = 0;
	init_Strings_with_size(&strings,count_occurence_in_str(str,separator)+1);
	token = strtok(str_copy, &separator);
	while(token != NULL){
		size_t length = strlen(token)+1;
		strings.tabStr[i] = malloc(length* sizeof(char *));
		memcpy(strings.tabStr[i], token, length);
		printf( " %s\n", strings.tabStr[i] );
		printf( " %d\n",i);
		i++;
		token = strtok(NULL, &separator);
   }
   free(token);
   free(str_copy);
   return strings;
}
