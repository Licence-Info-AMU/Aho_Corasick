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
#include "AhoCorasick.h"
#include "strings.h"
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
	tag = gtk_text_buffer_create_tag (buffer, NULL,
	   		            "foreground", "blue", NULL); 
	gtk_text_buffer_get_iter_at_offset (buffer, &startIter, start);
	gtk_text_buffer_get_iter_at_offset (buffer, &endIter, end);
	gtk_text_buffer_apply_tag (buffer, tag, &startIter, &endIter);
}

void text_view_remove_all_color(gpointer user_data,int start, int end){
	Mydata *my = get_mydata(user_data);
	GtkTextIter startIter, endIter;
	GtkTextBuffer *buffer;	
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (my->p_text_view));
	gtk_text_buffer_get_iter_at_offset (buffer, &startIter, start);
	gtk_text_buffer_get_iter_at_offset (buffer, &endIter, end);
	gtk_text_buffer_remove_all_tags (buffer,&startIter, &endIter);
}

gchar * getText_from_TextView(GtkTextView * p_text_view){
	gchar *contents = NULL;
	gchar *locale = NULL;
	GtkTextIter start;
	GtkTextIter end;
	GtkTextBuffer *p_text_buffer = NULL;

	p_text_buffer = gtk_text_view_get_buffer (p_text_view);
	gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
	contents = gtk_text_buffer_get_text (p_text_buffer, &start, &end, FALSE);
	locale = g_locale_from_utf8 (contents, -1, NULL, NULL, NULL);
	g_free (contents), contents = NULL;
	return locale;
}

//À finir !
void on_changed_search_entry (GtkSearchEntry *entry,gpointer user_data){
	Mydata *my = get_mydata(user_data);
	const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
	printf("%s\n",entry_text);
	if(strlen((char *) entry_text) > 0){
		int cpt=0;
		while(entry_text[cpt] == ' '){
			cpt++;
		}
		char * str_copy =malloc(strlen(entry_text) + 1-cpt);
		strcpy(str_copy,(char *) entry_text+cpt);
		if(strlen(str_copy) > 0){
			const char separator = ' ';
			char * text = (char*)getText_from_TextView(GTK_TEXT_VIEW(my->p_text_view));
			search_words(str_copy, separator,text);
		}	
		free(str_copy);
		str_copy=NULL;
	}
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
