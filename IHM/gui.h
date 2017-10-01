/**
 * \file gui.h
 * \brief Interface graphique
 * \author Gaëtan Perrot
 * \version 0.1
 * \date 23 avril 2017
 *
 * Interface graphique
 *
 */

#ifndef GUI_H
#define GUI_H

/**
 * \fn void window_init (GtkApplication* app, gpointer user_data)
 * \brief Fonction d'initialisation de la fenêtre
 *
 * \param self GtkApplication L'application, gpointer objet Mydata
 * \return void
 */
void window_init (GtkApplication* app, gpointer user_data);

/**
 * \fn void text_view_init (gpointer user_data)
 * \brief Fonction d'initialisation de la zone de texte
 *
 * \param self gpointer objet Mydata
 * \return void
 */
void text_view_init (gpointer user_data);

/**
 * \fn void text_view_color(gpointer user_data,int start, int end)
 * \brief Fonction de changement de colro d'une partie du texte
 *
 * \param self gpointer user_data,int start, int end
 * \return void
 */
void text_view_color(gpointer user_data,int start, int end);

/**
 * \fn void search_bar_init(gpointer user_data)
 * \brief Fonction d'initialisation de la barre de recherche
 *
 * \param self gpointer objet Mydata
 * \return void
 */
void search_bar_init(gpointer user_data);

/**
 * \fn void layout_init (gpointer user_data)
 * \brief Fonction d'initialisation du layout
 *
 * \param self gpointer Objet Mydata
 * \return void
 */
void layout_init (gpointer user_data);

#endif// GUI_H

