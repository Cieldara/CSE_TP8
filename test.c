#include "stdes.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	FICHIER *f1;
	FICHIER *f2;
	char c;

	if (argc != 3){
		
		exit(-1);
	}

	f1 = ouvrir (argv[1], 'L');
	if (f1 == NULL){
		exit (-1);
	}
	f2 = ouvrir (argv[2], 'E');
	if (f2 == NULL){
		exit (-1);
	}
	while (lire (&c, 1, 1, f1) == 1) {
		ecrire (&c, 1, 1, f2);
	}
	printf("\n");
	fermer (f1);
	fermer (f2);

	printf("\n\n/*************************/\n");
	printf("Affichage (via cat) du fichier %s qui est la copie du fichier %s\n",argv[2],argv[1]);
	printf("/*************************/\n\n");

	return 0;
}
