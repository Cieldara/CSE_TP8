#include "stdes.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

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
	int ret;
	if(f->mode == 'W' || f->mode == 'E' || f->mode == 'w' || f->mode == 'e'){
		write(f->fd, f->buffer, f->buffer_index);
	}
	ret = close(f->fd);
	free(f);
	return ret;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
	unsigned int has_to_read = 1;
	unsigned int nb_octets = taille*nbelem;
	unsigned int octets_lus = 0;
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
	unsigned int nb_octets = taille*nbelem;
	unsigned int octets_ecrits = 0;
	while (taille*nbelem != octets_ecrits){

		if (f->buffer_index == MAXSIZE){
			f->buffer_size = write(f->fd, f->buffer, MAXSIZE);
			f->buffer_index = 0;
		}
		if (taille*nbelem - octets_ecrits > MAXSIZE - f->buffer_index)
			nb_octets = MAXSIZE - f->buffer_index;
		else
			nb_octets = taille*nbelem - octets_ecrits;
		memcpy(f->buffer+f->buffer_index, (const void*)((const char*)p+octets_ecrits), nb_octets);
		f->buffer_index = f->buffer_index + nb_octets;
		octets_ecrits += nb_octets;
	}
	return octets_ecrits;
}

char* itoa (int i){
	static char str[21];
	char *ret = str + 20;
	if (i >= 0) {
		do {
			*--ret = '0' + (i % 10);
			i /= 10;
		} while (i != 0);
	} else {
		do {
			*--ret = '0' - (i % 10);
			i /= 10;
		} while (i != 0);
		*--ret = '-';
	}
	return ret;
}

int fecriref (FICHIER *fp, char *format, ...){
	va_list list;
	int i, nbChar;
	char *tmp, buf[1];

	va_start(list, format);
	for (i=0, nbChar=0; format[i] && nbChar!=-1; i++){
		if (format[i] == '%'){
			switch (format[i+1]){
				case 's':
				tmp = va_arg(list,char*);
				ecrire(tmp, sizeof(char), sizeof(tmp)/sizeof(char), fp);
				nbChar+=(sizeof(tmp)/sizeof(char));
				break;
				case 'c':
				buf[0] = va_arg(list,int);
				ecrire(buf, sizeof(char), 1, fp);
				nbChar++;
				break;
				case 'd':
				tmp = itoa(va_arg(list,int));
				ecrire(tmp, sizeof(char), sizeof(tmp)/sizeof(char), fp);
				nbChar+=(sizeof(tmp)/sizeof(char));
				break;
				case '%':
				ecrire((const void*)'%', sizeof(char), 1, fp);
				nbChar++;
				break;
				default:
				nbChar=-1;
			}
			i++;
		} else {
			ecrire(&format[i], sizeof(char), 1, fp);
			nbChar++;
		}
	}
	va_end(list);
	return nbChar;
}

int fliref (FICHIER *fp, char *format, ...){
	return -1;
}
