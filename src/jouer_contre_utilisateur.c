#include <gtk/gtk.h>
#include "game_logic.h"
#include "structure.h"




GtkLabel *lable1;
GtkLabel *lable2;
GtkLabel *lable3;
GtkLabel *lable4;
  GtkBuilder      *builder; 
   GtkWidget       *window;
GtkWidget * jouer_contre_utilisateur(GtkWidget *do_widget){
 
    app_widgets     *widgets = g_slice_new(app_widgets);
    gchar           str_img[] = "img_0";    
    char temp[5];
    int nbmatchj1=0,nbmatchj2=0;

   
    widgets->turn = TRUE;       			
    widgets->gm_state = GM_BUSY;			

 
    
    builder = gtk_builder_new_from_file("glade/window_main_VsPC.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_VsPC"));
       
   
    for (gint i = 0; i < 9; i++) {
        str_img[4] = i + '0';
        widgets->w_img[i] = GTK_WIDGET(gtk_builder_get_object(builder, str_img));
        
        widgets->game_board[i] = 0;
    }
     
    
 
   lable1=GTK_LABEL(gtk_builder_get_object(builder, "ng1"));
   lable2=GTK_LABEL(gtk_builder_get_object(builder, "ng2"));
    widgets->w_lbl_status = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_status"));
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "Nomjouer2")),(const gchar *)joueur_1->nom);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "Nomjouer1")),(const gchar *)joueur_2->nom);
     sprintf(temp, "%d", joueur_1->score);
    gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "ng1")),(const gchar *)temp);
     sprintf(temp, "%d", joueur_2->score);   
     gtk_label_set_text(GTK_LABEL(gtk_builder_get_object(builder, "ng2")),(const gchar *)temp);
     
       nbmatchj1=nbre_match_jouer(joueur_1);
     nbmatchj2=nbre_match_jouer(joueur_2);
    
     sprintf(temp, "%d",nbmatchj1);
      lable3=GTK_LABEL(gtk_builder_get_object(builder, "mj1"));
    gtk_label_set_text(lable3,(const gchar *)temp);
   
     sprintf(temp, "%d",nbmatchj2);
     lable4=GTK_LABEL(gtk_builder_get_object(builder, "mj2"));
    gtk_label_set_text(lable4,(const gchar *)temp);
       afficher_Scors(joueur_1,joueur_2);

    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);
    g_signal_connect (window, "destroy", gtk_main_quit, NULL); 
    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return window;
}


void on_btn_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    gint btn_num;       			
    gint winning_blocks[3] = {0};	
    
    if (app_wdgts->gm_state != GM_BUSY) {
        
        return;
    }
    

    btn_num = gtk_widget_get_name(GTK_WIDGET(button))[0] - '0';
    
   
    if (app_wdgts->game_board[btn_num] == 0) {
       
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img[btn_num]), app_wdgts->turn ? "Data/o.png" : "Data/x.png");
       
        app_wdgts->game_board[btn_num] = app_wdgts->turn ? 'o' : 'x';
        
        
        app_wdgts->gm_state = get_game_state(app_wdgts->game_board, winning_blocks);
        
        
        if (app_wdgts->gm_state == GM_O_WON) {
            for (int i = 0; i < 3; i++) {
                gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img[winning_blocks[i]]), "Data/o_win.png");
            }
            gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_status), "Joueur 1 (0) gagne!");
               modifier_Scors(joueur_1);
              Enregistrer_Match(joueur_1,joueur_2,saisie_Date(),joueur_1->username);
            
        }
        
        else if (app_wdgts->gm_state == GM_X_WON) {
            for (int i = 0; i < 3; i++) {
                gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img[winning_blocks[i]]), "Data/x_win.png");
            }
            gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_status), "Joueur 2 (X) gagne!");
               modifier_Scors(joueur_2);
               Enregistrer_Match(joueur_1,joueur_2,saisie_Date(),joueur_2->username);
                    }
        
        else if (app_wdgts->gm_state == GM_TIE) {
			gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_status), "égalité !");
			  Enregistrer_Match(joueur_1,joueur_2,saisie_Date(),"égalité");
		}
        
     
        app_wdgts->turn = !app_wdgts->turn;
    }
}


