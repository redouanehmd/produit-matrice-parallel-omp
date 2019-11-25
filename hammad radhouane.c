// Hammad radhouane

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <time.h> 
#include<math.h>
#include<omp.h>


#define nbr_ligne_A 3
#define  nbr_colonne_A 4
#define nbr_ligne_B 4
#define  nbr_colonne_B 2

int A [nbr_ligne_A] [nbr_colonne_A];
int B [nbr_ligne_B] [nbr_colonne_B];
int C [nbr_ligne_A] [nbr_colonne_B]; 


int main(int argc, char *argv[]){
	int i,j,k;
	double debP,finP,debS,finS;
	
	
    for ( i = 0; i < nbr_ligne_A; i++) { 
        for (j = 0; j < nbr_colonne_A; j++) { 
            A[i][j] = rand() % 10; 
        } 
    } 
	for ( i = 0; i < nbr_ligne_B; i++) { 
        for (j = 0; j < nbr_colonne_B; j++) {  
            B[i][j] = rand() % 10; 
        } 
    } 

    //calcul du C en parallel
    debP=clock();
    #pragma omp parallel for
        for( i = 0;i < nbr_ligne_A; i++){
        	for(j = 0; j < nbr_colonne_B; j++) {
				for(k = 0; k < nbr_colonne_B; k++)
                	C[i][j] =C[i][j] + A[i][k] * B[k][j]; 
            }

        }
         
        
    finP=clock(); 
    // affichage du C parallel
    printf("Matrice C parallel : \n ");
	for (i = 0; i < nbr_ligne_A; ++i){
       for ( j = 0; j < nbr_colonne_B; ++j){
           printf("%d  ", C[i][j]); 
       }
       printf("\n"); 
   }
    printf("temps parallele = %f \n", (double)(finP-debP)/CLOCKS_PER_SEC);
        
    //calcul du C en sequenciel 
    debS=clock();
	for ( i = 0; i < nbr_ligne_A; ++i){
       for ( j = 0; j < nbr_colonne_B; ++j){
          C[i][j]=0;
          for (k = 0; k < nbr_colonne_B; ++k)
          {    
             C[i][j]=C[i][j]+A[i][k]*B[k][j];
          }
		} 
	} 
    finS=clock();

    
    // affichage du C sequenciel  
    printf("Matrice C sequenciel : \n ");
	for ( i = 0; i < nbr_ligne_A; ++i){
       for (j = 0; j < nbr_colonne_B; ++j){
           printf("%d  ", C[i][j]); 
       }
       printf("\n"); 
   }
    	 
    printf("temps sequenciel= %f\n", (double)(finS-debS)/CLOCKS_PER_SEC);
	  
    return 0;

    }
  

