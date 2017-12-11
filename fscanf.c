#include "CensoADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _censo_h
#define _censo_h

int main(){
	//PaisADT paisNuevo = newPais();
	FILE * fp = stdin;
	int ocupacion, c, k = 0, m = 0;
	unsigned long id;
	char  * departamento = NULL;
	char  * provincia = NULL;
	int dimd = 0, dimp = 0;
	/*while((c = getchar()) != EOF){
		switch(estado){
				case INCIAL:
										if(isdigit(c))
		}
	}*/
	while(!feof(fp)){
		fscanf(fp,"%d,%lu,",&ocupacion,&id);
		while((c = fgetc(fp)) != ','){
				dimd++;
				departamento = realloc(departamento, dimd * sizeof(departamento[0]));
				departamento[k++] = c;
		}
		while((c = fgetc(fp)) != '\n'){
				dimp++;
				provincia = realloc(provincia, dimp * sizeof(provincia[0]));
				provincia[m++] = c;
		}
	printf("ocupacion: %i\n",ocupacion);
	printf("id: %lu\n",id);
	printf("departamento: %s\n",departamento);
	printf("provincia: %s\n",provincia);
	//add
	dimd = 0;
	dimp = 0;
	provincia = NULL;
	departamento = NULL;
	k = 0;
	m = 0;
	}
	return 0;
}

#endif