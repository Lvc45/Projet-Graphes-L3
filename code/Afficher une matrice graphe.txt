#include <stdio.h>
#include <stdlib.h>
#define ligne 20
#define colonne 20

void afficherMatrice(char mat[ligne][colonne]){
    int i,j;
    for (i=0;i<ligne;i++) {
        if ((mat[i][0]>='0'&&mat[i][0]<='9')||mat[i][0]=='-'){
            printf("|");
            for (j=0;j<colonne;j++) {
                if (mat[i][j]=='*'||(mat[i][j]>='0'&&mat[i][j]<='9')||mat[i][j]=='-'){
                    printf(" %c |",mat[i][j]);
                }
            }
            printf("\n");
        }
    }

}


int main(){
    char tableau[ligne][colonne] = {
        {'-','0','1','2','3','4','5','6'},
        {'0','*','0','0','*','*','*','*'},
        {'1','*','*','*','1','1','*','*'},
        {'2','*','*','*','*','2','2','*'},
        {'3','*','*','*','*','*','*','3'},
        {'4','*','*','*','*','*','4','*'},
        {'5','*','*','*','*','*','*','*'},
        {'6','*','*','*','*','*','*','*'},
      };
    afficherMatrice(tableau);
    return 0;
}