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
	unsigned int index = 0;
	
	while (has_to_read){
		if (f->buffer_index == 0)
			f->buffer_size = read(f->fd, f->buffer, MAXSIZE);
		if (taille*nbelem - octets_lus > f->buffer_size-f->buffer_index)
			nb_octets = f->buffer_size-f->buffer_index;
		else
			nb_octets = taille*nbelem - octets_lus;
		memcpy((char*)p+index, f->buffer+f->buffer_index, nb_octets);
		index+=nb_octets;
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
	char str[9];
	int nb;

	va_start(list, format);
	for (i=0, nbChar=0; format[i] && nbChar!=-1; i++){
		if (format[i] == '%'){
			switch (format[i+1]){
				case 's':
				tmp = va_arg(list,char*);
				ecrire(tmp, sizeof(char), strlen(tmp), fp);
				nbChar+=(sizeof(tmp)/sizeof(char));
				break;
				case 'c':
				buf[0] = va_arg(list,int);
				ecrire(buf, sizeof(char), 1, fp);
				nbChar++;
				break;
				case 'd':
				
				nb = va_arg(list,int);
				sprintf(str,"%d",nb);
				ecrire(str, sizeof(char),strlen(str), fp);
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
	va_list list;
	unsigned int i, j;
	int nbElem;
	int *tmpInt;
	char *tmpString, buf[1], str[21];

	va_start(list, format);
	for (i=0, nbElem=0; format[i] && nbElem!=-1; i++){
		if (format[i] == '%'){
			switch (format[i+1]){
				case 's':
				tmpString = va_arg(list,char*);
				j=0;
				while(lire(buf, sizeof(char), 1, fp) != -1
						&& buf[0] != ' ' && buf[0] != '\n'
						&& buf[0] != '\0' && buf[0] != '\r')
					tmpString[j++]=buf[0];
				tmpString[j]='\0';
				nbElem++;
				i++;
				break;
				case 'c':
				tmpString = (char*)va_arg(list,int*);
				lire(tmpString, sizeof(char), 1, fp);
				nbElem++;
				break;
				case 'd':
				tmpInt = (int*)va_arg(list,int*);
				j=0;

				while((lire(buf, sizeof(char), 1, fp) != -1 && buf[0] > 47
						&& buf[0] < 58 && sizeof(str) > j) || buf[0] == '-')
							str[j++] = buf[0];
				str[j]='\0';
				*tmpInt = atoi(str);
				nbElem++;
				i++;
				break;
				case '%':
				if (lire(buf, sizeof(char), 1, fp) == -1 || buf[0] != '%'){
					nbElem=-1;
				}
				break;
				default:
				nbElem=-1;
			}
			i++;
		} else {
			if (lire(buf, sizeof(char), 1, fp) == -1 || buf[0] != format[i]){
				nbElem =-1;
			}
		}
	}
	va_end(list);
	return nbElem;;
}
