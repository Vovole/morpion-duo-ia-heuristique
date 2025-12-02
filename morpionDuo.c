#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "header.h"

// Affiche le plateau (uniquement pour ce fichier)
void afficheTableauDuo(char tab[TAILLE][TAILLE]){
    printf("   ");
    for (int i = 1; i <= TAILLE; i++) {
        printf(" %d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < TAILLE; j++) {
            printf("[%c]", tab[i][j]);
        }
        printf("\n");
    }
}

// Vérifie si un joueur a gagné (uniquement pour ce fichier)
int partieEstFiniPointDinterrogationLoLDuo(char tab[TAILLE][TAILLE], char *gagnant) {

    // lignes
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE - 3; j++) {
            char c = tab[i][j];
            if (c != VIDE && c == tab[i][j + 1] && c == tab[i][j + 2] && c == tab[i][j + 3]) {
                *gagnant = c;
                return 1;
            }
        }

    // colonnes
    for (int j = 0; j < TAILLE; j++)
        for (int i = 0; i < TAILLE - 3; i++) {
            char c = tab[i][j];
            if (c != VIDE && c == tab[i + 1][j] && c == tab[i + 2][j] && c == tab[i + 3][j]) {
                *gagnant = c;
                return 1;
            }
        }

    // diagonales droites
    for (int i = 0; i < TAILLE - 3; i++)
        for (int j = 0; j < TAILLE - 3; j++) {
            char c = tab[i][j];
            if (c != VIDE && c == tab[i + 1][j + 1] && c == tab[i + 2][j + 2] && c == tab[i + 3][j + 3]) {
                *gagnant = c;
                return 1;
            }
        }

    // diagonales gauche
    for (int i = 0; i < TAILLE - 3; i++)
        for (int j = 3; j < TAILLE; j++) {
            char c = tab[i][j];
            if (c != VIDE && c == tab[i + 1][j - 1] && c == tab[i + 2][j - 2] && c == tab[i + 3][j - 3]) {
                *gagnant = c;
                return 1;
            }
        }

    return 0;
}

// Lance le morpion en 1v1
char morpionDuo(){
    char tab[TAILLE][TAILLE];
    char joueur = CROIX;
    char gagnant = VIDE;
    int boucle = 1;

    // initialisation tableau
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            tab[i][j] = VIDE;

    while (boucle == 1) {
        afficheTableauDuo(tab);

        printf("\nAu tour du joueur %c\n", joueur);

        int x, y;
        printf("Entrer x,y : ");
        scanf("%d,%d", &x, &y);

        if (x < 1 || x > TAILLE || y < 1 || y > TAILLE) {
            printf("Coordonnees invalides !\n");
            continue;
        }

        if (tab[x - 1][y - 1] != VIDE) {
            printf("Case deja prise !\n");
            continue;
        }

        // place du joueur
        tab[x - 1][y - 1] = joueur;

        // verifie fin
        if (partieEstFiniPointDinterrogationLoLDuo(tab, &gagnant)) {
            boucle = 0;
        } else {
            // change de joueur
            joueur = (joueur == CROIX) ? CERCLE : CROIX;
        }

        // verification match nul
        int plein = 1;
        for (int i = 0; i < TAILLE; i++)
            for (int j = 0; j < TAILLE; j++)
                if (tab[i][j] == VIDE)
                    plein = 0;
        if (plein) {
            boucle = 0;
            gagnant = VIDE;
        }
    }

    printf("\n--- fin de partie ---\n");
    afficheTableauDuo(tab);

    if (gagnant == CROIX) {
        printf("Le joueur X gagne !\n");
    } else if (gagnant == CERCLE) {
        printf("Le joueur O gagne !\n");
    } else {
        printf("Match nul !\n");
    }
    return gagnant;
}