void on_btn_new_game_clicked(GtkButton *button,  app_widgets *app_wdgts)
{   int nbmatchj1=0,nbmatchj2=0;
	char temp[5];
	
	for (int i = 0; i < 9; i++) {
		app_wdgts->game_board[i] = 0;
	}
	
	for (int i = 0; i < 9; i++) {
		gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img[i]), "Data/blank.png");
	}
	
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_status), "Joueur 1 --> O ET Joueur 2--> X");
	
	
    app_wdgts->gm_state = GM_BUSY;
   
    nbmatchj1=nbre_match_jouer(joueur_1);
   nbmatchj2=nbre_match_jouer(joueur_2);
     sprintf(temp, "%d",nbmatchj1);
    gtk_label_set_text(lable3,(const gchar *)temp);
    
     sprintf(temp, "%d",nbmatchj2);
    gtk_label_set_text(lable4,(const gchar *)temp);
    afficher_Scors(joueur_1,joueur_2);
}
void modifier_Scors(joueur * j){int check;
    joueur j1;
    
    joueur modifier_j1;
    FILE* f=fopen("projet.bin","rb");
    FILE* f1=fopen("Joueur_Scors.bin","ab");
    if(f==NULL ||f1==NULL) printf("erreur d'ouverture");
    else{check=0;
    while(!feof(f) && check==0){
    fread(&j1,sizeof(joueur),1,f);
    if(strcmp(j1.username,j->username)==0 && strcmp(j1.motdepass,j->motdepass)==0){
        check=1 ;strcpy(modifier_j1.nom,j1.nom);
        strcpy(modifier_j1.prenom,j1.prenom);
        strcpy(modifier_j1.username,j1.username);
        strcpy(modifier_j1.motdepass,j1.motdepass);
        modifier_j1.score=++j1.score;
    }
    else
    if(!feof(f)){fwrite(&j1,sizeof(joueur),1,f1); }
    }
    fwrite(&modifier_j1,sizeof(joueur),1,f1);
    while(!feof(f)){
    fread(&j1,sizeof(joueur),1,f);
    if(!feof(f)){fwrite(&j1,sizeof(joueur),1,f1); }
    }

        }
       
        fclose(f);
        fclose(f1);
        
        remove("projet.bin");
        rename("Joueur_Scors.bin","projet.bin");
}
void afficher_Scors(joueur *j1,joueur *j2){
	joueur j;
	  char temp[5];
FILE* f=fopen("projet.bin","rb");
if(f==NULL) fprintf(stderr,"erreur d'ouverture de fichier");
else{
    while(!feof(f)){
        fread(&j,sizeof(joueur),1,f);
        if(!feof(f)){
	 if(strcmp(j1->username,j.username)==0 && strcmp(j1->motdepass,j.motdepass)==0){
    sprintf(temp, "%d", j.score);
    gtk_label_set_text(lable1,temp);}
    
     if(strcmp(j2->username,j.username)==0 && strcmp(j2->motdepass,j.motdepass)==0){
    sprintf(temp, "%d", j.score);
    gtk_label_set_text(lable2,temp);
        
    }
			
			
      
        }

    }

}
fclose(f);
}

date saisie_Date(){
    date d;
    time_t t;
    time(&t);
    struct tm *mytime=localtime(&t);
    d.jour=mytime->tm_mday;
    d.mois=mytime->tm_mon+1;
    d.annee=mytime->tm_year+1900;
return d;
}

void Enregistrer_Match(joueur* j1,joueur* j2 , date d,char* Username){
    Match m;
      strcpy(m.joueur1.prenom,j1->prenom);
      strcpy(m.joueur1.nom,j1->nom);
      strcpy(m.joueur1.username,j1->username);
      m.joueur1.score=j1->score;
   
      strcpy(m.joueur2.prenom,j2->prenom);
      strcpy(m.joueur2.nom,j2->nom);
      strcpy(m.joueur2.username,j2->username);
      m.joueur2.score=j2->score;
    m.d=d;
    strcpy(m.gagner,Username);
    FILE* f=fopen("Match.bin","ab");
    if(f==NULL)
        fprintf(stderr,"erreur d'ouverture de fichier");
    else{
        fwrite(&m,sizeof(Match),1,f);
    }
    fclose(f);
}

int nbre_match_jouer(joueur* j){
Match m;
int compteur=0;
FILE* f=fopen("Match.bin","rb");
    if(f==NULL)
        fprintf(stderr,"erreur d'ouverture de fichier");
    else{
        while(!feof(f)){
            fread(&m,sizeof(Match),1,f);
            if((!feof(f) && strcmp(m.joueur1.username,j->username)==0)||(!feof(f) && strcmp(m.joueur2.username,j->username)==0)){
                ++compteur;
            }
    }

    }
    fclose(f);
    return compteur;
}




void on_window_VsPC_remove()
{
	
	 
    gtk_main_quit();
}
