#include <unistd.h>
#include <stdlib.h>
#include "stdes.h"
#include <stdio.h>

int main (int argc, char **argv)
{
  FICHIER *f1, *f2;
  int n;
  if (argc != 3){
	printf("2 arguments sont attendus : <nom_fichier1> <nom_fichier2>\nDans nom_fichier1 sera écrit une chaîne de caractères formatée complexe et dans nom_fichier2, sera lue.\nCette chaine est générée automatiquement par le Makefile, n'essayez pas de créer une chaîne de ce type, trop complexe\n");
	exit (-1);
  }

  f1 = ouvrir (argv[1], 'E');
  if (f1 == NULL) exit (-1);

  n = fecriref (f1, "Test char: '%c' and string: '%s' with normal number 12\n", 'a', "bonjour");
  fecriref (f1, "Test number: '%d' char written on the above line\n", n);

  for (n=-11;n<11;n++)
    fecriref (f1, "%d ", n);
  fecriref (f1, "\n", n);

  fermer (f1);

  {
    int second, first, res;
    char de[500], numero[500];
    f2 = ouvrir (argv[2], 'L');
    res = fliref(f2, "test %d %s lecture %s %d", &first, de, numero, &second);
    printf("res='%d' first='%d', de='%s', numero='%s', second='%d'\n",res, first, de, numero, second);

    fermer (f2);
  }
  return 0;
}
