#include "stdes.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	FICHIER *f1;
	FICHIER *f2;
	char c1[500], c2[500],c3[500];
	if (argc != 2){
		printf("1 argument est attendu : <nom_fichier1>\nOn écrit dans le fichier 3 chaines de caracteres, puis on les lit\n");
		exit(-1);
	}
	printf("\n\n/*************************/\n");
	printf("Ecriture dans le fichier %s 3 chaines de caracteres\n",argv[1]);
	printf("/*************************/\n\n");
	f1 = ouvrir (argv[1], 'W');

	fecriref (f1, "%s %s %s ", "bonjour","salut","aurevoir");
	fecriref (f1, "\n");
	fermer (f1);

	printf("\n\n/*************************/\n");
	printf("On lit dans le fichier maintenant :\n");
	printf("/*************************/\n\n");

	
	f2 = ouvrir (argv[1], 'R');
	fliref(f2, "%s %s %s ",&c1,&c2,&c3);
	printf("%s\n",c1);
	printf("%s\n",c2);
	printf("%s\n",c3);
	fermer (f2);
	
	return 0;
}
