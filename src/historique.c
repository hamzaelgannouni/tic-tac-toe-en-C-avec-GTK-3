#include <gtk/gtk.h>
#include "structure.h"
GtkLabel *lible[24];
GtkWidget * historique(GtkWidget *do_widget){
   
   GtkBuilder      *builder; 
   GtkWidget       *window;
    gchar           str_img[] = "label_0";  
 

     builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("glade/window_main_historique.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "historique"));
    
    for (gint i = 0; i < 24; i++) {
		if(i<=9){
			str_img[6] = i + '0';
		}else{
			if(i<=19){
				str_img[6]= '1';
				str_img[7] = (i-10) + '0';
		}
		
		else{
			str_img[6]= '2';
				str_img[7] = (i-20) + '0';
		}
	}
		
       
        lible[i] =GTK_LABEL(gtk_builder_get_object(builder, str_img));
    }
    
   historique_rempli(joueur_1);
    
    gtk_builder_connect_signals(builder, NULL);


    g_object_unref(builder);

    g_signal_connect (window, "destroy", gtk_main_quit, NULL);
    gtk_widget_show(window);
    gtk_main();


    return window;
}

void historique_rempli(joueur *j){
    Match M;
     char temp[10];
     int i=0;
    FILE* F;
    F=fopen("Match.bin","rb");
    if(F==NULL){
        printf("erreur d'ouverture");
    }
    else{
        while(!feof(F)){
            fread(&M,sizeof(struct Match),1,F);
                if((!feof(F)) && strcmp(j->username,M.joueur1.username)==0 ){
                  
                  sprintf(temp,"%d/%d/%d",M.d.jour,M.d.mois,M.d.annee);
                 
                  gtk_label_set_text(lible[i],(const gchar *)temp);
                  gtk_label_set_text(lible[i+1],(const gchar *)M.joueur2.nom);
                  if(strcmp(j->username,M.gagner)==0){
                  gtk_label_set_text(lible[i+2],"Gagner");
                  }else{
                  gtk_label_set_text(lible[i+2],"Echec");
                }
                
                
              i=i+3;  
        }
       
         if((!feof(F)) && strcmp(j->username,M.joueur2.username)==0){
                 
                  sprintf(temp,"%d/%d/%d",M.d.jour,M.d.mois,M.d.annee);
                  gtk_label_set_text(lible[i],(const gchar *) temp);
                  gtk_label_set_text(lible[i+1],(const gchar *)M.joueur1.nom);
                  if(strcmp(j->username,M.gagner)==0){
                  gtk_label_set_text(lible[i+2],"Gagner");
                  }else{
                  gtk_label_set_text(lible[i+2],"Echec");
                 
			  }
			   i=i+3;
                }
         
        }
        
        
}
fclose(F);
}


