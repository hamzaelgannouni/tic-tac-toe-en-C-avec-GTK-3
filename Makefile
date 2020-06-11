# change application name here (executable output name)
TARGET=template_app

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=    main.o inscrire.o connecter.o jouer_contre_ordinateur.o game_logic.0 jouer_contre_utilisateur.o meilleur_score.o historique.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o
    
inscrire.o: src/inscrire.c
	$(CC) -c $(CCFLAGS) src/inscrire.c $(GTKLIB) -o inscrire.o

connecter.o: src/connecter.c
	$(CC) -c $(CCFLAGS) src/connecter.c $(GTKLIB) -o connecter.o
	
jouer_contre_ordinateur.o: src/jouer_contre_ordinateur.c
	$(CC) -c $(CCFLAGS) src/jouer_contre_ordinateur.c $(GTKLIB) -o jouer_contre_ordinateur.o
		
game_logic.0: src/game_logic.c
	$(CC) -c $(CCFLAGS) src/game_logic.c $(GTKLIB) -o game_logic.0
	
jouer_contre_utilisateur.o: src/jouer_contre_utilisateur.c
	$(CC) -c $(CCFLAGS) src/jouer_contre_utilisateur.c $(GTKLIB) -o jouer_contre_utilisateur.o
	
meilleur_score.o: src/meilleur_score.c
	$(CC) -c $(CCFLAGS) src/meilleur_score.c $(GTKLIB) -o meilleur_score.o
	
historique.o: src/historique.c
	$(CC) -c $(CCFLAGS) src/historique.c $(GTKLIB) -o historique.o
	
	
clean:
	rm -f *.o $(TARGET)
