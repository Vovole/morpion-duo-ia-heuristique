#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define TAILLE 4
#define VIDE ' '
#define CERCLE 'O'
#define CROIX 'X'

void afficheTableauDuo(char tab[TAILLE][TAILLE]);
int partieEstFiniPointDinterrogationLoLDuo(char tab[TAILLE][TAILLE], char *gagnant);
char morpionDuo();

void afficheTableau(char tab[TAILLE][TAILLE]);

void bestMoveHeuristique(int *moveRow, int *moveCol);
char morpionIAHeuristique();

#endif