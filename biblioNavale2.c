#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// gcc -c biblioNavale2.c ; gcc BatailleNavale.c -o MaBatailleNavale.o biblioNavale.o biblioNavale2.o
// 7/7 fonctions réalisées

int verifDeux(char tab[][10]){
	int compte=0;
	int verif=0;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(!(tab[i][j]==' ')){ //compte le nombre de case du tableau sans espace (avec des bateaux)
				compte++;
			}
		}
	}
	if(compte==17){ //s'il y a 17 cases avec bateau, on renvoie 1. sinon on garde 0
		verif=1;
	}
	return verif;
}

void afficheDeux(char t[][10]){
	char lettre='A';
	printf("_|");
	for(int j=0;j<10;j++){ //1ere ligne, avec les chiffres
		printf("%d|",j);
	}
	printf("\n");
	for(int i=0;i<10;i++){ //tableau entier
		printf("%c|",lettre); //lettres sur la gauche du tableau
		for(int j=0;j<10;j++){
			printf("%c|",t[i][j]);
		}
		printf("\n");
		lettre++;
	}
}

void ajoutNavireAleatoireDeux(char tab[][10],char b,int t){
	int correct=0; // correct=0 quand le placement du navire est incorrect, correct=1 sinon
	srand(time(NULL));
	while(correct==0){ // on ne sort pas de la boucle tant que le navire n'a pas été bien placé
		char sens,ligne;
		int colonne;
		if(rand()%2==0){ //choix du sens
			sens='v';
		}else{
			sens='h';
		}
		colonne=rand()%10; //choix de la colonne
		ligne=rand()%10+'A'; //choix de la ligne
		if(sens=='h'){ //sens horizontal
			if(ligne>='A'&&ligne<='J'){ //vérifie la ligne
				if(colonne>=0&&colonne<=10-t){ //vérifie la colonne
					int verifieur=0;
					for(int i=colonne;i<colonne+t;i++){ //vérifie si le placement est possible, par rapport aux autres bateaux
						if(!(tab[ligne-'A'][i]==' ')){
							verifieur++;
						}
					}
					if(verifieur==0){ //si le placement est impossible, on n'écrit pas dans le tableau
						for(int i=colonne;i<colonne+t;i++){
							tab[ligne-'A'][i]=b; //écriture du bateau dans le tableau
						}
						correct=1;
					}
				}
			}
		}else if(sens=='v'){ //sens vertical : similaire au sens horizontal
			if(colonne>=0&&colonne<=9){
				if(ligne>='A'&&ligne<='J'-t){
					int verifieur=0;
					for(int i=ligne-'A';i<ligne-'A'+t;i++){
						if(!(tab[i][colonne]==' ')){
							verifieur++;
						}
					}
					if(verifieur==0){
						for(int i=ligne-'A';i<ligne-'A'+t;i++){
							tab[i][colonne]=b;
						}
						correct=1;
					}			
				}
			}
		}
	}
}

void entrerBateauMain(char plat[][10], char b, int t){ //fonctionne comme la fonction ajoutNavireAleatoireDeux, mais prend en compte les valeurs de l'utilisateur
	int correct=0;
	while(correct==0){
		afficheDeux(plat);
		printf("\nPlacez votre %c (longueur %d) :\n",b,t); 
		char sens,ligne;
		int colonne;
		scanf("%c,%c%d",&sens,&ligne,&colonne); 
		getchar(); // pour ne pas prendre le saut de ligne
		if(sens=='h'){
			if(ligne>='A'&&ligne<='J'){
				if(colonne>=0&&colonne<=10-t){
					int verifieur=0;
					for(int i=colonne;i<colonne+t;i++){
						if(!(plat[ligne-'A'][i]==' ')){
							verifieur++;
						}
					}
					if(verifieur==0){
						for(int i=colonne;i<colonne+t;i++){
							plat[ligne-'A'][i]=b;
						}
						correct=1;
					}else{		
						printf("La position choisie empiete sur un autre navire.\n");
					}
				}else{
					printf("Le navire est place en dehors du tableau.\n");
				}
			}else{
				printf("Le navire est place en dehors du tableau.\n");
			}
		}else if(sens=='v'){
			if(colonne>=0&&colonne<=9){
				if(ligne>='A'&&ligne<='J'-t){
					int verifieur=0;
					for(int i=ligne-'A';i<ligne-'A'+t;i++){
						if(!(plat[i][colonne]==' ')){
							verifieur++;
						}
					}
					if(verifieur==0){
						for(int i=ligne-'A';i<ligne-'A'+t;i++){
							plat[i][colonne]=b;
						}
						correct=1;
					}else{
						printf("La position choisie empiete sur un autre navire.\n");
					}				
				}else{
					printf("Le navire est place en dehors du tableau.\n");
				}
			}else{
				printf("Le navire est place en dehors du tableau.\n");
			}
		}else{
			printf("Nous n'avons pas pu comprendre ce que vous avez entre.\n");
		}
	}
}

