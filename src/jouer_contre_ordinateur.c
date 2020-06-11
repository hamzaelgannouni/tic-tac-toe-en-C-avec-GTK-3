#include <gtk/gtk.h>
#include <stdlib.h>
#include "structure.h"
// declaring global variables
static GtkButton *statusClick,*diffClick,*gameClick,*quiter;
static GtkButton *button[3][3]={{NULL,NULL,NULL},{NULL,NULL,NULL},{NULL,NULL,NULL}};
static GtkButton *buttonz[3][3]={{NULL,NULL,NULL},{NULL,NULL,NULL},{NULL,NULL,NULL}};

// declaring global flags
static int flag=1, gameNotOver=1, initialise=0, statusFlag=1, pressed[3][3]={{0,0,0},{0,0,0},{0,0,0}};
static int moveCounter=0;

// declaring game parameters
static int arr[3][3]={{0,0,0},{0,0,0},{0,0,0}};
static int gameType=1, gameDifficulty=1;

// main method, start of execution
GtkWidget * jouer_contre_ordinateur(GtkWidget *do_widget){

    
    
    GtkBuilder      *builder;
    GtkWidget       *window;

// initialising GTKbuilder with .glade file
    builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("glade/window_main_vspc.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow_vspc"));

// initialising main window widget
    statusClick=GTK_BUTTON(gtk_builder_get_object(builder, "statusButton"));
    buttonz[0][0]=GTK_BUTTON(gtk_builder_get_object(builder, "button11"));
    buttonz[0][1]=GTK_BUTTON(gtk_builder_get_object(builder, "button12"));
    buttonz[0][2]=GTK_BUTTON(gtk_builder_get_object(builder, "button13"));
    buttonz[1][0]=GTK_BUTTON(gtk_builder_get_object(builder, "button21"));
    buttonz[1][1]=GTK_BUTTON(gtk_builder_get_object(builder, "button22"));
    buttonz[1][2]=GTK_BUTTON(gtk_builder_get_object(builder, "button23"));
    buttonz[2][0]=GTK_BUTTON(gtk_builder_get_object(builder, "button31"));
    buttonz[2][1]=GTK_BUTTON(gtk_builder_get_object(builder, "button32"));
    buttonz[2][2]=GTK_BUTTON(gtk_builder_get_object(builder, "button33"));
    quiter=GTK_BUTTON(gtk_builder_get_object(builder, "quitButton"));
    
    gtk_builder_connect_signals(builder, NULL);

// dereferencing builder pointer (for reuse later)
    g_object_unref(builder);
     g_signal_connect_swapped (quiter, "clicked", G_CALLBACK (gtk_widget_destroy), window);

// showing main window widget
    gtk_widget_show(window);
    gtk_main();
  
    return window;
   
}



// runs the about dialog box
void on_aboutSelection_activate()
{
  GtkWidget   *about;
  GtkBuilder  *builder;

// initialising GTKbuilder with .glade file
  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "glade/window_main_vspc.glade", NULL);

// initialising about widget
  about = GTK_WIDGET(gtk_builder_get_object(builder, "aboutDialog"));
  gtk_builder_connect_signals(builder, NULL);

// dereferencing builder for later use
  g_object_unref(builder);
  gtk_dialog_run (GTK_DIALOG (about));

// when response signal is triggered
  gtk_widget_destroy (about);
}

// when gamemode button is pressed
void on_chooseGamemodeButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
  gameClick = (GtkButton *) user_data;
  if(!statusFlag) return;
  if(flag)
  {
    gtk_button_set_label(statusClick, "RESTART TO SELECT GAMEMODE");
    return;
  }
  flag=1; //enable flag at button press, not here. reset flag to 0 in restart
  gtk_button_set_label(statusClick, "SELECT GAMEMODE");
  GtkBuilder  *builder;
  GtkWidget   *gameDialog;
// initialising GTKbuilder with .glade file
  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "glade/window_main_vspc.glade", NULL);
// initialising gamemode selection widget
  gameDialog = GTK_WIDGET(gtk_builder_get_object(builder, "chooseGamemodeDialog"));
  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);
  gtk_dialog_run (GTK_DIALOG (gameDialog));
// when window is closed from the x button in toolbar
  gtk_widget_destroy(gameDialog);
}

// runs when PvP is selected in settings menu
void on_pvpButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
  gameType = 0;
  gtk_widget_destroy((GtkWidget *) user_data);
  gtk_button_set_label(gameClick, "PvP");
}

