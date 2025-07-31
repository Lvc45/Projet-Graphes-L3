#include "prototype.h"

int main(void)
{

    // Nos test
    char test[NOMBRE_MAX_TEXT][200] = {"table 1.txt","table 2.txt","table 3.txt","table 4.txt","table 5.txt","table 6.txt","table 7.txt","table 8.txt","table 9.txt","table 10.txt","table 11.txt","table 12.txt","table 13.txt","table 14.txt"};

    // Pour chacune de nos test :
    for(int i=0;i<NOMBRE_TEXT;i++) {
        printf("\n====================\nPour le test numero %d (%s)\n====================\n",i+1,test[i]);
        // Déclaration de nos tableau
        char tableau[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER];   // Représentation de notre tableau proprement avec des chaînes de caractères
        int matrice[LIGNE_MAX][COLONNE_MAX];                   // Représentation de notre tableau mais avec des entiers

        // Importer les tableaux des fichiers textes dans notre programme
        int n = convert(tableau,test[i]);                   // n représente la taille du tableau, convert est la fonction qui crée le tableau
        printf("La matrice initiale : \n");
        afficherMatriceChar(tableau,n);             // On affiche le tableau avec les chaînes de caractères

        // Conversion de la matrice de contraintes en matrice d'entiers
        charToInt(tableau, matrice, n);

        // Création et affichage de la matrice d'adjacence
        int adjacense[LIGNE_MAX][COLONNE_MAX];
        printf("\nLa matrice d'ajacence : \n");
        matriceAdjacense(tableau, adjacense, n);
        afficherMatrice(adjacense, n-1);
        printf("\n");

        // Détection de circuit et calcul des rangs
        int copie[LIGNE_MAX][COLONNE_MAX];
        copieMatrice(adjacense, copie, n-1);   // On crée une copie car on ne veut pas modifier la matrice d'origine
        int lignesTransformees[LIGNE_MAX]; // Tableau pour stocker les indices des lignes transformées.
        int stockAffichage[LIGNE_MAX];
        for(int i=0;i<n;i++) //On initialise le tableau des lignes transformees
            stockAffichage[i] = 0;
        int taille = 0;     // Nombre de lignes transformées
        int rang = 0;       // Rang initial
        char rang_liste[LIGNE_MAX][100];
        verifierRecursivement(copie, n-1, lignesTransformees, &taille, &rang, rang_liste, stockAffichage);

        // Vérifie si la matrice est entièrement composée de zéros.
        if (estMatriceNulle(copie, n-1)) {
            printf("\nIl n'y a pas de circuit.\n");
        } else {
            printf("\nIl y a un circuit.\n");
        }

        // Vérifie la présence d'arcs négatifs
        if(verifier_negatif(tableau, n))
            printf("Il n'y a pas d'arcs negatifs\n");
        else
            printf("Il y a des arcs negatifs\n");
        printf("\n");

        // Algorithme des dates au plus tôt et au plus tard uniquement s'il n'y a pas de circuit et que les arcs sont positifs
        int datesAuPlusTotRep[COLONNE_MAX];
        int datesAuPlusTardRep[COLONNE_MAX];
        if(estMatriceNulle(copie, n-1) && verifier_negatif(tableau, n)) {
            printf("C'est un graphe d'ordonnancement\n");
            for(int i=0;i<taille;i++) {
                printf("%s",rang_liste[i]);
            }
            printf("\n");
            datesAuPlusTot(matrice, n-1, lignesTransformees, datesAuPlusTotRep);
            for(int i = 0; i < n-1; i++)
                printf("La date au plus tot du sommet %d est %d\n", i, datesAuPlusTotRep[i]);

            datesAuPlusTard(matrice, n-1, lignesTransformees, datesAuPlusTardRep, dureeTotale(datesAuPlusTotRep, n-1));
            printf("\n");
            for(int i = 0; i < n-1; i++)
                printf("La date au plus tard du sommet %d est %d\n", i, datesAuPlusTardRep[i]);

            // Trouver les chemins critiques
            int cheminsCritiques[MAX_CHEMINS][COLONNE_MAX];
            int nbrCheminsCritiquesFinaux = 0;
            int longueursCheminsCritiquesFinaux[MAX_CHEMINS];

            trouverCheminCritiques(matrice, n-1, datesAuPlusTotRep, datesAuPlusTardRep, cheminsCritiques, lignesTransformees, &nbrCheminsCritiquesFinaux, longueursCheminsCritiquesFinaux);
        }
    }
    return 0;
}
