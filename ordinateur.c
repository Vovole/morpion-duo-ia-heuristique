#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

char tableau[TAILLE][TAILLE];

// Initialiser le plateau
void inittableau() {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            tableau[i][j] = VIDE;
}

// Afficher le plateau
void afficheTableau(char tab[TAILLE][TAILLE]) {
    printf("   ");
    for (int i = 1; i <= TAILLE; i++) printf(" %d ", i);
    printf("\n");

    for (int i = 0; i < TAILLE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < TAILLE; j++)
            printf("[%c]", tab[i][j]);
        printf("\n");
    }
    printf("\n");
}

// verifie si un joueur a gagne ou match nul
int partieEstFini(char tab[TAILLE][TAILLE], char *gagnant) {
    // lignes et colonnes
    for (int i = 0; i < TAILLE; i++) {
        int winRow = 1, winCol = 1;
        for (int j = 1; j < TAILLE; j++) {
            if (tab[i][j] != tab[i][0] || tab[i][0] == VIDE) winRow = 0;
            if (tab[j][i] != tab[0][i] || tab[0][i] == VIDE) winCol = 0;
        }
        if (winRow) { *gagnant = tab[i][0]; return 1; }
        if (winCol) { *gagnant = tab[0][i]; return 1; }
    }
    // diagonales
    char diag = tab[0][0];
    int k;
    for (k = 1; k < TAILLE; k++) if (tab[k][k] != diag) break;
    if (k == TAILLE && diag != VIDE) { *gagnant = diag; return 1; }

    diag = tab[0][TAILLE-1];
    for (k = 1; k < TAILLE; k++) if (tab[k][TAILLE-1-k] != diag) break;
    if (k == TAILLE && diag != VIDE) { *gagnant = diag; return 1; }

    // est plateau plein ?
    int full = 1;
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (tab[i][j] == VIDE) full = 0;
    if (full) { *gagnant = VIDE; return 1; }

    return 0;
}

// verifie si jouer a (r,c) donne la victoire pour le joueur
int victoirePotentielle(char joueur, int r, int c) {
    tableau[r][c] = joueur;
    char gagnant;
    int fini = partieEstFini(tableau, &gagnant);
    tableau[r][c] = VIDE;
    return fini && gagnant == joueur;
}

// IA heuristique
void bestMoveHeuristique(int *moveRow, int *moveCol) {
    // verifier victoire 
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (tableau[i][j] == VIDE && victoirePotentielle(CERCLE, i, j)) {
                *moveRow = i; *moveCol = j;
                return;
            }
    // bloquer adversaire
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (tableau[i][j] == VIDE && victoirePotentielle(CROIX, i, j)) {
                *moveRow = i; *moveCol = j;
                return;
            }
    // jouer centre
    if (tableau[1][1] == VIDE) { *moveRow = 1; *moveCol = 1; return; }
    // jouer coin libre
    int coins[4][2] = {{0,0},{0,2},{2,0},{2,2}};
    for (int i=0; i<4; i++)
        if (tableau[coins[i][0]][coins[i][1]] == VIDE) {
            *moveRow = coins[i][0]; *moveCol = coins[i][1];
            return;
        }
    // jouer aleatoire
    int r, c;
    srand(time(NULL));
    do {
        r = rand() % TAILLE;
        c = rand() % TAILLE;
    } while(tableau[r][c] != VIDE);
    *moveRow = r;
    *moveCol = c;
}

// partie contre IA "heuristique"
char morpionIAHeuristique() {
    inittableau();
    int joueurTour = 1; // 1 = humain(CROIX), 0 = IA(CERCLE)
    int r, c;
    char gagnant = VIDE;

    while (1) {
        afficheTableau(tableau);
        if (joueurTour) {
            printf("Votre tour ! \n Entrer x,y :  ");
            if (scanf("%d,%d", &r, &c) != 2 || r < 1 || r > TAILLE || c < 1 || c > TAILLE || tableau[r-1][c-1] != VIDE) {
                printf("Case invalide !\n");
                while(getchar()!='\n');
                continue;
            }
            tableau[r-1][c-1] = CROIX;
            joueurTour = 0;
        } else {
            bestMoveHeuristique(&r, &c);
            tableau[r][c] = CERCLE;
            printf("IA joue en %d,%d\n", r+1, c+1);
            joueurTour = 1;
        }

        if (partieEstFini(tableau, &gagnant)) {
            afficheTableau(tableau);
            if (gagnant == CROIX) printf("Vous gagnez !\n");
            else if (gagnant == CERCLE) printf("L'IA gagne !\n");
            else printf("Match nul !\n");
            return gagnant;
        }
    }
}
