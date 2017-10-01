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

void text_view_init (gpointer user_data){
	Mydata *my = get_mydata(user_data);
	my->p_text_view = gtk_text_view_new ();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(my->p_text_view), FALSE);
	gtk_container_add (GTK_CONTAINER (my->p_text_view_scroll), my->p_text_view);
	gtk_widget_set_sensitive (GTK_WIDGET (my->p_text_view), FALSE);
}

typedef struct {
	char** tabStr;
	int size;
} Strings;

void init_Strings(Strings * strings){
	strings->size = 0;
}

void init_Strings_with_size(Strings * strings,int size){
	strings->size = size;
	strings->tabStr = malloc((strings->size) * sizeof (char *));
	if(strings->tabStr==NULL){
        perror("malloc strings->tabstr Strings");
        exit(1);
   }
}

int count_occurence_in_str(char * str,const char separator){
	int count = 0;
	for (int i=0; str[i]; i++)
		count += (str[i] == separator);	
	return count;
}

Strings convert_str_into_TabStr_by_separator(char * str,const char separator){
	char *token = NULL;
	char* str_copy = malloc(strlen(str) + 1);
	strcpy(str_copy,str);
	Strings strings;
	int i = 0;
	init_Strings_with_size(&strings,count_occurence_in_str(str,separator)+1);
	token = strtok(str_copy, &separator);
	while(token != NULL){
		size_t length = strlen(token)+1;
		strings.tabStr[i] = malloc(length* sizeof(char *));
		memcpy(strings.tabStr[i], token, length);
		printf( " %s\n", strings.tabStr[i] );
		printf( " %d\n",i);
		i++;
		token = strtok(NULL, &separator);
   }
   free(str_copy);
   return strings;
}


//À finir !
void on_changed_search_entry (GtkSearchEntry *entry,gpointer user_data){
	Mydata *my = get_mydata(user_data);
	const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
	printf("%s\n",entry_text);
	const char separator = ' ';
	Strings strings = convert_str_into_TabStr_by_separator((char *)entry_text,separator);
}

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
