#include <gtk/gtk.h>
#include "structure.h"
GtkBuilder      *builder; 
static GtkWidget       *window=NULL;
gpointer data;
GtkButton *pointeur_sur_annuler;
GtkWidget *pointeur_sur_valider;
GtkWidget *pointeur_sur_nom;
GtkWidget *pointeur_sur_prenom;
GtkWidget *pointeur_sur_motdepass;
GtkWidget *pointeur_sur_username;

joueur utilisateur;


GtkWidget * inscription(GtkWidget *do_widget){
    builder = gtk_builder_new_from_file("glade/window_main_inscrire.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main_inscrire"));
    pointeur_sur_valider= GTK_WIDGET(gtk_builder_get_object(builder, "valider"));
    pointeur_sur_nom= GTK_WIDGET(gtk_builder_get_object(builder, "nom"));
    pointeur_sur_prenom= GTK_WIDGET(gtk_builder_get_object(builder, "prenom"));
    pointeur_sur_motdepass=GTK_WIDGET(gtk_builder_get_object(builder, "motdepass"));
    pointeur_sur_username=GTK_WIDGET(gtk_builder_get_object(builder, "username"));
    pointeur_sur_annuler=GTK_WIDGET(gtk_builder_get_object(builder, "annuler"));

    gtk_builder_connect_signals(builder, NULL);
      
    g_signal_connect (window, "destroy", gtk_main_quit, NULL); 
    
   
    
    g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(nom),(gpointer) pointeur_sur_nom);
    g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(prenom),(gpointer) pointeur_sur_prenom);
    g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(motdepasse_utilisateur),(gpointer) pointeur_sur_motdepass);
     g_signal_connect (G_OBJECT (pointeur_sur_valider), "clicked", G_CALLBACK(username_utilisateur),(gpointer) pointeur_sur_username);
    g_signal_connect_swapped (pointeur_sur_annuler, "clicked", G_CALLBACK (gtk_widget_destroy), window);
   

    gtk_widget_show(window);
    gtk_main();
   return window;
}
void onon_annuler_remove()
{
    gtk_main_quit();
}

gchar* nom(GtkWidget *widget, gpointer data)
{          
	    
        g_stpcpy(utilisateur.nom,gtk_entry_get_text(GTK_ENTRY(data)));

       g_print("nom=%s\n", utilisateur.nom);

      return utilisateur.nom;
}


gchar* prenom(GtkWidget *widget, gpointer data)
{
       
        g_stpcpy(utilisateur.prenom,gtk_entry_get_text(GTK_ENTRY(data)));

        g_print("prenom=%s\n", utilisateur.prenom);

      return utilisateur.prenom;
}


gchar* username_utilisateur(GtkWidget *widget, gpointer data){
         g_erreur e;
       
        g_stpcpy(utilisateur.username,gtk_entry_get_text(GTK_ENTRY(data)));
        test(e);
      return utilisateur.username;
}



gchar* motdepasse_utilisateur(GtkWidget *widget, gpointer data){
       
        g_stpcpy(utilisateur.motdepass,gtk_entry_get_text(GTK_ENTRY(data)));

         g_print("mdp=%s\n", utilisateur.motdepass);


      return utilisateur.motdepass;
}


g_erreur test(g_erreur e){
	
int i=0;
FILE* f;
joueur* ptr;
e.n_u_existe=0;
e.espace=0;
e.premier_lettre=0;
e.champ_vide=0;





//test sur username
if((utilisateur.username[0]<'A' || utilisateur.username[0]>'Z') &&(utilisateur.username[0]<'a' || utilisateur.username[0]>'z'))
   e.premier_lettre=1;
   //test sur username
if((utilisateur.nom[0]<'A' || utilisateur.nom[0]>'Z') &&(utilisateur.nom[0]<'a' || utilisateur.nom[0]>'z'))
   e.premier_lettre=1;
if((utilisateur.prenom[0]<'A' || utilisateur.prenom[0]>'Z') &&(utilisateur.prenom[0]<'a' || utilisateur.prenom[0]>'z'))
   e.premier_lettre=1;

while(i<15) {
    if(utilisateur.username[i]==' ') {
        e.espace=1;
    }
   i++;
}
//fin


ptr=malloc(sizeof(joueur));
f=fopen("projet.bin","rb");
if(f!=NULL) {
    while(!feof(f)) {
        //printf("flag=%d\n",e.n_u_existe);printf("i=%d\n",i);
        fread(ptr,sizeof(joueur),1,f);
        if(!feof(f))
        {
        //printf("ptr=%s\n",ptr[i].nom_u);printf("util=%s\n",username);
            if(g_strcmp0(utilisateur.username,ptr->username)==0) {
                e.n_u_existe=1;
                break;
           }
        }
    }
fclose(f);}
free(ptr);

//fin

//chi champ 5awi
if(g_strcmp0(utilisateur.motdepass,"")== 0|| g_strcmp0(utilisateur.nom,"")==0 || g_strcmp0(utilisateur.prenom,"")==0 || g_strcmp0(utilisateur.username,"")==0  ) {
        e.champ_vide=1;
}
   
if(e.premier_lettre==1 || e.espace==1 || e.n_u_existe==1 || e.champ_vide==1)
           erreur_gtk(e);
else{
            inscription_reussite(e);
            gtk_widget_destroy(window);
}
return e;

}




