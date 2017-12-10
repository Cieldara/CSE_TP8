#include "stdes.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	FICHIER *f1;
	FICHIER *f2;
	FICHIER *f3;
	char c,chaine[100];;

	if (argc != 3){
		printf("OK");
		exit(-1);
	}

	printf("/*************************/\n");
	printf("Test généralisé : tout les comportements seront testés\n");
	printf("/*************************/\n");

	printf("\n\n Etape 1 : afficher le contenu du premier fichier passé en paramètre par lecture de blocs de 1 octets et écrit aussi son contenu dans le fichier passé en deuxième paramètre\n\n");
	printf("Resultat attendu : Bonjour, ceci est le test de l'étape 1 !\n");
	printf("Resultat obtenu : ");
	
	f1 = ouvrir (argv[1], 'L');
	f3 = ouvrir (argv[2], 'W');
	if (f1 == NULL){
		exit (-1);
	}
	if (f3 == NULL){
		exit (-1);
	}
	
	while (lire (&c, 1, 1, f1) == 1) {
		printf("%c",c);
		ecrire (&c, 1, 1, f3);
	}
	printf("\n");

	fermer (f1);
	fermer (f3);

	printf("\n\n Etape 2 : afficher le contenu du deuxieme fichier en paramètre, là où nous avons effectué la copie\n\n");
	printf("Resultat attendu : Bonjour, ceci est le test de l'étape 1 !\n");
	printf("Resultat obtenu : ");

	f2 = ouvrir (argv[2], 'L');
	if (f2 == NULL){
		exit (-1);
	}
	while (lire (&chaine, 100, 1, f2) >0) {
		printf("%s",chaine);
	}
	printf("\n");

	fermer (f2);

	printf("\n\n Etape 3: tests sur des formats\n\n");
	printf("Resultat attendu : Bonjour, ceci est le test de l'étape 1 !\n");
	printf("Resultat obtenu : ");
	
	return 0;
}
