#include "structure.h"
#include <gtk/gtk.h>

GtkWidget *window;
gpointer  data;
GtkBuilder      *builder; 
gpointer data;
int test1;
GtkWidget *pointeur_sur_valider;
GtkWidget *pointeur_sur_motdepass;
GtkWidget *pointeur_sur_username;
GtkWidget *pointeur_sur_Annuler;
joueur utilisateur1;
static GtkWidget *window1= NULL;
GtkWidget * connexion(GtkWidget *do_widget){
	
	static GtkWidget *window = NULL;
	
	if (!window)
    { 
    builder = gtk_builder_new_from_file("glade/window_main_connecter.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_connecter"));
    pointeur_sur_valider= GTK_WIDGET(gtk_builder_get_object(builder, "valider1"));
    pointeur_sur_motdepass=GTK_WIDGET(gtk_builder_get_object(builder, "motdepass"));
    pointeur_sur_username=GTK_WIDGET(gtk_builder_get_object(builder, "username"));
    pointeur_sur_Annuler=GTK_WIDGET(gtk_builder_get_object(builder, "annuler1"));
    

    gtk_builder_connect_signals(builder, NULL);

    g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(username_utilisateur1),(gpointer) pointeur_sur_username);
    g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(motdepasse_utilisateur1),(gpointer) pointeur_sur_motdepass);
    g_signal_connect_swapped (pointeur_sur_Annuler, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    
   
    g_signal_connect (window, "destroy", gtk_main_quit, NULL);
    gtk_widget_show(window);
    gtk_main();
    }
    
    
     g_signal_connect (window, "destroy", gtk_main_quit, NULL);
    
   return window;
}

GtkWidget * connexion1(GtkWidget *do_widget){
	
	
	
	if (!window1)
    { 
    builder = gtk_builder_new_from_file("glade/window_main_connecter.glade");
    window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_connecter"));
    pointeur_sur_valider= GTK_WIDGET(gtk_builder_get_object(builder, "valider1"));
    pointeur_sur_motdepass=GTK_WIDGET(gtk_builder_get_object(builder, "motdepass"));
    pointeur_sur_username=GTK_WIDGET(gtk_builder_get_object(builder, "username"));
    pointeur_sur_Annuler=GTK_WIDGET(gtk_builder_get_object(builder, "annuler1"));
    

    gtk_builder_connect_signals(builder, NULL);

    g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(username_utilisateur1),(gpointer) pointeur_sur_username);
    g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(motdepasse_utilisateur1),(gpointer) pointeur_sur_motdepass);
    g_signal_connect_swapped (pointeur_sur_Annuler, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    
   
      // g_signal_connect (window, "destroy", gtk_main_quit, NULL);
    gtk_widget_show(window1);
    gtk_main();
    
    
    }
     //  g_signal_connect (window, "destroy", gtk_main_quit, NULL);
    
   return window1;
}
gchar* username_utilisateur1(GtkWidget *widget, gpointer data){
        
        g_stpcpy(utilisateur1.username,gtk_entry_get_text(GTK_ENTRY(data)));
        
         

return utilisateur1.username;
}

gchar* motdepasse_utilisateur1(GtkWidget *widget, gpointer data){

        g_stpcpy(utilisateur1.motdepass,gtk_entry_get_text(GTK_ENTRY(data)));
      
         
         identifie_utilisateur(utilisateur1);

      return utilisateur1.motdepass;
}

void identifie_utilisateur(joueur utilisateur2) {
FILE* f;
joueur* users;
int flag1=0,flag2=0 ;
users=malloc(sizeof(joueur));
f=fopen("projet.bin","rb");
if(f!=NULL) {
    while(!feof(f)) {
        fread(users,sizeof(joueur),1,f);
        if(!feof(f)) {
            if(g_strcmp0(utilisateur2.username,users->username)==0) {
                flag1=1;
                if(g_strcmp0(utilisateur2.motdepass,users->motdepass)==0) {
                flag2=1;
                break;
                }
            }
        }else{  
			
		}
    }
    fclose(f);

}


if(flag1==0 || flag2==0){
        erreur_connexion(flag1,flag2);
}else
{
	   
	        if(joueur_1==NULL){
			gtk_widget_destroy(connexion(window));
				
			 joueur_1=(joueur*)malloc(sizeof(joueur));
			 strcpy( joueur_1->motdepass,users->motdepass);
			 strcpy( joueur_1->nom,users->nom);
			 strcpy( joueur_1->prenom,users->prenom);
			 strcpy( joueur_1->username,users->username);
			 joueur_1->score=0;
			 test1=0;
			  identification_reussie(window,data);  
			}else{
		       gtk_widget_destroy(window1);
		       window1=NULL;
				
			 joueur_2=(joueur*)malloc(sizeof(joueur));
			 strcpy( joueur_2->motdepass,users->motdepass);
			 strcpy( joueur_2->nom,users->nom);
			 strcpy( joueur_2->prenom,users->prenom);
			 strcpy( joueur_2->username,users->username);
			 joueur_2->score=0;
			 test1=1;
		     jouer_contre_utilisateur(window);
			}
    
       
}


}

