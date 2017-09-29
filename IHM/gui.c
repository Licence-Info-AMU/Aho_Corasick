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
    gtk_box_pack_start (GTK_BOX (my->vbox), my->hbox, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (my->hbox), my->p_text_view_scroll, TRUE, TRUE, 0);
    text_view_init(my);
}
