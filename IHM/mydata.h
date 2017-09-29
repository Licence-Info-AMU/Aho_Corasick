/**
 * \file mydata.h
 * \brief Mydata structure avec les objets principaux
 * \author Gaëtan Perrot
 * \version 0.1
 * \date 23 avril 2017
 *
 * Mydata structure avec les objets principaux
 *
 */

#ifndef MYDATA_H
#define MYDATA_H

/**
 * \struct Mydata
 * \brief Objet contenant les informations pour un Mydata
 *
 * Objet contenant les informations pour un Mydata
 */
typedef struct {
    GtkWidget *window;					/*!< Fenêtre principale. */ 
    int win_width;						/*!< Largeur Fenêtre principale. */ 
    int win_height;						/*!< Hauteur Fenêtre principale. */ 
    unsigned int magic;					/*!< Nombre magique. */ 
    char * current_folder;				/*!< Dossier courant. */ 
    char *title;						/*!< Titre de la fenêtre principale. */ 
    GtkWidget *vbox;					/*!< Vertical box. */ 
    GtkWidget *hbox;					/*!< Horizontal box. */ 
    GtkWidget *p_text_view;				/*!< Texte view. */ 
    gchar *contents;					/*!< Contenu du fichier. */ 
    GtkWidget *p_text_view_scroll;		/*!< Scroll bar. */ 
    GtkWidget *menu_bar;				/*!< Barre menu. */ 
} Mydata;

/**
 * \fn Mydata *get_mydata (gpointer data)
 * \brief Fonction de récupération de l'objet Mydata à partir d'un gpointeur
 *
 * \param self Un Mydata passé sous forme de gpointer
 * \return Mydata * si aucune erreur, NULL sinon.
 */
Mydata *get_mydata (gpointer data);

/**
 * \fn void init_mydata(Mydata *my)
 * \brief Fonction d'initialisation de l'objet Mydata
 *
 * \param self Un objet Mydata
 * \return void
 */
void init_mydata(Mydata *my);

#endif /* MYDATA_H */