GtkWidget *erreur_connexion(int e_nom_u, int e_mdp ) {
    GtkWidget *button = NULL;
    GtkWidget *window = NULL;
    GtkWidget *main_vbox;
    GtkWidget *label;
    GtkWidget *vbox;
    GtkWidget *image;
    GtkWidget *frame_vert;

 /* Create the main window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Définition de la fenêtre
  gtk_window_set_title(GTK_WINDOW(window), "ERREUR"); // Titre de la fenêtre
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_widget_realize (window);
  g_signal_connect (window, "destroy", gtk_main_quit, NULL);
   


    main_vbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_container_add (GTK_CONTAINER (window), main_vbox);

    image = gtk_image_new_from_file ("Data/erreur.png");
    gtk_box_pack_start(GTK_BOX(main_vbox), image, 1, 1, 0);

    frame_vert = gtk_frame_new ("");
  /* Create a vertical box with buttons */
    gtk_box_pack_start (GTK_BOX (main_vbox), frame_vert, TRUE, TRUE, 5);


    vbox = gtk_box_new (TRUE, 8);
    gtk_container_add (GTK_CONTAINER (frame_vert), vbox);


   if (e_nom_u==0) {

              label=gtk_label_new("<span face=\"Verdana\" foreground=\"#ff0000\" size=\"x-large\">\n<b>ERREUR POUR LE JOUEUR 1 !!!</b></span>\n\n<b> Ce nom d'utilisateur n'est associe a aucun compte </b>");
              gtk_label_set_use_markup(GTK_LABEL(label), TRUE); // On dit que l'on utilise les balises pango
              gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER); // On centre notre texte
              gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

            button = gtk_button_new_from_stock ("Retour");
            g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
            gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 30);
    }

    else if(e_mdp==0) {

              label=gtk_label_new("<span face=\"Verdana\" foreground=\"#ff0000\" size=\"xx-large\">\n<b>Reessayer !!!</b></span>\n\nLe mot de passe du <b>JOUEUR 1</b> est <b>INCORRECTE</b> ");
              gtk_label_set_use_markup(GTK_LABEL(label), TRUE); // On dit que l'on utilise les balises pango
              gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER); // On centre notre texte
              gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

            button = gtk_button_new_from_stock ("Retour");
            g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
            gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 30);
    }

    gtk_widget_show_all (window);
    gtk_main();

    return window;

}

GtkWidget* identification_reussie(GtkWidget* do_widget, gpointer data) {
    GtkWidget* pointeur_sur_pc;
    GtkWidget* pointeur_sur_utili;
    GtkWidget* pointeur_sur_historique;
    GtkWidget* pointeur_sur_ms;
    GtkWidget* pointeur_sur_quitter;

 if (!window)
  {
    builder = gtk_builder_new_from_file("glade/window_main_menu.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_menu"));
    pointeur_sur_pc= GTK_WIDGET(gtk_builder_get_object(builder, "pc"));
    pointeur_sur_utili=GTK_WIDGET(gtk_builder_get_object(builder, "utili"));
    pointeur_sur_historique=GTK_WIDGET(gtk_builder_get_object(builder, "historique"));
    pointeur_sur_ms=GTK_WIDGET(gtk_builder_get_object(builder, "ms"));
    pointeur_sur_quitter=GTK_WIDGET(gtk_builder_get_object(builder, "quitter"));

    gtk_builder_connect_signals(builder, NULL);

     
    g_signal_connect (G_OBJECT (pointeur_sur_utili), "clicked", G_CALLBACK(connexion1),(gpointer) window);	
	g_signal_connect (G_OBJECT (pointeur_sur_pc), "clicked", G_CALLBACK(jouer_contre_ordinateur),(gpointer) window);
     g_signal_connect (G_OBJECT (pointeur_sur_ms), "clicked", G_CALLBACK(meilleur_score),(gpointer) window);
    g_signal_connect (G_OBJECT (pointeur_sur_historique), "clicked", G_CALLBACK(historique),(gpointer) window);
    g_signal_connect_swapped (pointeur_sur_quitter, "clicked", G_CALLBACK (gtk_widget_destroy), window); 
    
    
    g_signal_connect (window, "destroy",G_CALLBACK (gtk_widget_destroyed),&window);
    gtk_widget_show(window);
    gtk_main();
  
  

  }


  gtk_widget_show_all (window);

  return window;
}


