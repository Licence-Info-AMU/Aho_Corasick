/* 
 * File:   main.c
 * Author: Lucas,Gaëtan
 *
 * Created on 28 septembre 2017, 19:07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "AhoCorasick.h"

int main(int argc, char* argv[]){
    char filename[200]="fichiers/fichiertest.txt";
    if(argc <= 2){
        printf("tip : %s fichier_à_lire mot1 mot2 ...\n", argv[0]);
        exit(0);
    }
    sprintf(filename, "fichier/%s",argv[1]);
    char** words=init_words(argv,2,argc);
    show_argv(words,argc-2);
    printf("\n");
    int nb_etats; 
    char ** prefix=genere_prefix(words,0,argc-2,&nb_etats);
    show_argv(prefix,nb_etats);
    printf("%d\n", nb_etats);
    int ** commande=tableau_commande(prefix,nb_etats);
    show_tableau_commande(commande,nb_etats);
    int * erreur=tableau_erreur(prefix,nb_etats);
    show_tableau_erreur(erreur,nb_etats);
    fuuuuusion(commande,erreur,nb_etats);
    show_tableau_commande(commande,nb_etats);
    return 0;
}