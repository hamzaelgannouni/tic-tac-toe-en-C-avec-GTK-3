#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include "game_logic.h"
typedef struct joueur {
char nom[20];
char prenom[20];
char username[20];
char motdepass[20];
int score;
}joueur;

typedef struct T_scors{
    char username[20];
    int scors;
}T_scors;


typedef struct date{
    int jour;
    int mois;
    int annee;
}date;


typedef struct Match{
	joueur joueur1;
	joueur joueur2;
	struct date d;
	char gagner[50];
}Match;

typedef struct gerreur {
int espace;
int premier_lettre;
int n_u_existe;
int champ_vide;
} g_erreur;


typedef struct kapp_widget{
    GtkWidget *w_img[9];    	// Images in buttons hold blank, O or X
    GtkWidget *w_lbl_status;	// Status label
    gboolean turn;          	// Keeps track of turns - TRUE = O, FALSE = X
    gchar game_board[9];    	// Tracks game moves on board, maps board left to right, top to bottom
    game_state gm_state;    	// Game state: busy, O won, X won or tie
} app_widgets;




joueur *joueur_1;
joueur *joueur_2;

//jouer_contre_utilisateur
void modifier_Scors(joueur * j);
int nbre_match_jouer(joueur* j);
void Enregistrer_Match(joueur* j1,joueur* j2 , date d,char* Username);
date saisie_Date();

//historique
void afficher_Scors(joueur * j1,joueur *j2);
void historique_rempli(joueur *j);
GtkWidget * historique(GtkWidget *do_widget);

//meilleur_score
GtkWidget * meilleur_score(GtkWidget *do_widget);
void dix_meilleur_scors();
void trie_score(T_scors *T,int taille);

//jouer_contre_ordinateur
GtkWidget * jouer_contre_ordinateur(GtkWidget *do_widget);
int randomNumberLessThan(int n);
void initialising(GtkButton *buttonInit,int i,int j);
int hasAnyoneWon(int a[3][3]);
void setAllButtonsToBlank();
void computerMove();

//jouer_contre_utilisateur
GtkWidget * jouer_contre_utilisateur(GtkWidget *do_widget);
void on_btn_clicked(GtkButton *button, app_widgets *app_wdgts);
void on_btn_new_game_clicked(GtkButton *button,  app_widgets *app_wdgts);
void on_window_VsPC_remove();

// main
GtkWidget * inscription(GtkWidget *do_widget);
GtkWidget * connexion(GtkWidget *do_widget);
GtkWidget * connexion1(GtkWidget *do_widget);



//inscrire
gchar* nom(GtkWidget *widget, gpointer data);
gchar* prenom(GtkWidget *widget, gpointer data);
gchar* username_utilisateur(GtkWidget *widget, gpointer data);
gchar* motdepasse_utilisateur(GtkWidget *widget, gpointer data);
GtkWidget * inscription_reussite(g_erreur e) ;
GtkWidget * erreur_gtk(g_erreur e);
g_erreur test(g_erreur e);

//identification
void identifie_utilisateur(joueur utilisateur);
gchar* username_utilisateur1(GtkWidget *widget, gpointer data);
gchar* motdepasse_utilisateur1(GtkWidget *widget, gpointer data);
GtkWidget *erreur_connexion(int e_nom_u, int e_mdp );
GtkWidget* identification_reussie(GtkWidget* window, gpointer data);

int win(const int board[9]) ;
int minimax(int board[9], int player);
int computerMove1(int arr[3][3]);



