/* 
 * File:   utils.h
 * Author: Gaëtan
 *
 * Created on 28 septembre 2017, 19:10
 */

#ifndef UTILS_H
#define	UTILS_H

//Copy a char ** on another char**
char**  copy_argv(char** argv,int start,int size);

//show a char** contain
void show_argv(char** argv,int size);

//Free a char**
void free_argv(char** argv,int size);

void free_tabIntInt(int ** tabInt, int size);

//sort a char **
void sort_words(char ** words,int size);

//initialisation with argv of words table
char ** init_words(char ** argv,int start,int end);

#endif	/* UTILS_H */

