#include "stdes.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

FICHIER *ouvrir(char *nom, char mode){
	FICHIER * file = malloc(sizeof(FICHIER));
	int fd = -1;
	if(mode == 'W' || mode == 'E' || mode == 'w' || mode == 'e'){
		fd = open(nom,O_WRONLY);
	}
	else if(mode == 'L' || mode == 'R' || mode == 'l' || mode == 'r'){
		fd = open(nom,O_RDONLY);
	}

	if(fd != -1){
		file->fd = fd;
		file->mode = mode;
		file->file_index = 0;
		file->buffer_index = 0;
		file->buffer_size = 0;
	} else {
		file = NULL;
	}
	
	return file;
}

int fermer(FICHIER*f){
	if(f->mode == 'W' || f->mode == 'E' || f->mode == 'w' || f->mode == 'e'){
		printf("OKOKOK");
		write(f->fd, f->buffer, f->buffer_index);
	}
	int ret = close(f->fd);
	free(f);
	return ret;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
	int has_to_read = 1;
	int nb_octets = taille*nbelem;
	int octets_lus = 0;
	while (has_to_read){
		if (f->buffer_index == 0)
			f->buffer_size = read(f->fd, f->buffer, MAXSIZE);
		if (taille*nbelem - octets_lus > f->buffer_size-f->buffer_index)
			nb_octets = f->buffer_size-f->buffer_index;
		else
			nb_octets = taille*nbelem - octets_lus;
		memcpy(p, f->buffer+f->buffer_index, nb_octets);
		f->buffer_index = f->buffer_index + nb_octets;
		if (f->buffer_index >= f->buffer_size)
			f->buffer_index = 0;
		octets_lus += nb_octets;
		if (taille*nbelem == octets_lus || f->buffer_size < MAXSIZE)
			has_to_read = 0;
	}
	return octets_lus;
}

int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
	int nb_octets = taille*nbelem;
	int octets_ecrits = 0;
	while (taille*nbelem != octets_ecrits){
		if (f->buffer_index == MAXSIZE){
			f->buffer_size = write(f->fd, f->buffer, MAXSIZE);
			f->buffer_index = 0;
		}
		if (taille*nbelem - octets_ecrits > MAXSIZE - f->buffer_index)
			nb_octets = MAXSIZE - f->buffer_index;
		else
			nb_octets = taille*nbelem - octets_ecrits;
		memcpy(f->buffer+f->buffer_index, p + octets_ecrits, nb_octets);
		f->buffer_index = f->buffer_index + nb_octets;
		octets_ecrits += nb_octets;
	}
	return octets_ecrits;
}
