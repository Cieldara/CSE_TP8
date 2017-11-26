#include <unistd.h>
#include <stdlib.h>
#include "stdes.h"
#include <stdio.h>

int main (int argc, char **argv)
{
  FICHIER *f1, *f2;
  int n;
  if (argc != 3) exit (-1);

  f1 = ouvrir (argv[1], 'E');
  if (f1 == NULL) exit (-1);

  n = fecriref (f1, "Test char: '%c' and string: '%s' with normal number 12\n", 'a', "bonjour");
  fecriref (f1, "Test number: '%d' char written on the above line\n", n);

  for (n=-11;n<11;n++)
    fecriref (f1, "%d ", n);
  fecriref (f1, "\n", n);

#if 0
  /* Error, as expected: */
  fecriref (f1, "Num: '%e'\n");
#endif

  fermer (f1);

  {
    char a,b,c;
    int d, second, first, res;
    char my_word[128], de[500], numero[500];
    f2 = ouvrir (argv[2], 'L');
    /*fliref (f2, "  test  %c end %s", &c, my_word);
    ecriref ("Read '%c' and '%s' from %s\n", c, my_word, argv[2]);
    fliref (f2, "end %d %s", &d, my_word);
    ecriref ("Now read '%d' and '%s' from %s\n", d, my_word, argv[2]);*/
    res = fliref(f2, "test %d %s lecture %s %d", &first, de, numero, &second);
    printf("res='%d' first='%d', de='%s', numero='%s', second='%d'\n",res, first, de, numero, second);

    fermer (f2);
  }
  return 0;
}
