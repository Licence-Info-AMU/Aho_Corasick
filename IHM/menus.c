/**
 * \file menus.c
 * \brief Gestion des menus et évènements des menus
 * \author Gaëtan Perrot
 * \version 0.1
 * \date 23 avril 2017
 *
 * Gestion des menus et évènements des menus
 *
 */
 
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydata.h"
#include <errno.h>
#include "menus.h"

// Callbacks menus / boutons
void on_item_about_activate (GtkWidget *widget, gpointer data){
    Mydata *my = get_mydata(data);
    char *auteurs[] = {"Lucas Moragues <lucas.moragues.univ-amu.fr>","Gaëtan Perrot <gaetan.perrot@etu.univ-amu.fr>", NULL};
    gtk_show_about_dialog (NULL, "program-name", my->title, "version", 
                           "0.1", "website", "https://github.com/moonlight83340/Aho_Corasick", 
                           "authors", auteurs, "logo-icon-name", 
                           "face-wink",NULL);    
    printf ("About\n");
}

void on_item_load_activate(GtkWidget *widget, gpointer data){
	Mydata *my = get_mydata(data);
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;
    dialog = gtk_file_chooser_dialog_new ("Load Track",
                                          GTK_WINDOW(my->window),action,"Cancel",GTK_RESPONSE_CANCEL,"Open",GTK_RESPONSE_ACCEPT,NULL);
    if (my->current_folder != NULL) 
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (dialog), my->current_folder);
    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT){
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
		if(!g_file_get_contents (filename, &my->contents, NULL, NULL)){
			GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
			GtkWidget * error_dialog = gtk_message_dialog_new (GTK_WINDOW(my->window),
																flags,GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE,"Error reading “%s”",filename);
			gtk_window_set_title(GTK_WINDOW(error_dialog),"Load Track Error");
			gtk_dialog_run (GTK_DIALOG (error_dialog));
			g_signal_connect_swapped (error_dialog, "response",G_CALLBACK (gtk_widget_destroy),error_dialog);
		}else{
			gchar *utf8 = NULL;
			GtkTextBuffer *p_text_buffer = NULL;
			GtkTextIter iter;
			
			gtk_widget_set_sensitive (GTK_WIDGET (my->p_text_view), TRUE);
			p_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(my->p_text_view));
			gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
			utf8 = g_locale_to_utf8 (my->contents, -1, NULL, NULL, NULL);
			gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
			g_free (utf8), utf8 = NULL;
		}
        my->current_folder = NULL;
        my->current_folder = gtk_file_chooser_get_current_folder(chooser);    
        g_free(filename);    
    }
    gtk_widget_destroy (dialog);
}

void on_item_close_activate(GtkWidget *widget, gpointer data){
	Mydata *my = get_mydata(data);
	GtkTextIter start;
    GtkTextIter end;
    GtkTextBuffer *p_text_buffer = NULL;

    p_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(my->p_text_view));
    gtk_text_buffer_get_bounds (p_text_buffer, &start, &end);
    gtk_text_buffer_delete (p_text_buffer, &start, &end);
    
    my->contents = NULL;
    
    gtk_widget_set_sensitive (GTK_WIDGET (my->p_text_view), FALSE);
}

void on_item_quit_activate (GtkWidget *widget, gpointer data){
    Mydata *my = get_mydata(data);
    gtk_widget_destroy(my->window);
}

/**
 * \fn void menu_init (gpointer user_data)
 * \brief Fonction d'initialisation du menu
 *
 * \param self Un objet gpointer (Mydata).
 * \return void
 */
void menu_init (gpointer user_data){
	Mydata *my = get_mydata(user_data);  
    GtkWidget *item_file, *item_help, *sub_file, *item_quit, *sub_help, *item_about, *item_load, *item_close;
    my->menu_bar = gtk_menu_bar_new();    
    //Menu    
    item_file = gtk_menu_item_new_with_label ("File");
    item_help = gtk_menu_item_new_with_label ("Help");
    
    gtk_menu_shell_append(GTK_MENU_SHELL(my->menu_bar), item_file);
    gtk_menu_shell_append(GTK_MENU_SHELL(my->menu_bar), item_help);
    
    //File
    sub_file = gtk_menu_new ();
    
    item_load = gtk_menu_item_new_with_label ("Load");
    item_close = gtk_menu_item_new_with_label ("Close");
    item_quit = gtk_menu_item_new_with_label ("Quit");
           
    gtk_menu_shell_append(GTK_MENU_SHELL(sub_file), item_load);
    gtk_menu_shell_append(GTK_MENU_SHELL(sub_file), item_close);
    gtk_menu_shell_append(GTK_MENU_SHELL(sub_file), item_quit);

	g_signal_connect (item_load, "activate",G_CALLBACK(on_item_load_activate), my); 
	g_signal_connect (item_close, "activate",G_CALLBACK(on_item_close_activate), my);
    g_signal_connect (item_quit, "activate",G_CALLBACK(on_item_quit_activate), my); 
    
    //Help
    sub_help = gtk_menu_new ();
    
    item_about = gtk_menu_item_new_with_label ("About"); 
    gtk_menu_shell_append(GTK_MENU_SHELL(sub_help), item_about);
    g_signal_connect (item_about, "activate",G_CALLBACK(on_item_about_activate), my); 
    
    //Sub-menus    
    gtk_menu_item_set_submenu (GTK_MENU_ITEM(item_file), sub_file);
    gtk_menu_item_set_submenu (GTK_MENU_ITEM(item_help), sub_help);    
}


