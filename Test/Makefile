# Makefile kitc-phelma / projet-type
# Auteurs : Felix Piedallu, Patrick Kocelniak
# Derniere modification : 22/01/2016
# Utilisation :
# make : recompile si un des fichiers a ete modifie et contruit l'executable
# make clean : supprime les fichiers objets de compilation *.o
# make cleanall : supprime les fichiers objets *.o et le fichier executable projet-type

# Compilateur
CC=g++ -fPIC
# Activation du mode debug (-g) :
CFLAGS=-g
# Edition de liens avec les librairies C
LDFLAGS=$(shell fltk-config --use-gl --use-images --ldflags )

PFMOD=fmodlinux64
LIBFMOD=libfmodex64.so

# includes fltk et fmod
PREOPTIONS=$(shell fltk-config --use-gl --use-images --cxxflags) -I. -I$(PFMOD)
# librairies fltk et fmod
POSTOPTIONS=$(shell fltk-config --use-gl --use-images --ldstaticflags) $(PFMOD)/api/lib/$(LIBFMOD)

# Fichier executable
EXEC=slicer
#SRCALL=main.cpp main.h u1-interface.cpp u1-interface.h u2-dessin.cpp u2-dessin.h u3-callbacks.cpp u3-callbacks.h u4-fonctions.cpp u4-fonctions.h
# Fichiers source .cpp
SRC=main.cpp u1-interface.cpp u2-dessin.cpp u3-callbacks.cpp u4-fonctions.cpp
# Fichiers objets .o
OBJ=$(SRC:.cpp=.o)
# Fichiers entetes .h
SRH=$(SRC:.cpp=.h)

all:$(EXEC) clean

$(EXEC):$(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(POSTOPTIONS) $(LDFLAGS) $(CFLAGS)

%.o:%.cpp $(SRH)
	$(CC) $(CFLAGS) -o $@ -c $< $(PREOPTIONS)

.PHONY: clean cleanall
clean:
	rm -f *.o obj/Debug/*.o
cleanall:
	rm -f *.o obj/Debug/*.o $(EXEC) bin/Debug/$(EXEC)
