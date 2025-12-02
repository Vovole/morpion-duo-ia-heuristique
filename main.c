#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "header.h"

// Animation progressBar
void progressBar(int width, int ms_total) {
    int steps = width;
    int delay = ms_total / steps;

    printf("[");
    for (int i = 0; i < width; i++) printf(" ");
    printf("] 0%%");
    fflush(stdout);

    for (int i = 0; i < steps; i++) {
        printf("\r[");
        for (int j = 0; j < width; j++) {
            if (j <= i) putchar('#');
            else putchar(' ');
        }
        int percent = (int)((100.0 * (i + 1)) / steps);
        printf("] %3d%%", percent);
        fflush(stdout);
        Sleep(delay);
    }
    printf("\n");
}

int main() {
    int boucle = 1;
    int choix = 0;
    int scoreJoueurX = 0, scoreJoueurO = 0, scoreJoueur = 0, scoreOrdinateur = 0;

    while (boucle) {
        printf("\n=== Bienvenue dans le jeu du Morpion ! ===\n");
        printf("Scores Duo : Joueur X = %d  | Joueur O = %d\n", scoreJoueurX, scoreJoueurO);
        printf("Scores vs IA : Joueur = %d  | Ordinateur = %d\n", scoreJoueur, scoreOrdinateur);
        printf("\nVotre choix :\n");
        printf("1 - Jouer en duo\n");
        printf("2 - Jouer contre l'IA\n");
        printf("3 - Quitter\n");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                progressBar(30, 2000);
                char val = morpionDuo();
                if (val == CROIX) scoreJoueurX++;
                else if (val == CERCLE) scoreJoueurO++;
                break;
            }
            case 2: {
                progressBar(30, 2000);
                char valIA = morpionIAHeuristique(); // IA heuristique
                if (valIA == CROIX) scoreJoueur++;
                else if (valIA == CERCLE) scoreOrdinateur++;
                break;
            }
            case 3:
                boucle = 0;
                printf("Merci d'avoir joué !\n");
                break;
            default:
                printf("Choix invalide ! Entrez un chiffre valide.\n");
                while(getchar() != '\n'); // vider buffer
                break;
        }
    }

    return 0;
}
