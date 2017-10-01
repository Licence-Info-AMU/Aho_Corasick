/* 
 * File:   strings.h
 * Author: Gaëtan
 *
 * Created on 1 octobre 2017, 22:23
 */

#ifndef STRINGS_H
#define	STRINGS_H

typedef struct {
	char** tabStr;
	int size;
} Strings;

void init_Strings(Strings * strings);

void init_Strings_with_size(Strings * strings,int size);

int count_occurence_in_str(char * str,const char separator);

Strings convert_str_into_TabStr_by_separator(char * str,const char separator);

#endif	/* STRINGS_H */

