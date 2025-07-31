#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LIGNE_MAX 30
#define COLONNE_MAX 30
#define MAX_CHEMINS 100
#define MAX_CHARACTER 10
#define NOMBRE_TEXT 14
#define NOMBRE_MAX_TEXT 100

int convert(char matrice[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], char *test);
void afficherMatriceChar(char tableau[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int n);
void charToInt(char matrice[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int tableau[LIGNE_MAX][COLONNE_MAX], int n);
void matriceAdjacense(char mat[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int copie[LIGNE_MAX][COLONNE_MAX], int taille);
void afficherMatrice(int matrice[LIGNE_MAX][COLONNE_MAX], int n);
void copieMatrice(int matrice[LIGNE_MAX][COLONNE_MAX],int copie[LIGNE_MAX][COLONNE_MAX], int n);
void verifierRecursivement(int matrice[LIGNE_MAX][COLONNE_MAX], int n, int lignesTransformees[], int *index, int *rang, char rep[LIGNE_MAX][100],int stockAffichage[]);
bool transformerColonnesEtLignesZeroRecursif(int matrice[LIGNE_MAX][COLONNE_MAX], int n, int lignesTransformees[], int *index, int *rang, char rep[LIGNE_MAX][100],int stockAffichage[]);
bool estDejaTransformee(int lignesTransformees[], int taille, int ligne);
bool estMatriceNulle(int matrice[LIGNE_MAX][COLONNE_MAX], int n);
bool verifier_negatif(char matrice[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int n);
void datesAuPlusTot(int matrice[LIGNE_MAX][COLONNE_MAX],int n,int lignesTransformee[],int rep[]);
int dureeTotale(int datesAuPlusTot[],int n);
void datesAuPlusTard(int matrice[LIGNE_MAX][COLONNE_MAX],int n,int lignesTransformee[],int rep[],int dureeTotale);
int nbrSuccesseur(int matrice[LIGNE_MAX][COLONNE_MAX], int ligne, int n, int successeurs[]);
void trouverCheminCritiques(int matrice[LIGNE_MAX][COLONNE_MAX], int n,int datesAuPlusTot[COLONNE_MAX], int datesAuPlusTard[COLONNE_MAX],int cheminsCritiques[MAX_CHEMINS][COLONNE_MAX], int rang[LIGNE_MAX],int *nbrCheminsCritiquesFinaux, int longueursCheminsCritiquesFinaux[MAX_CHEMINS]);

#endif //PROTOTYPE_H
