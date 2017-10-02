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
	strings->tabStr = NULL;
}

void init_Strings_with_size(Strings * strings,int size){
	strings->size = size;
	strings->tabStr = NULL;
	strings->tabStr = malloc((strings->size) * sizeof (char *));
	if(strings->tabStr==NULL){
        perror("malloc strings->tabstr Strings");
        exit(1);
   }
}

int count_occurence_in_str(char * str,const char separator){
	int count = 0;
	size_t length = strlen(str);
	printf("length str : %d\n",(int)length);
	for (int i=0; str[i]; i++){
		count += ((str[i] == separator) && (i != length-1) && (str[i+1] != separator));
		printf("i et count : %d - %d\n",i, count);
	}
	return count;
}

Strings convert_str_into_TabStr_by_separator(char * str,const char separator){
	char *token = NULL;
	Strings strings;
	int i = 0;
	int tmp=count_occurence_in_str(str,separator)+1;
	init_Strings_with_size(&strings,tmp);
	printf("tmpp %d\n",tmp );
	token = strtok(str, &separator);
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
	token=NULL;
	
   return strings;
}