// runs the choose difficulty pop up when PvC is selected in settings menu
void on_pvcButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
  gameType = 1;
  gtk_widget_destroy((GtkWidget *) user_data);
  gtk_button_set_label(gameClick, "PvC");
}

// when difficulty button is pressed
void on_chooseDifficultyButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
    diffClick = (GtkButton *) user_data;
    gtk_button_set_label(statusClick, "SELECT DIFFICULTY");
    GtkBuilder  *builder;
    GtkWidget   *diffDialog;
  // initialising GTKbuilder with .glade file
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main_vspc.glade", NULL);
  // initialising difficulty selection widget
    diffDialog = GTK_WIDGET(gtk_builder_get_object(builder, "chooseDifficultyDialog"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_dialog_run (GTK_DIALOG (diffDialog));
  // when window is closed from the x button in toolbar
    gtk_widget_destroy(diffDialog);
}

// runs when easy is selected in difficulty selection dialog
void on_easyButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
  gameDifficulty = 0;
  gtk_widget_destroy((GtkWidget *) user_data);
  gtk_button_set_label(diffClick, "EASY");
}

// runs when medium is selected in difficulty selection dialog
void on_mediumButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
  gameDifficulty = 1;
  gtk_widget_destroy((GtkWidget *) user_data);
  gtk_button_set_label(diffClick, "MEDIUM");
}

// runs when hard is selected in difficulty selection dialog
void on_hardButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
  gameDifficulty = 1;
  gtk_widget_destroy((GtkWidget *) user_data);
  gtk_button_set_label(diffClick, "HARD");
}

/* runs when restart is selected in settings menu. Destroys old window,
 reinitialises all global variables and runs main method */
void on_restartGame_activate(GtkWidget *click_button, gpointer   user_data)
{
  int i,j;
  
  gameDifficulty=0; gameType=1; flag=1; moveCounter=0; gameNotOver=1; initialise=0;
  for(i=0;i<3;i++)
  {
      for(j=0;j<3;j++)
      {
          button[i][j]=NULL;
          arr[i][j]=0;
          pressed[i][j]=0;
      }
  }
  setAllButtonsToBlank();
}

// runs when status button is clicked, used to pass a reference of the status button
void on_statusButton_clicked(GtkWidget *click_button, gpointer   user_data)
{
  statusClick = (GtkButton *) user_data;
  if(!flag)
    {
      gtk_button_set_label(statusClick, "SELECT GAMEMODE FROM SETTINGS");
      statusFlag=1;
    }
}

/* initialising mode is used to get a reference to all the buttons in order to change
their labels in PvC mode. This is a downside of using Glade, as the computer
can not press the button when it's its move */

// runs when button 1,1 is clicked
int on_button11_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
   buttonz[0][0]=buttonTemp;
  // runs if in initialising mode
  if(initialise!=0)
  {
    initialising(buttonTemp,0,0);
    return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[0][0]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[0][0]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[0][0]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[0][0]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[0][0]=1;
  }
  return 0;
}

// runs when button 1,2 is clicked
int on_button12_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
     buttonz[0][1]=buttonTemp;

  // runs if in initialising mode
  if(initialise!=0)
  {
    initialising(buttonTemp,0,1);
    return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[0][1]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[0][1]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[0][1]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[0][1]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[0][1]=1;
  }
  return 0;
}

// runs when button 1,3 is clicked
int on_button13_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
     buttonz[0][2]=buttonTemp;

  // runs if in initialising mode
  if(initialise!=0)
  {
    initialising(buttonTemp,0,2);
    return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[0][2]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[0][2]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[0][2]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[0][2]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[0][2]=1;
  }
  return 0;
}

// runs when button 2,1 is clicked
int on_button21_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
     buttonz[1][0]=buttonTemp;
  // runs if in initialising mode
  if(initialise!=0)
  {
    initialising(buttonTemp,1,0);
    return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[1][0]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[1][0]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[1][0]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[1][0]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[1][0]=1;
  }
  return 0;
}

// runs when button 2,2 is clicked
int on_button22_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
     buttonz[1][1]=buttonTemp;
  // runs if in initialising mode
  if(initialise!=0)
  {
    initialising(buttonTemp,1,1);
    return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[1][1]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[1][1]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[1][1]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[1][1]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[1][1]=1;
  }
  return 0;
}

// runs when button 2,3 is clicked
int on_button23_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
     buttonz[1][2]=buttonTemp;
  // runs if in initialising mode
  if(initialise!=0)
  {
    initialising(buttonTemp,1,2);
    return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[1][2]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[1][2]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[1][2]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[1][2]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[1][2]=1;
  }
  return 0;
}

