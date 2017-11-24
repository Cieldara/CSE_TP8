#ifndef _STDES_H
#define _STDES_H
#define MAXSIZE 10	

//struct _ES_FICHIER;
//typedef struct _ES_FICHIER FICHIER;
typedef struct {
	char buffer[MAXSIZE];
	char mode;
	unsigned int buffer_index;
	unsigned int buffer_size;
	int fd;
	unsigned int file_index;
	
} FICHIER;

FICHIER *ouvrir(char *nom, char mode);
int fermer(FICHIER*f);
int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f);
int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f);

#endif

