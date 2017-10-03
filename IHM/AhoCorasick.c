/* 
 * File:   AhoCorasick.c
 * Author: Lucas,Gaëtan
 *
 * Created on 28 septembre 2017, 19:07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AhoCorasick.h"
#include "strings.h"
#include "utils.h"

#define NBCARAC	256
#define FIRSTCARAC	0

char * ajouteprefix(int size,char * mot){
	char *prefix=calloc(size,sizeof(char));
	if(prefix==NULL){
		perror("malloc");
		exit(1);
	}
	memcpy(prefix, mot, size);
	return prefix;
}

char ** genere_prefix(char ** mots,int start,int end,int * nb_etats){			//argv,2,argc, un pointeur sur un entier
	int nbprefixmax=0,sizeprefixmax=0;
	for (int nummots=start; nummots < end; ++nummots){
		int taillemot=strlen(mots[nummots]);
		nbprefixmax+=taillemot;
		if (sizeprefixmax < taillemot){
			sizeprefixmax = taillemot;
		}
	}
	printf("sizeprefixmax = %d , nbprefixmax = %d \n",sizeprefixmax,nbprefixmax);		// affichage première partie 
	char ** prefix = malloc(sizeof(char *)*nbprefixmax);
	if(prefix==NULL){
		perror("malloc");
		exit(1);
	}
	int isfirst;
	int etats=0;
	for (int sizeprefix = 1; sizeprefix <= sizeprefixmax; ++sizeprefix){		// genere les prefix taille par taille
		isfirst=1;
		for (int nummots = start; nummots < end; ++nummots){	//parcour tout les mots
			if(sizeprefix <= strlen(mots[nummots])){
				if(isfirst){													//premier mot de cette taile
					isfirst=0;
					prefix[etats]=ajouteprefix(sizeprefix,mots[nummots]);
					etats++;
				}
				else {
					int tmp=strncmp(mots[nummots],prefix[etats-1],sizeprefix);	//comparaison des deux string jusqu'a sizeprefix
					if (tmp > 0){												
						prefix[etats]=ajouteprefix(sizeprefix,mots[nummots]);
						etats++;
					}
					else if(tmp < 0){											//tmp est censer etre positif vu qu'on a trié avant
						perror("tris ascii");
					}
				}
			}
		}
	}
	*nb_etats=etats;
	return prefix;
}

int ** tableau_commande(char ** prefix,int nb_etats){
	int ** commande=malloc(sizeof(int *)*nb_etats+1);
	if(commande==NULL){
		perror("malloc");
		exit(1);
	}
	for (int i = 0; i < nb_etats+1; ++i){
		commande[i]=calloc(NBCARAC,sizeof(int));
		if(commande[i]==NULL){
			perror("calloc");
			exit(1);
		}
	}
	int sizeprefix=1,firstprefix=-1,nextfirstprefix=0;
	for (int numprefix = 0; numprefix < nb_etats; ++numprefix){
		if(strlen(prefix[numprefix])==sizeprefix){
			if(sizeprefix==1){
				commande[0][prefix[numprefix][0]-FIRSTCARAC]=numprefix+1;			// met le numérot de l'etat correspondant au prefix dans la case de la lette/0 (prefix[numprefix][sizeprefix-1]-'a')
			}
			else{
				int preprefix=-1;
				for (int i = firstprefix; preprefix==-1 && i < nextfirstprefix; ++i){
					if(strncmp(prefix[numprefix],prefix[i],sizeprefix-1) == 0){	//comparaison des deux string jusqu'a sizeprefix-1
						preprefix=i;											// on trouve le préfix du préfix
					}
				}
				if (preprefix!=-1){
					commande[preprefix+1][prefix[numprefix][sizeprefix-1]-FIRSTCARAC]=numprefix+1;	// met le numérot de l'etat correspondant au prefix dans la case de la lette/preprefix (prefix[numprefix][sizeprefix-1]-'a')
				}
				else{
					printf("%s %s %s \n",prefix[numprefix],prefix[firstprefix],prefix[nextfirstprefix]);			//perror si on a pas trouver le prefix du prefix
					perror("commande");
				}
			}
		}
		else{													//on change et on recommence car prefix de taille supérieur
			sizeprefix++;
			firstprefix=nextfirstprefix;
			nextfirstprefix=numprefix;
			numprefix--;												// est-ce moche ?
		}
	}
	return commande;
}

void show_tableau_commande(int ** commande, int nb_etats){
	printf("\ntableau commande :\n");
	int util[NBCARAC];
	for (int j = 0; j < NBCARAC; ++j){
		util[j]=0;
		for (int i = 0; i < nb_etats+1; ++i){
			if(commande[i][j]!=0){
				util[j]=1;
				break;
			}
		}
	}
	for (int j = 0; j < NBCARAC; ++j){
		if(util[j]==1){
			printf("\t%c",j+FIRSTCARAC );
		}
	}
	printf("\n");
	for (int i = 0; i < nb_etats+1; ++i){
		printf("%d :\t", i);
		for (int j = 0; j < NBCARAC; ++j){
			if(util[j]==1){
				printf("%d\t", commande[i][j]);
			}
		}
		printf("\n");
	}
}


int * tableau_erreur(char ** prefix,int nb_etats){
	int * tab_erreur=calloc(nb_etats,sizeof(int));
	for (int numprefix = 0; numprefix < nb_etats; ++numprefix){
		if(strlen(prefix[numprefix])>1){											// pour tout les prefix de plus d'un lettre
			int sufix=0;
			int diffsize=strlen(prefix[numprefix])-strlen(prefix[sufix]);
			while(diffsize>0){														// on regarde parmis tout les prefix plus petit qu'eux
				if(strcmp(prefix[numprefix]+diffsize,prefix[sufix]) == 0 ){			// si l'un d'entre eux resemble a leur sufix et on prend le plus grand d'entre eux
					tab_erreur[numprefix]=sufix+1;
				}
				++sufix;
				diffsize=strlen(prefix[numprefix])-strlen(prefix[sufix]);
			}
		}
	}
	return tab_erreur;
}

void show_tableau_erreur(int * erreur,int nb_etats){
	printf("\ntableau erreur :\n");
	for (int i = 0; i < nb_etats; ++i){
		printf("%d\t: %d\n",i,erreur[i]);
	}
}


void fuuuuusion(int ** commande,int * erreur,int nb_etats){
	for (int etat = 0; etat < nb_etats; ++etat){
		if(erreur[etat]>0){					// pour tout les etats qui on un retour en cas d'erreur
			for (int i = 0; i < NBCARAC; ++i){
				if(commande[etat+1][i]==0 && commande[erreur[etat]][i]!=0){
					commande[etat+1][i]=commande[erreur[etat]][i];			// ajout des transition non 0 de l'erreur[etat]  sur les transition 0 de l'etat
				}
			}
		}
	}
}


int * etat_finaux(char ** mots,int nbmots,char ** prefix,int nb_etats){
	int * etat_finaux=calloc(nb_etats,sizeof(int));
	if(etat_finaux==NULL){
		perror("calloc");
		exit(1);
	}
	for (int etat = 0; etat < nb_etats; ++etat){
		for (int i = 0; i < nbmots; ++i){
			if(strcmp(prefix[etat],mots[i]) == 0){
				etat_finaux[etat]=strlen(prefix[etat]);
			}
		}
	}
	return etat_finaux;
}

int nextetat(int ** commande,int etat, char lettre ){
	int read=0;
	for (int i = 0; i < NBCARAC; ++i){	//tester si la lettre est dans commande
		if ((int)lettre== i+FIRSTCARAC){
			read=1;
			break;
		}
	}
	if (read){
		return commande[etat][(int)lettre-FIRSTCARAC];
	}
	return 0;
}

int ** build_commande(char ** prefix,int nb_etats){
	int ** commande=tableau_commande(prefix,nb_etats);
	show_tableau_commande(commande,nb_etats);
	
	int * erreur=tableau_erreur(prefix,nb_etats);
	show_tableau_erreur(erreur,nb_etats);
	
	fuuuuusion(commande,erreur,nb_etats);
	show_tableau_commande(commande,nb_etats);
	free(erreur);
	erreur=NULL;
	return commande;
}

void search_words(char * words, const char separator,char * text){
    Strings strings = convert_str_into_TabStr_by_separator(words,separator);
    show_argv(strings.tabStr,strings.size);
    printf("\n");
    sort_words(strings.tabStr,strings.size);
    show_argv(strings.tabStr,strings.size);
    printf("\n");

    int nb_etats;
    char ** prefix=genere_prefix(strings.tabStr,0,strings.size,&nb_etats);
    show_argv(prefix,nb_etats);
    
    int * etats_finaux = etat_finaux(strings.tabStr,strings.size,prefix,nb_etats);
    
    int ** commande=build_commande(prefix,nb_etats);

    //ici free prefix
    
    int currentState = 0;
 
    //On cherche dans le texte
    for (int i = 0; i < strlen(text); ++i){
        currentState = nextetat(commande,currentState,text[i]);
        printf("currentState : %d\n",currentState);
        //On continue si rien ne correspond
        if (etats_finaux[currentState] != 0){//On continue si rien ne correspond
            printf("on a trouver un mot !!! debut du mot : %d fin du mot %d\n",i-etats_finaux[currentState],i );	// le mot c'est prefix[currentState-1]
        }
    }
    
    //free zone
    free_argv(strings.tabStr,strings.size);
    free_argv(prefix,nb_etats);
    
    free(etats_finaux);
    etats_finaux=NULL;
        
    free_tabIntInt(commande,nb_etats+1);
}
