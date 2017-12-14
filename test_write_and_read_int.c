#include "stdes.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	FICHIER *f1;
	FICHIER *f2;
	int n, nb;
	if (argc != 2){
		printf("1 argument est attendu : <nom_fichier1>\nOn écrit dans le fichier des entiers de 0 à 100\n");
		exit(-1);
	}
	printf("\n\n/*************************/\n");
	printf("Ecriture dans le fichier %s des valeurs de 0 à 100 puis lecture dans ce même fichier de ces entiers\n",argv[1]);
	printf("/*************************/\n\n");
	f1 = ouvrir (argv[1], 'W');

	for (n=-11;n<101;n++){
		fecriref (f1, "%d ", n);
	}
	fecriref (f1, "\n", n);
	fermer (f1);

	printf("\n\n/*************************/\n");
	printf("On lit dans le fichier maintenant :\n");
	printf("/*************************/\n\n");

	
	f2 = ouvrir (argv[1], 'R');
	for (n=-11;n<101;n++){
		fliref(f2, "%d ",&nb);
		printf("%d ",nb);
	}
	fermer (f2);
	
	return 0;
}
