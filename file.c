/* 
 * File:   file.c
 * Author: Gaëtan
 *
 * Created on 28 septembre 2017, 21:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void read_file(char * filename){
    FILE *fichier = fopen(filename,"r");
    if (fichier != NULL){
        //lire le fichier ici
        fclose(fichier);
    }
    else{
        perror(filename);
        exit(1);
    }
}