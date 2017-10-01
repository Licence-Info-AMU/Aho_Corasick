/**
 * \file gui.c
 * \brief Interface graphique
 * \author Gaëtan Perrot
 * \version 0.1
 * \date 23 avril 2017
 *
 * Interface graphique
 *
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydata.h"
#include "strings.h"
#include "AhoCorasick.h"
#include "utils.h"

/**
 * \fn void window_init (GtkApplication* app, gpointer user_data)
 * \brief Fonction d'initialisation de la fenêtre
 *
 * \param self GtkApplication L'application, gpointer objet Mydata
 * \return void
 */
void window_init (GtkApplication* app, gpointer user_data){
    Mydata *my = get_mydata(user_data);
    my->window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (my->window), my->title);
    gtk_window_set_default_size (GTK_WINDOW (my->window), my->win_width, my->win_height);
}

/**
 * \fn void text_view_init (gpointer user_data)
 * \brief Fonction d'initialisation de la zone de texte
 *
 * \param self gpointer objet Mydata
 * \return void
 */
void text_view_init (gpointer user_data){
	Mydata *my = get_mydata(user_data);
	my->p_text_view = gtk_text_view_new ();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(my->p_text_view), FALSE);
	gtk_container_add (GTK_CONTAINER (my->p_text_view_scroll), my->p_text_view);
	gtk_widget_set_sensitive (GTK_WIDGET (my->p_text_view), FALSE);
}

/**
 * \fn void text_view_color(gpointer user_data,int start, int end)
 * \brief Fonction de changement de colro d'une partie du texte
 *
 * \param self gpointer user_data,int start, int end
 * \return void
 */
void text_view_color(gpointer user_data,int start, int end){
	Mydata *my = get_mydata(user_data);
	GtkTextIter startIter, endIter;
	GtkTextBuffer *buffer;	
	GtkTextTag *tag;
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (my->p_text_view));
	tag = gtk_text_buffer_create_tag (buffer, "red_foreground",
	   		            "foreground", "red", NULL);  
	gtk_text_buffer_get_iter_at_offset (buffer, &startIter, start);
	gtk_text_buffer_get_iter_at_offset (buffer, &endIter, end);
	gtk_text_buffer_apply_tag (buffer, tag, &startIter, &endIter);
}

//À finir !
void on_changed_search_entry (GtkSearchEntry *entry,gpointer user_data){
	Mydata *my = get_mydata(user_data);
	const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
	printf("%s\n",entry_text);
	const char separator = ' ';
	printf("strings %d\n",__LINE__);
	Strings strings = convert_str_into_TabStr_by_separator((char *)entry_text,separator);

	//Ancien main problème d'erreur de segmentation, ça pu....
    int nb_etats; 
    printf("prefix %d\n",__LINE__);
    char ** prefix=genere_prefix(strings.tabStr,0,strings.size,&nb_etats);
    printf("show prefix %d\n",__LINE__);
    show_argv(prefix,nb_etats);
    printf("%d\n", nb_etats);
    printf("commande %d\n",__LINE__);
    int ** commande=tableau_commande(prefix,nb_etats);
    printf("show commande %d\n",__LINE__);
    show_tableau_commande(commande,nb_etats);
    printf("erreur %d\n",__LINE__);
    int * erreur=tableau_erreur(prefix,nb_etats);
    printf("show erreur %d\n",__LINE__);
    show_tableau_erreur(erreur,nb_etats);
    printf("fusion %d\n",__LINE__);
    fuuuuusion(commande,erreur,nb_etats);
    printf("show fusion%d\n",__LINE__);
    show_tableau_commande(commande,nb_etats);
    printf("fin %d\n",__LINE__);
}

/**
 * \fn void search_bar_init(gpointer user_data)
 * \brief Fonction d'initialisation de la barre de recherche
 *
 * \param self gpointer objet Mydata
 * \return void
 */
void search_bar_init(gpointer user_data){
	Mydata *my = get_mydata(user_data);
	my->search_bar = gtk_search_bar_new();
	gtk_box_pack_start (GTK_BOX (my->vbox), my->search_bar, FALSE, FALSE, 0);
	my->entry = gtk_search_entry_new ();
	gtk_widget_set_hexpand (my->entry, TRUE);
	gtk_box_pack_start (GTK_BOX (my->vbox), my->entry,FALSE, FALSE, 0);
	gtk_search_bar_connect_entry (GTK_SEARCH_BAR (my->search_bar), GTK_ENTRY (my->entry));	
	g_signal_connect (my->entry, "search-changed",G_CALLBACK(on_changed_search_entry), my); 
}

/**
 * \fn void layout_init (gpointer user_data)
 * \brief Fonction d'initialisation du layout
 *
 * \param self gpointer Objet Mydata
 * \return void
 */
void layout_init (gpointer user_data){
    Mydata *my = get_mydata(user_data);
    my->vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
    my->hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_container_add (GTK_CONTAINER (my->window), my->vbox);
	my->p_text_view_scroll = gtk_scrolled_window_new (NULL, NULL);
    //Menu
    gtk_box_pack_start (GTK_BOX (my->vbox), my->menu_bar, FALSE, FALSE, 0);
    search_bar_init(my);
    gtk_box_pack_start (GTK_BOX (my->vbox), my->hbox, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (my->hbox), my->p_text_view_scroll, TRUE, TRUE, 0);
    text_view_init(my);
}
