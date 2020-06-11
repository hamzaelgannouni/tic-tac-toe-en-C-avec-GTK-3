#include <gtk/gtk.h>
#include "structure.h"
 GtkLabel *lible[30];
GtkWidget * meilleur_score(GtkWidget *do_widget){
   
   GtkBuilder      *builder; 
   GtkWidget       *window;
    gchar           str_img[] = "lab_0";  
 

     builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("glade/window_main_meilleur_score.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "meilleur_score"));
    
    for (gint i = 0; i < 30; i++) {
		
		if(i<=9){
			str_img[4] = i + '0';
		}else{
			if(i<=19){
				str_img[4]= '1';
				str_img[5] = (i-10) + '0';
		}
		
		else{
			str_img[4]= '2';
				str_img[5] = (i-20) + '0';
		}
	}
	lible[i] =GTK_LABEL(gtk_builder_get_object(builder, str_img));
}
   
    dix_meilleur_scors();
    
    gtk_builder_connect_signals(builder, NULL);


    g_object_unref(builder);

    g_signal_connect (window, "destroy", gtk_main_quit, NULL);
    gtk_widget_show(window);
    gtk_main();


    return window;
}
void dix_meilleur_scors(){
  int taille;
   char temp[10];
  joueur*J;
  T_scors *T;
  int i=0,j1;
  joueur j;
  J=(joueur*)malloc(sizeof(joueur)*11);
  FILE* f=fopen("projet.bin","rb");
  if(f==NULL) fprintf(stderr,"erreur d'ouverture de fichier");
  else{
      fseek(f,0,SEEK_END);
      taille=ftell(f)/sizeof(joueur);
      T=(T_scors*)malloc(100*sizeof(T_scors));
      fseek(f,0,0);
      while(!feof(f)){
        fread(&j,sizeof(joueur),1,f);
        T[i].scors=j.score;
        strcpy(T[i].username,j.username);
        i++;
      }
      trie_score(T,taille);
      fseek(f,0,0);
      i=0;
      while(!feof(f)){
        fread(&j,sizeof(joueur),1,f);
        for(i=0;i<10;i++){
          if(!feof(f) && j.score==T[i].scors && strcmp(T[i].username,j.username)==0 ){
              J[i]=j;
          }
       }
     }
  }
  
  
  if(taille>=10){
	      i=0;
	  	
		  for(j1=0;j1<10;j1++){
			  gtk_label_set_text(lible[i],(const gchar *)J[j1].nom);
		      gtk_label_set_text(lible[i+1],(const gchar *)J[j1].prenom);
		       sprintf(temp, "%d", J[j1].score);
	
		       
		       gtk_label_set_text(lible[i+2],(const gchar *) temp);
		       i=i+3;
		  }
		  
		  
 
  }else{
	  i=0;
     for(j1=0;j1<taille;j1++){
			  gtk_label_set_text(lible[i],(const gchar *)J[j1].nom);
		      gtk_label_set_text(lible[i+1],(const gchar *)J[j1].prenom);
		      sprintf(temp, "%d", J[j1].score);
		      gtk_label_set_text(lible[i+2],(const gchar *) temp);
		      i=i+3; 
		  }
  }
  
    fclose(f);
}

void trie_score(T_scors *T,int taille){
       int i,j;
       int max;
       T_scors temp;
       for(i=0;i<taille-1;i++){
           max=i;
           for(j=i+1;j<taille;j++){
                if(T[max].scors<T[j].scors)
                    max=j;
           }
           temp=T[i];
           T[i]=T[max];
           T[max]=temp;
      }
}