// runs when button 3,1 is clicked
int on_button31_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
     buttonz[2][0]=buttonTemp;
  // runs if in initialising mode
  if(initialise!=0)
  {
    initialising(buttonTemp,2,0);
    return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[2][0]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[2][0]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[2][0]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[2][0]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[2][0]=1;
  }
  return 0;
}

// runs when button 3,2 is clicked
int on_button32_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
    buttonz[2][1]=buttonTemp;

  // runs if in initialising mode
  if(initialise!=0)
  {
      initialising(buttonTemp,2,1);
      return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[2][1]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[2][1]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[2][1]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[2][1]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[2][1]=1;
  }
  return 0;
}

// runs when button 3,3 is clicked
int on_button33_clicked(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;
      buttonz[2][2]=buttonTemp;
  // runs if in initialising mode
  if(initialise!=0)
  {
      initialising(buttonTemp,2,2);
      return 0;
  }

  // runs if button has already been pressed either while Initialising or in-game
  if(pressed[2][2]) return 0;

  // runs when button is pressed in-game
  if(flag&&gameNotOver)
  {
    // runs when the button is pressed during an odd move
    if(++moveCounter%2)
    {
      arr[2][2]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[2][2]=1;
      switch(hasAnyoneWon(arr))
      {
        case 0: if(moveCounter==9)
                {
                  gtk_button_set_label(statusClick, "égalité");
                  gameNotOver=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 2'S MOVE");
      if(gameType==1) computerMove();
    }
    // runs when the button is pressed during an even move
    else
    {
      arr[2][2]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(hasAnyoneWon(arr))
      {
        case 1: gtk_button_set_label(statusClick, "utilisateur 1 gagner");
                gameNotOver=0; return 0;
        case 2: gtk_button_set_label(statusClick, "PLAYER 2 WON");
                gameNotOver=0; return 0;
      }
      gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");
    }
    pressed[2][2]=1;
  }
  return 0;
}

/* function for checking if whether any row, column or diagonal is completely
filled by either 0, 1, or 2 and returns either 0,1 or 2 */
int hasAnyoneWon(int a[3][3])
{
  int oneWon=0; int twoWon=0; int i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(a[i][j]==1) oneWon++;
      if(a[i][j]==2) twoWon++;
    }
    if(oneWon==3) return 1;
    if(twoWon==3) return 2;
    oneWon=0; twoWon=0;
  }
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(a[j][i]==1) oneWon++;
      if(a[j][i]==2) twoWon++;
    }
    if(oneWon==3) return 1;
    if(twoWon==3) return 2;
    oneWon=0; twoWon=0;
  }
  for(i=0;i<3;i++)
  {
    if(a[i][i]==1) oneWon++;
    if(a[i][i]==2) twoWon++;
  }
  if(oneWon==3) return 1;
  if(twoWon==3) return 2;
  oneWon=0; twoWon=0;
  for(i=0,j=2;i<3;i++,j--)
  {
    if(a[i][j]==1) oneWon++;
    if(a[i][j]==2) twoWon++;
  }
  if(oneWon==3) return 1;
  if(twoWon==3) return 2;
  return 0;
}

// called after initialising mode is completed to reset buttons
void setAllButtonsToBlank()
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            gtk_button_set_label(buttonz[i][j], " ");
        }
    }
}


