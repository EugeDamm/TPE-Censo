#include "CensoADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef _censo_h
#define _censo_h

#define INICIAL 0
#define ID 1
#define DEPTO 3
#define PROV 4
#define ERROR 5

int main(){
	//PaisADT paisNuevo = newPais();
	FILE * fp = stdin;
	int ocupacion, c, k = 0, m = 0;
	unsigned long id = 0;
	char  * departamento = NULL;
	char  * provincia = NULL;
	int dimd = 0, dimp = 0;
	int estado = INICIAL, ultimo = 0;
	while(!feof(fp)){
		while((c = fgetc(fp)) != EOF){
			switch(estado){
				case INICIAL:
										if(c - '0' == 0 || c - '0' == 1 || c - '0' == 2 || c - '0' == 3){ //ocupacion
											ultimo = 0;
											ocupacion = c - '0';
											printf("ocupacion: %i\n",ocupacion);
											break;
										}
										if(c == ','){
											estado = ID;
											id = 0;
											break;
										}
										else{
											estado = ERROR;
											break;
										}
				case ID:
										if(isdigit(c)){
											id = id * 10 + c - '0';
											break;
										}
										if(c == ','){ //termino el id
											estado = DEPTO;
											printf("id: %lu\n",id);
											break;	
										}
										else{
											estado = ERROR;
											break;
										}
				case DEPTO:
										if(isalpha(c) || c == ' '){
											dimd++;
											departamento = realloc(departamento, dimd * sizeof(departamento[0]));
											departamento[k++] = c;
											break;
										}
										if(c == ','){ //termino el depto
											dimd++;
											departamento = realloc(departamento, dimd * sizeof(departamento[0]));
											departamento[k] = '\0';
											estado = PROV;
											k = 0;
											printf("departamento: %s\n",departamento);
											break;
										}
										else{
											estado = ERROR;
											break;
										}
				case PROV:
										if(isalpha(c) || c == ' '){
											dimp++;
											provincia = realloc(provincia, dimp * sizeof(provincia[0]));
											provincia[m++] = c;
											break;
										}
										if(c == '\n'){//nuevo ingreso, nuevo habitante
											dimp++;
											provincia = realloc(provincia, dimp * sizeof(provincia[0]));
											provincia[m] = '\0';
											estado = INICIAL;
											m = 0;
											ultimo = 1;
											printf("provincia: %s\n",provincia);
											provincia = NULL;
											departamento = NULL;
											break;	
										}
										else{
											estado = ERROR;
											break;
										}
				case ERROR:
										printf("Error\n");
										break;
			}
		}
		if(ultimo == 0){
			dimp++;
			provincia = realloc(provincia, dimp * sizeof(provincia[0]));
			provincia[m] = '\0';
			printf("provincia: %s\n",provincia);
		}
	}

	return 0;
}

#endif