void initPlateauDeux(char plat[][10]){ //crée un plateau de jeu
	char choix='B'; //initié à 'B' pour ne pas rentrer dans la boucle while ci-dessous
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			plat[i][j]=' '; //rempli d'espace pour pouvoir l'afficher facilement
		}
	}
	while(choix!='A'&&choix!='M'){
		printf("Souhaitez-vous placer vos navires a la (M)ain, ou (A)leatoirement ?\n");
		choix=getchar();
		getchar();
	}
	if(choix=='A'){ //choix aléatoire
		ajoutNavireAleatoireDeux(plat,'A',5);		
		ajoutNavireAleatoireDeux(plat,'C',4);
		ajoutNavireAleatoireDeux(plat,'S',3);
		ajoutNavireAleatoireDeux(plat,'M',3);
		ajoutNavireAleatoireDeux(plat,'T',2);
	}
	if(choix=='M'){ //choix manuel
		printf("Vous devez placer vos navires.\nPour chaque navire, indiquez horizontal (h) ou vertical (v), suivi de la case la plus au nord-ouest (ex : h,E4)\n");
		entrerBateauMain(plat,'A',5);
		entrerBateauMain(plat,'C',4);
		entrerBateauMain(plat,'S',3);
		entrerBateauMain(plat,'M',3);
		entrerBateauMain(plat,'T',2);
	}
}

int jouerJoueurDeux(char adv[][10]){ //problème : en cas de mauvaise entrée de l'utilisateur (e.g. 'F4*'), le programme ne fonctionne plus.
	int tir;
	char ligne;
	int colonne;
	getchar();
	scanf("%c%d",&ligne,&colonne); //récupère le choix de l'utilisateur
	if(ligne>='A'&&ligne<='J'){
		if(colonne>=0&&colonne<=9){
			if(adv[ligne-'A'][colonne]==' '){
				tir=-1;
				adv[ligne-'A'][colonne]='.';
			}else if(adv[ligne-'A'][colonne]=='A'){ 				//tous les cas différents
				tir=0;												//sont listés ici
			}else if(adv[ligne-'A'][colonne]=='C'){
				tir=1;
			}else if(adv[ligne-'A'][colonne]=='S'){
				tir=2;
			}else if(adv[ligne-'A'][colonne]=='M'){
				tir=3;
			}else if(adv[ligne-'A'][colonne]=='T'){
				tir=4;
			}else{
				tir=-2;
			}
			if(tir>=0){
				adv[ligne-'A'][colonne]='x';
			}
		}else{
			tir=-3;
		}
	}else{
		tir=-3;
	}
	return tir;
}

char* navireDeux(int i){
	char* nomBateau=calloc(12,sizeof(char));
	if(i==0){
		nomBateau="Porte-Avion";
	}
	if(i==1){
		nomBateau="Croiseur";
	}
	if(i==2){
		nomBateau="Sous-Marin";
	}
	if(i==3){
		nomBateau="Mous-Sarin";
	}
	if(i==4){
		nomBateau="Torpilleur";
	}
	return nomBateau;
}

void afficheduoDeux(char t[][10],char p[][10]){
	char lettre='A';
	for(int i=0;i<2;i++){
		printf("_|");
		for(int j=0;j<10;j++){
			printf("%d|",j);
		}
		printf("          ");
	}
	printf("\n");
	for(int i=0;i<10;i++){
		printf("%c|",lettre);
		for(int j=0;j<10;j++){
			if(t[i][j]=='x'||t[i][j]=='.'){
			printf("%c|",t[i][j]);
			}else{
				printf(" |");
			}
		}
		printf("%11c|",lettre); //crée un espace entre les tableaux
		for(int j=0;j<10;j++){
			if(p[i][j]=='x'||p[i][j]=='.'){
			printf("%c|",p[i][j]);
			}else{
				printf(" |");
			}
		}
		printf("\n");
		lettre++;
	}
}