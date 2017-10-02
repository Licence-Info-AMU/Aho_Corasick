/* 
 * File:   AhoCorasick.h
 * Author: Gaëtan
 *
 * Created on 28 septembre 2017, 21:25
 */

#ifndef AHOCORASICK_H
#define	AHOCORASICK_H

char * ajouteprefix(int size,char * mot);

char ** genere_prefix(char ** mots,int start,int end,int * nb_etats);

int ** tableau_commande(char ** prefix,int nb_etats);

void show_tableau_commande(int ** commande, int nb_etats);

int * tableau_erreur(char ** prefix,int nb_etats);

void show_tableau_erreur(int * erreur,int nb_etats);

void fuuuuusion(int ** commande,int * erreur,int nb_etats);

int * etat_finaux(char ** mots,int nbmots,char ** prefix,int nb_etats);

// int startread(int ** commande,char lettre );

int nextetat(int ** commande,int etat, char lettre );

#endif	/* AHOCORASICK_H */

