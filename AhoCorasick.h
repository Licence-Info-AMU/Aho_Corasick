/* 
 * File:   AhoCorasick.h
 * Author: Gaëtan
 *
 * Created on 28 septembre 2017, 21:25
 */

#ifndef AHOCORASICK_H
#define	AHOCORASICK_H

char * ajouteprefix(int size,char * mot);

char ** genere_prefix(char * mots[],int start,int end,int * nb_etats);

int ** tableau_commande(char ** prefix,int nb_etats);

#endif	/* AHOCORASICK_H */