void computerMove()
{
  int i,j,k,l,best=0,x,y;
  int tempGame[3][3];
  int score[3][3]={{0,0,0},{0,0,0},{0,0,0}};
  moveCounter++;

  // coping game into a temporary array, to be used for checking if someone is about to win
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      tempGame[i][j]=arr[i][j];
    }
  }

  // running through all 9 buttons
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {

      // if a move has already been played in the button
      if(pressed[i][j]) continue;

      // adds score for column and row
      for(k=0;k<3;k++)
      {
        if(arr[i][k]==0) score[i][j]++;
        if(arr[k][j]==0) score[i][j]++;
      }

      // adds score for primary diagonal
      if((i==0&&j==0)||(i==2&&j==2)||(i==1&&j==1))
      {
        for(k=0;k<3;k++)
          if(arr[k][k]==0) score[i][j]++;
      }

      // adds score for secondary diagonal
      if((i==0&&j==2)||(i==2&&j==0)||(i==1&&j==1))
      {
        for(k=0,l=2;k<3;k++,l--)
          if(arr[k][l]==0) score[i][j]++;
      }

      // checks if playing the button causes player 1 to win
      tempGame[i][j]=1;
      if(hasAnyoneWon(tempGame)==1) score[i][j]+=100;

      // checks if playing the button causes computer to win
      tempGame[i][j]=2;
      if(hasAnyoneWon(tempGame)==2) score[i][j]+=200;

      // resets the temporary game array
      tempGame[i][j]=0;
    }
  }

  // adjusting scores for certain edge cases to prevent player 1 from assured victory
  if(moveCounter==4)
  {
    if((arr[0][0]==1&&arr[2][2]==1)||(arr[0][2]==1&&arr[2][0]==1))
    score[1][0]=300;
    if((arr[0][1]==1&&arr[1][0]==1)||(arr[1][0]==1&&arr[0][2]==1)||(arr[0][1]==1&&arr[2][0]==1))
    score[0][0]=300;
    if((arr[0][1]==1&&arr[1][2]==1)||(arr[0][1]==1&&arr[2][2]==1)||(arr[1][2]==1&&arr[0][0]==1))
    score[0][2]=300;
    if((arr[1][2]==1&&arr[2][1]==1)||(arr[1][2]==1&&arr[2][0]==1)||(arr[2][1]==1&&arr[0][2]==1))
    score[2][2]=300;
    if((arr[2][1]==1&&arr[1][0]==1)||(arr[2][1]==1&&arr[0][0]==1)||(arr[1][0]==1&&arr[2][2]==1))
    score[2][0]=300;
  }

  // finds the highest scored button
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(score[i][j]>best)
      {
        best=score[i][j]; x=i; y=j;
      }
    }
  }
  
  

    // alters the highest scored move to be played if a random number matches criteria, lower chance
    if(gameDifficulty==1)
    {
		
        
		    do
		    {
				   int place =computerMove1(arr);
		if(place==0){
			x=0;
			y=0;
		}
		if(place==1){
			x=0;
			y=1;
		}
		if(place==2){
			x=0;
			y=2;
		}
		if(place==3){
			x=1;
			y=0;
		}
		if(place==4){
			x=1;
			y=1;
		}
		if(place==5){
			x=1;
			y=2;
		}
		if(place==6){
			x=2;
			y=0;
		}
		if(place==7){
			x=2;
			y=1;
		}
		if(place==8){
			x=2;
			y=2;
		}
		    	g_print("x=%d,y=%d",x,y);
		    }
		    while(pressed[x][y]);
	    
    }

    // alters the highest scored move to be played if a random number matches criteria, higher chance
    if(gameDifficulty==0)
    {
		if(randomNumberLessThan(10)<7)
		{
			do
			{
				x=randomNumberLessThan(3); y=randomNumberLessThan(3);
			}
			while(pressed[x][y]);
		}
	}
	


	

  // plays the chosen button
  arr[x][y]=2;
  pressed[x][y]=1;
  button[x][y]=buttonz[x][y];

  gtk_button_set_label(button[x][y], "O");
  gtk_button_set_label(statusClick, "PLAYER 1'S MOVE");

  // checks to see if anyone won
  switch(hasAnyoneWon(arr))
  {
    case 1: gtk_button_set_label(statusClick, "Utilisateur 1 Gagne");
            gameNotOver=0;
            break;
    case 2: gtk_button_set_label(statusClick, "L'ordinateur  Gagne");
            gameNotOver=0;
            break;
  }
}

// runs for the first time each button is pressed
void initialising(GtkButton *buttonInit,int i,int j)
{
    if(button[i][j]!=NULL) return;
    
    button[i][j]=buttonInit;
    gtk_button_set_label(button[i][j], "OK");
    if(++initialise==10)
    {
      initialise=0;
      gtk_button_set_label(statusClick, "Utilisateur 1'S MOVE");
      setAllButtonsToBlank();
    }
}


int randomNumberLessThan(int n)
{
    return (double)rand()*n/RAND_MAX;
}

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}
//https://gist.github.com/MatthewSteel/3158579
 int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?

	
    int winner = win(board);
    if(winner != 0) return winner*player;
    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

int computerMove1(int arr[3][3]) {
    int move = -1;
    int score = -2;
    int i,k=0,j;
    int board[9];
    
    for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(arr[i][j]==2)board[k]=1;
			if(arr[i][j]==1)board[k]=-1;
			if(arr[i][j]==0)board[k]=0;
			k++;
		}
	}
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    
   
    //returns a score based on minimax tree at a given node.
    return move;
}
