/* 
 * File:   AhoCorasick.c
 * Author: Lucas,Gaëtan
 *
 * Created on 28 septembre 2017, 19:07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * ajouteprefix(int size,char * mot){
    char *prefix=malloc(sizeof(char)*size);
    memcpy(prefix, mot, size);
    return prefix;
}

char ** genere_prefix(char * mots[],int start,int end,int * nb_etats){			//argv,2,argc, un pointeur sur un entier
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
                    for (int j = 0; j < sizeprefix; ++j){					//compare toute les letre au mot précédent
                        if ( prefix[etats-1][j]!=mots[nummots][j]){
                            prefix[etats]=ajouteprefix(sizeprefix,mots[nummots]);
                            etats++;
                            break;
                        }
                    }
                }
            }
        }
    }
    * nb_etats=etats;
    return prefix;
}

int ** tableau_commande(char ** prefix,int nb_etats){
    int ** commande=malloc(sizeof(int *)*nb_etats+1);
    if(commande==NULL){
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < nb_etats+1; ++i){
        commande[i]=calloc(26,sizeof(int));
        if(commande[i]==NULL){
            perror("calloc");
            exit(1);
        }
    }
    int sizeprefix=1,firstprefix=-1,nextfirstprefix=0;
    for (int numprefix = 0; numprefix < nb_etats; ++numprefix){
        if(strlen(prefix[numprefix])==sizeprefix){
            if(sizeprefix==1){
                commande[0][prefix[numprefix][0]-'a']=numprefix+1;			// met le numérot de l'etat correspondant au prefix dans la case de la lette/0 (prefix[numprefix][sizeprefix-1]-'a')
            }
            else{
                int preprefix=-1;
                for (int i = firstprefix; preprefix==-1 && i < nextfirstprefix; ++i){
                    for (int lettre = 0; lettre < sizeprefix-1; ++lettre){				// on compare les prefix précédent au préfix actuel
                        if(prefix[i][lettre]!=prefix[numprefix][lettre]){
                            break;
                        }
                        else if(lettre==sizeprefix-2){
                            preprefix=i;												// on trouve le préfix du préfix
                        }
                    }
                }
                if (preprefix!=-1){
                    commande[preprefix+1][prefix[numprefix][sizeprefix-1]-'a']=numprefix+1;	// met le numérot de l'etat correspondant au prefix dans la case de la lette/preprefix (prefix[numprefix][sizeprefix-1]-'a')
                }
                else{
                    printf("%s %s %s \n",prefix[numprefix],prefix[firstprefix],prefix[nextfirstprefix]);
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
    for (int j = 0; j < 26; ++j){
            printf("\t%c",j+'a' );
    }
    for (int i = 0; i < nb_etats+1; ++i){
        printf("%d :\t", i);
        for (int j = 0; j < 26; ++j){
            printf("%d\t", commande[i][j]);
        }
        printf("\n");
    }
    return commande;
}

/*int ** tableau_erreur(){

}

int ** fuuuuusion(){

}*/