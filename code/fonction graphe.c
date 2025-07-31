#include "prototype.h"

// Lire le document test de Moodle
int convert(char matrice[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], char *test) {
    int ligne = 0;
    char buffer[256];
    int temp_tableau[LIGNE_MAX][COLONNE_MAX] = {0};  // Initialiser à zéro
    int nb_elements_par_ligne[LIGNE_MAX] = {0};      // Initialiser à zéro
    int n = 0;

    FILE *fichier = fopen(test, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Lecture des données du fichier
    while (fgets(buffer, sizeof(buffer), fichier) != NULL && ligne < LIGNE_MAX) {
        int colonne = 0;
        char *token = strtok(buffer, " \n");

        while (token != NULL && colonne < COLONNE_MAX) {
            temp_tableau[ligne][colonne] = atoi(token);
            colonne++;
            token = strtok(NULL, " \n");
        }

        nb_elements_par_ligne[ligne] = colonne;
        ligne++;
    }
    fclose(fichier);

    int nbval = ligne + 3;
    // Initialisation de la matrice avec '*'
    for (int i = 0; i < nbval; i++) {
        for (int j = 0; j < nbval; j++) {
            matrice[i][j][0] = '*';
            matrice[i][j][1] = '\0';
        }
        n++;
    }
    // Assignation du caractère '-' à la première case
    matrice[0][0][0] = '-';
    matrice[0][0][1] = '\0';

    // Assignation des labels aux première ligne et première colonne
    for (int i = 0; i < nbval - 1; i++) {
        snprintf(matrice[0][i + 1], MAX_CHARACTER, "%d", i);
        snprintf(matrice[i + 1][0], MAX_CHARACTER, "%d", i);
    }

    int temoin[LIGNE_MAX] = {0};  // Initialiser à zéro

    for (int i = 0; i < ligne; i++) {
        int taille = nb_elements_par_ligne[i];
        if (taille < 3) {
            // Assignation de "0" si pas de prédécesseurs
            snprintf(matrice[1][i + 2], MAX_CHARACTER, "0");
        } else {
            for (int j = 2; j < taille; j++) {
                int pred = temp_tableau[i][j];
                if (pred > 0 && pred < LIGNE_MAX) {
                    temoin[pred]++;
                    if ((pred - 1) < COLONNE_MAX) {
                        int from = pred - 1;
                        if (from >= 0 && from < nbval - 1) {
                            // Assignation de la valeur correspondante dans la matrice
                            snprintf(matrice[pred + 1][i + 2], MAX_CHARACTER, "%d", temp_tableau[pred - 1][1]);
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i < nbval - 2; i++) {
        if (temoin[i] == 0) {
            if ((i - 1) < ligne && 1 < COLONNE_MAX) {
                // Assignation de la durée de la tâche si pas de prédécesseurs
                snprintf(matrice[i + 1][nbval - 1], MAX_CHARACTER, "%d", temp_tableau[i - 1][1]);
            }
        }
    }
    return n;
}





// Afficher une matrice de chaîne de caractères
void afficherMatriceChar(char tableau[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int n){
    for (int i = 0; i < n; i++) {       // Parcours les lignes
        for (int j = 0; j < n; j++) {   // Parcours les colonnes
            printf("%-3s|", tableau[i][j]);  //Affiche la chaîne de charactère
        }
        printf("\n");           // Retour à la ligne à chaque nouvelle ligne
    }
    printf("\nLe sommet d'entree est %d et de sortie est %d\n",0,n-2);
}

// Convertir la matrice de chaîne de caractère en matrice d'entier
void charToInt(char matrice[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int tableau[LIGNE_MAX][COLONNE_MAX], int n){
    for(int i = 1; i < n; i++) {                // Parcours les lignes (sans prendre le 0 car la première ligne est la "légende")
        for(int j = 1; j < n; j++) {            // Parcours les colonnes (sans prendre le 0 car la première colonne est la "légende")
            if(matrice[i][j][0] == '*')         // Si on à une étoile : il n'y a pas d'arrête
                tableau[i-1][j-1] = -1;         // On sait qu'il ne peux pas y avoir d'arête négative dans le problème d'ordonnancement, donc on met -1 pour dire qu'il y a pas d'arête
            else {
                int number = atoi(matrice[i][j]);   // Convertir la chaîne de caractère en nombre
                tableau[i-1][j-1] = number;         // Mettre la valeur à la variable -1 car on a démarré à 1 --> ne pas avoir un décalage
            }
        }
    }
}

// Créer une matrice d'ajacence
void matriceAdjacense(char mat[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int copie[LIGNE_MAX][COLONNE_MAX], int taille){
    for(int i=1;i<taille;i++){              // Parcours les lignes (sans prendre le 0 car la première ligne est la "légende")
        for(int j=1;j<taille;j++){          // Parcours les colonnes (sans prendre le 0 car la première colonne est la "légende")
            if (mat[i][j][0] >= '0' && mat[i][j][0] <= '9')     //si le tableau donne une valeur entre deux sommets, alors on met 1 sur la matrice d'ajacence
                copie[i-1][j-1] = 1;
            else if(mat[i][j][0] == '*')
                copie[i-1][j-1] = 0;                            //sinon on met 0
        }
    }
}

//afficher une matrice avec des entiers (adjacence)
void afficherMatrice(int matrice[LIGNE_MAX][COLONNE_MAX], int n) {
    for (int i = 0; i < n; i++) {               //boucle sur les lignes
        for (int j = 0; j < n; j++) {           //boucle sur les colonnes
            printf("%d ", matrice[i][j]);       //affiche ligne par ligne
        }
        printf("\n");
    }
}

// On crée une copie de notre matrice
void copieMatrice(int matrice[LIGNE_MAX][COLONNE_MAX],int copie[LIGNE_MAX][COLONNE_MAX], int n){
    for (int i = 0; i < n; i++) {               //boucle sur les lignes
        for (int j = 0; j < n; j++) {           //boucle sur les colonnes
            copie[i][j] = matrice[i][j];        //crée une copie exacte
        }
    }
}


// PARTIE DETECTION CIRCUIT

// Fonction pour vérifier si une ligne a déjà été transformée en zéro.
// Elle parcourt le tableau lignesTransformees, qui stocke les lignes déjà transformées.
// Retourne true si la ligne est trouvée, sinon false.
bool estDejaTransformee(int lignesTransformees[], int taille, int ligne) {
    for (int i = 0; i < taille; i++) {
        if (lignesTransformees[i] == ligne) {
            return true;
        }
    }
    return false;
}

bool transformerColonnesEtLignesZeroRecursif(int matrice[LIGNE_MAX][COLONNE_MAX], int n, int lignesTransformees[], int *index, int *rang, char rep[LIGNE_MAX][100],int stockAffichage[]) {
    int colonneZero[COLONNE_MAX] = {0}; // Tableau pour marquer les colonnes remplies de zéros.
    bool changement = false;    // Indicateur pour savoir si une transformation a eu lieu.
    printf("=== Pour l'etape rang = %d : \n", *rang);

    // Sert juste à afficher les sommets restants à traiter (pour compréhension du code)
    printf("Les sommets restants a traiter : ");
    for(int i=0; i < n; i++) {
        if(stockAffichage[i] == 0)
            printf("%d ",i);
    }
    printf("\n");

    // Vérifie si chaque colonne est entièrement composée de zéros.
    for (int j = 0; j < n; j++) {
        bool colonneEstZero = true;
        for (int i = 0; i < n && colonneEstZero == true; i++) {
            if (matrice[i][j] != 0) {
                colonneEstZero = false;     //Si on trouve une valeur positive on sort
            }
        }
        if (colonneEstZero) {
            colonneZero[j] = 1; // Marque la colonne comme remplie de zéros.
        }
    }

    // Applique la transformation sur les colonnes et lignes marquées.
    for (int j = 0; j < n; j++) {
        if (colonneZero[j] == 1) {
            // Transforme tous les éléments de la colonne en zéros.
            for (int i = 0; i < n; i++) {
                if (matrice[i][j] != 0) {
                    matrice[i][j] = 0;
                    changement = true; // Indique qu'une transformation a eu lieu.
                }
            }

            // Enregistre la ligne transformée si elle ne l'est pas déjà.
            if (!estDejaTransformee(lignesTransformees, *index, j)) {
                lignesTransformees[*index] = j; // Enregistre l'indice de la ligne transformée.
                printf("Transformation sur la ligne %d colonne %d\n",j,j);
                stockAffichage[j] = 1;
                snprintf(rep[*index], 100, "Sommet %d : rang %d\n", j, *rang);
                (*index)++;
            }

            // Transforme tous les éléments de la ligne en zéros.
            for (int k = 0; k < n; k++) {
                if (matrice[j][k] != 0) {
                    matrice[j][k] = 0;
                    changement = true; // Indique qu'une transformation a eu lieu.
                }
            }
        }
    }
    printf("\n");
    (*rang)++;
    return changement; // Retourne true si une transformation a eu lieu, sinon false.
}

// Fonction récursive pour appliquer les transformations jusqu'à ce qu'aucune modification ne soit nécessaire.
void verifierRecursivement(int matrice[LIGNE_MAX][COLONNE_MAX], int n, int lignesTransformees[], int *index, int *rang, char rep[LIGNE_MAX][100],int stockAffichage[]) {
    if (transformerColonnesEtLignesZeroRecursif(matrice, n, lignesTransformees, index,rang,rep,stockAffichage)) {
        verifierRecursivement(matrice, n, lignesTransformees, index, rang, rep,stockAffichage); // Appel récursif
    }
}

// FIN PARTIE DETECTION CIRCUIT


// Fonction pour vérifier si la matrice est entièrement composée de zéros.
// Retourne false si un élément non zéro est trouvé, sinon true.
bool estMatriceNulle(int matrice[LIGNE_MAX][COLONNE_MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrice[i][j] != 0) {     // Il y a un nombre différent de 0
                return false;
            }
        }
    }
    return true;
}

//vérifier pas d'arc à valeur négatif
bool verifier_negatif(char matrice[LIGNE_MAX][COLONNE_MAX][MAX_CHARACTER], int n) {
    for (int i=1; i<n; i++) {           // Parcours les lignes (sans prendre le 0 car la première ligne est la "légende")
        for(int j=1; j<n; j++) {        // Parcours les colonne (sans prendre le 0 car la première colonne est la "légende")
            if(matrice[i][j][0]=='-') {
                return false;           //Si une valeur négatif --> return false
            }
        }
    }
    return true;                        //Si pas de valeur négatif --> return True
}


//date au plus tôt
void datesAuPlusTot(int matrice[LIGNE_MAX][COLONNE_MAX],int n,int lignesTransformee[],int rep[]) {
    rep[0] = 0;         //alpha est toujours à 0
    int indiceColonne;
    for(int i = 1;i < n;i++)
        rep[i] = -1;    //On initiliase correctement le tableau pour ne pas avoir de valeurs étranges au milieu (-1 représente dans notre cas : qu'il y a rien)
    for (int i = 0; i < n; i++) {           //on va parcourir le tableaux lignesTransformee --> c'est une étude dans l'ordre des rangs !
        indiceColonne = lignesTransformee[i];
        for (int j = 0; j < n; j++) {       //on va parcourir la matrice (en lignes) pour chercher les prédecesseurs --> colonne fixe mais ligne qui bouge --> les valeurs d'une même colonne sont les prédécesseurs du sommet !
            if(matrice[j][indiceColonne] >= 0){  //il existe un précesseur car ce n'est pas -1
                if(rep[j] < 0)                                                      //Si le sommet qu'on a trouvé est directement relié à celui de rang 0 ou non ?
                    rep[indiceColonne] = matrice[j][indiceColonne];                 //Si oui, on met juste la valeur de la matrice dans notre résultat
                else{
                    int nouvelValeur = matrice[j][indiceColonne] + rep[j];          //On calcule la date en prenant donc la somme des sommets se trouvant avant (prend en compte les dates au plus tôt déjà calculé)
                    if(rep[indiceColonne] < nouvelValeur)                           //Si la nouvelle date est plus tôt que la date déjà inséré, alors on la change
                        rep[indiceColonne] = nouvelValeur;
                }
            }
        }
    }
}

//durée totale
int dureeTotale(int datesAuPlusTot[],int n){
    return(datesAuPlusTot[n-1]);
}

//date au plus tard
void datesAuPlusTard(int matrice[LIGNE_MAX][COLONNE_MAX],int n,int lignesTransformee[],int rep[],int dureeTotale){
    rep[n-1] = dureeTotale;     //On lit cette fois ci à l'envers, et donc la dernière valeur c'est la durée totale du projet au plus tôt
    int indiceLigne;
    for(int i = 0;i < n-1;i++)
        rep[i] = -1;            //On initialise correctement le tableau
    for(int i = n-1;i >= 0;i--){   //On lit le tableau ligneTransformee à l'envers cette fois
        indiceLigne = lignesTransformee[i];
        for(int j=0;j < n;j++){  //cette fois ci, i désignera les lignes donc ligne fixe pour un j qui étudie pour chaque colonne, car les valeurs d'une même ligne sont les successeurs de celui qu'on regarde
            if(matrice[indiceLigne][j] >= 0){                                               //Il existe un successeur
                if(rep[j] >= 0){                                                            //le sommet du successeur est déjà traité (ça sera toujours vrai si notre chaîne est bien faite, c'est pour cela qu'on traite pas l'autre cas)
                    int nouvelValeur = rep[j] - matrice[indiceLigne][j];                    //la nouvelle date au plus tard
                    if(rep[indiceLigne] == -1 || rep[indiceLigne] > nouvelValeur)           //Si la nouvelle date est plus tard que la date déjà présente, attention on rajoute "rep[indiceLigne] == -1" pour le tout premier tour de boucle !
                        rep[indiceLigne] = nouvelValeur;
                }
            }
        }
    }
}


// Le nombre de successeur du sommet
int nbrSuccesseur(int matrice[LIGNE_MAX][COLONNE_MAX], int ligne, int n, int successeurs[]) {
    int nbrSuccesseur = 0;
    for (int i = 0; i < n; i++) {
        if (matrice[ligne][i] >= 0) {
            successeurs[nbrSuccesseur] = i;
            nbrSuccesseur++;
        }
    }
    return nbrSuccesseur;
}

// Chercher et afficher le chemin critique
void trouverCheminCritiques(int matrice[LIGNE_MAX][COLONNE_MAX], int n,int datesAuPlusTot[COLONNE_MAX], int datesAuPlusTard[COLONNE_MAX],int cheminsCritiques[MAX_CHEMINS][COLONNE_MAX], int rang[LIGNE_MAX],int *nbrCheminsCritiquesFinaux, int longueursCheminsCritiquesFinaux[MAX_CHEMINS]) {
    int nbrCheminCritique = 0;                  //Nombre de chemin actuellement trouvé (ayant une marge nulle de 0 au dernier sommet)
    int chemins[MAX_CHEMINS][COLONNE_MAX]; //Stocker les chemins en cours de traitement
    int longueurs[MAX_CHEMINS]; //Longueurs de chaque chemin du stockage

    //Initialisation
    chemins[0][0] = rang[0]; //Le premier sommet est 0 car c'est la représentation du alpha et il est stocké dans le premier chemin
    longueurs[0] = 1;        //la longueur du chemin est donc de 1 car on a mit le alpha
    nbrCheminCritique = 1;   //On a un chemin

    for (int i = 0; i < nbrCheminCritique; i++) {               //Parcours les chemins en cours de traitement
        int dernierSommet = chemins[i][longueurs[i] - 1];       //On prend le dernier élément du tableau --> i étant le chemin en cours de traitement et longueur étant la longueur du chemin, avec -1 on a accès à l'indice du dernier élément
        bool cheminTerminé = true;                              //Le chemin ne peux plus être étendue
        //On parcours maintenant pour trouver les successeur du dernier sommet du chemin en cours de traitement
        int indicesSuccesseurs[n]; // Tableau pour stocker les indices des successeurs
        int nbrSucc = nbrSuccesseur(matrice, dernierSommet, n, indicesSuccesseurs);

        for (int s = 0; s < nbrSucc; s++) {
            int j = indicesSuccesseurs[s]; // j est un successeur de dernierSommet
            if (datesAuPlusTot[j] == datesAuPlusTard[j]) { // Si le successeur est critique {   //Si le sommet est un successeur et a une marge nulle
                int sommetDejaPresent = false;                                                 //Vérifie si le sommet est déjà dans la liste pour éviter les doublons (problème rencontré --> on corrige)
                for (int k = 0; k < longueurs[i]; k++) {
                    if (chemins[i][k] == j) {
                        sommetDejaPresent = true;
                        break;
                    }
                }
                if (!sommetDejaPresent) {  //Le sommet n'est pas encore dans le chemin ET il doit y être
                    cheminTerminé = false; // Le chemin peut être étendu
                    for(int l=0;l < longueurs[i];l++)
                        chemins[nbrCheminCritique][l] = chemins[i][l];
                    chemins[nbrCheminCritique][longueurs[i]] = j;                                   //rajoute le sommet actuellement en traitement au nouveau chemin critique inédit
                    longueurs[nbrCheminCritique] = longueurs[i] + 1;                                //La logueur du nouveau chemin critique est + 1 à celui qu'on avait juste avant
                    nbrCheminCritique++;                                                            //Le nombre de chemin critique a augmenté
                }
            }
        }
        // On a finit de traiter tout les successeurs critiques du dernier sommet du chemin en cours de traitement
        //Si on a traité des successeurs critique alors on rentre pas dans le if suivant car ça veut dire que le chemin peut encore être étendu

        if (cheminTerminé) {        //on n'est pas rentré dans le if des marges nulles donc on peut pas étendre notre chemin --> pas de successeur critique
            for(int l=0;l < longueurs[i]; l++) {
                cheminsCritiques[*nbrCheminsCritiquesFinaux][l] = chemins[i][l];
            }
            longueursCheminsCritiquesFinaux[*nbrCheminsCritiquesFinaux] = longueurs[i];
            (*nbrCheminsCritiquesFinaux)++;
        }
    }
    //On a finit de traiter tout les chemins critiques !

    // Trouver le chemin critique le plus long
    int longueurMax = 0;
    int indexCheminMax = 0;
    for (int i = 0; i < *nbrCheminsCritiquesFinaux; i++) {
        if (longueursCheminsCritiquesFinaux[i] > longueurMax) {
            longueurMax = longueursCheminsCritiquesFinaux[i];
            indexCheminMax = i;
        }
    }

    // Afficher le chemin critique le plus long
    printf("\nLe chemin critique le plus long est : ");
    for (int i = 0; i < longueursCheminsCritiquesFinaux[indexCheminMax]; i++) {
        printf("%d ", cheminsCritiques[indexCheminMax][i]);
    }
    printf("\n");