GtkWidget *erreur_gtk(g_erreur e) {
    GtkWidget *button = NULL;
    GtkWidget *window = NULL;
    GtkWidget *main_vbox;
    GtkWidget *label;
    GtkWidget *vbox;
    GtkWidget *image;
    GtkWidget *frame_vert;


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
  gtk_window_set_title(GTK_WINDOW(window), "ERREUR"); //
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_widget_realize (window);
  g_signal_connect (window, "destroy", gtk_main_quit, NULL);


  

    main_vbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_container_add (GTK_CONTAINER (window), main_vbox);

    image = gtk_image_new_from_file ("Data/erreur.png");
    gtk_box_pack_start(GTK_BOX(main_vbox), image, 1, 1, 0);

    frame_vert = gtk_frame_new ("Message d'erreur");
    gtk_box_pack_start (GTK_BOX (main_vbox), frame_vert, TRUE, TRUE, 20);


    vbox = gtk_box_new (TRUE, 8);
    gtk_container_add (GTK_CONTAINER (frame_vert), vbox);

    if (e.champ_vide==1) {
              label=gtk_label_new("<span face=\"Verdana\" foreground=\"#ff0000\" size=\"xx-large\"><b>ERREUR !!!</b></span>\n\n<b> Vous devez remplissez tous les champs </b>");
              gtk_label_set_use_markup(GTK_LABEL(label), TRUE); 
              gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER); 
              gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

    }

    else if(e.premier_lettre==1) {

              label=gtk_label_new("<span face=\"Verdana\" foreground=\"#ff0000\" size=\"xx-large\"><b>ERREUR !!!</b></span>\n\nLe premier caractere du nom ou prenom ou de nom d'utilisateur o\n doit etre une <b>LETTRE</b>\n\n Saisir un autre nom d'utilisateur ");
              gtk_label_set_use_markup(GTK_LABEL(label), TRUE); 
              gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER); 
              gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);


    }

    else if(e.espace==1) {
            label=gtk_label_new("<span face=\"Verdana\" foreground=\"#ff0000\" size=\"xx-large\"><b>ERREUR !!!</b></span>\n\nLe nom d'utilisateur\n ne doit pas contenir <b>DES ESPACES</b>\n\n Saisir un autre nom d'utilisateur ");
            gtk_label_set_use_markup(GTK_LABEL(label), TRUE); 
            gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER); 
            gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
    }

    else {
            label=gtk_label_new("<span face=\"Verdana\" foreground=\"#ff0000\" size=\"xx-large\"><b>ERREUR !!!</b></span>\n\n<b>EXISTE DEJA</b>\n\n Saisir un autre nom d'utilisateur ");
            gtk_label_set_use_markup(GTK_LABEL(label), TRUE); 
            gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER); 
            gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

    }

            button = gtk_button_new_with_label ("Retour");
            g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
            gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 30);

    gtk_widget_show_all (window);
    gtk_main();

    return window;

}

GtkWidget * inscription_reussite(g_erreur e) {
    GtkWidget *button = NULL;
    GtkWidget *window = NULL;
    GtkWidget *main_vbox;
    GtkWidget *label;
    GtkWidget *vbox;
    GtkWidget *image;
    GtkWidget *frame_vert;
    FILE* f;

 
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
  gtk_window_set_title(GTK_WINDOW(window), "INSCRIPTION REUSSIE"); 
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_widget_realize (window);
  g_signal_connect (window, "destroy", gtk_main_quit, NULL);


  

    main_vbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_container_add (GTK_CONTAINER (window), main_vbox);

    image = gtk_image_new_from_file ("Data/reussite.png");
    gtk_box_pack_start(GTK_BOX(main_vbox), image, 1, 1, 0);

    frame_vert = gtk_frame_new ("");
    gtk_box_pack_start (GTK_BOX (main_vbox), frame_vert, TRUE, TRUE, 20);


    vbox = gtk_box_new (TRUE, 8);
    gtk_container_add (GTK_CONTAINER (frame_vert), vbox);
utilisateur.score=0;
     
    f=fopen("projet.bin","ab");
        if(f!=NULL){
	
            fwrite(&utilisateur,sizeof(joueur),1,f);
		}
    fclose(f);

    label=gtk_label_new("\n<b>INSCRIPTION REUSSIE</b> ");
    gtk_label_set_use_markup(GTK_LABEL(label), TRUE); 
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);

    button = gtk_button_new_with_label ("OK");
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 30);

    gtk_widget_show_all (window);
    gtk_main();

 return window;
}


