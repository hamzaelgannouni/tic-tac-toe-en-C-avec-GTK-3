#include <gtk/gtk.h>
#include "structure.h"

GtkWidget *pointeur_sur_inscrire;
GtkWidget *pointeur_sur_connecter;
GtkBuilder      *builder; 
GtkWidget       *window;
int main(int argc, char *argv[])
{
	GtkWidget *window = NULL;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    pointeur_sur_inscrire= GTK_WIDGET(gtk_builder_get_object(builder, "inscrire"));
    pointeur_sur_connecter= GTK_WIDGET(gtk_builder_get_object(builder, "connecter"));
    
    
     g_signal_connect (G_OBJECT (pointeur_sur_inscrire), "clicked", G_CALLBACK (inscription) ,(gpointer) window);
     g_signal_connect (G_OBJECT (pointeur_sur_connecter), "clicked", G_CALLBACK (connexion), (gpointer) window);

    g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

void on_window_main_destroy()
{
    gtk_main_quit();
}
