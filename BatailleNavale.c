#include "biblioNavale.h"
#include <stdio.h>
#include "biblioNavale2.h"

// verifions vérifie si la partie a été initialisée correctement (17 cases remplies par plateau)
int verifions(char plateauj1[][10], char plateauj2[][10]){
	int continuer=1;
	if(verif(plateauj1)!=1||verif(plateauj2)!=1){
		printf("Une erreur a eu lieu, veuillez recommencer la partie.\n");
		continuer=0;
	}
	return continuer;
}

// messageBateauCoule permet d'afficher dans la sortie standard si un bateau a été frappé ou non
void messageBateauCoule (int bateaux[]){
	for(int i=0; i<5;i++){
		if(bateaux[i]==0){
			printf("--> Vous avez eu le %s !\n",navire(i));
			bateaux[i]=-1; //une fois le message envoyé, on met la "vie" du bateau à -1
		}
	}
}

// attaque prend le résultat de la fonction jouerJoueur, pour comprendre où le tir a frappé et comment réagir en conséquence
int attaque(int tir, int bateaux[]){
	int peutrejouer;
	if (tir>=0){ //tous les cas où un navire a été touché
		printf("-> Touché !\n");
		peutrejouer=1;
		bateaux[tir]--; //retire un "point de vie" au bateau qui a été touché
		messageBateauCoule(bateaux);
	}
	if(tir==-1){ //le tir est tombé à l'eau
		printf("-> Plouf...\n");
		peutrejouer=0;
	}
	if(tir==-2){ //soit l'utilisateur a rentré un caractère non reconnu, soit c'est une case qu'il a déjà rentrée. dans ce cas, on le fait rejouer
		printf("-> Une erreur est survenue. Soit :\n - Un caractere que vous avez entre n'est pas reconnu\n - Vous avez déjà entré cette case\n");
		peutrejouer=1;
	}
	if(tir==-3){ //l'utilisateur a entré une case hors plateau. dans ce cas, on l'invite à rejouer
		printf("-> Le tir est hors plateau, veuillez rejouer :\n");
		peutrejouer=1;	
	}
	return peutrejouer; //on retourne cette variable pour refaire un tour pour le même joueur
}

// victoire vérifie si tous les bateaux d'un joueur ont été coulés, c'est à dire si chaque case du tableau contenant ses bateaux est égale à -1
int victoire(int bateaux[]){
	int continuer=1,bateauxcoules=0;
	for (int i=0;i<5;i++){
		if (bateaux[i]==-1){
			bateauxcoules++; //bateauxcoules compte le nombre de bateaux coules
		}
	}
	if(bateauxcoules==5){ //si 5 bateaux ont été coulés, on arrête la partie
		continuer=0;
	}
	return continuer;
}

//creerTableaux permet l'initialisation de la partie
void creerTableaux(char plateauj1[][10], char plateauj2[][10]){
	printf("Joueur 1 :\n");
	initPlateau(plateauj1);
	printf("Joueur 2 :\n");
	initPlateau(plateauj2);
}

// affiche les plateaux avec un habillage autour, pour le style
void afficheduoMieux(char plateauj1[][10], char plateauj2[][10]){
	printf("______________________________________________________\n");
	printf("       Joueur 1                        Joueur 2       \n");
	afficheduo(plateauj2,plateauj1);
}

int main(){
	char plateauj1[10][10],plateauj2[10][10];	 //plateau du joueur 1 et du joueur 2
	creerTableaux(plateauj1,plateauj2);
	int tirj1,tirj2;		 // les variables qui montrent sur quoi le joueur a tiré (navire, eau, hors-plateau)
	int bateauxj1[5]={5,4,3,3,2}; 		//navires du joueur 2, sur lequels le joueur 1 tire
	int bateauxj2[5]={5,4,3,3,2}; 		//l'inverse
	int peutrejouer=0; 		//lorsque peutrejouer=1, le joueur rejoue
	int continuer=1;		 //lorsque continuer=0, la partie s'arrête
	verifions(plateauj1,plateauj2);
	while(continuer){
		do{ // déroulement du tour du joueur 1
			afficheduoMieux(plateauj1,plateauj2);
			printf("> Joueur 1, à vous :\n");
			tirj1=jouerJoueurDeux(plateauj2); 
			peutrejouer=attaque(tirj1,bateauxj2);
			continuer=victoire(bateauxj2);
			if(continuer==0){ 		//si continuer=0, la partie doit s'arrêter
				peutrejouer=0; 
				printf("---> Le joueur 1 remporte la partie !\n"); 		//message de victoire
				afficheduoMieux(plateauj1,plateauj2);	 //affiche la statut final de la partie
			}
		}while(peutrejouer);
		if(continuer!=0){
			do{ // tour du joueur 2, similaire au joueur 1
				afficheduoMieux(plateauj1,plateauj2);
				printf("> Joueur 2, a vous :\n");
				tirj2=jouerJoueurDeux(plateauj1);
				peutrejouer=attaque(tirj2,bateauxj1);
				continuer=victoire(bateauxj1);
				if(continuer==0){
					peutrejouer=0;
					printf("---> Le joueur 2 remporte la partie !\n");
					afficheduoMieux(plateauj1,plateauj2);
				}
			}while(peutrejouer);
		}
	}
	return 0;
}