#include "CensoADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INICIAL 0
#define ID 1
#define DEPTO 3
#define PROV 4
#define ERROR 5

int leerArchivos(FILE * fp, int * ocupacion, unsigned long * id, char * departamento, char * provincia){
	int c, k = 0, m = 0;
	int dimd = 0, dimp = 0;
	int estado = INICIAL, ultimo = 0;
	int termino = 0, cant = 0;
	//while(!termino){	
			c = getc(fp);
			switch(estado){
				case INICIAL:
										if(c - '0' == 0 || c - '0' == 1 || c - '0' == 2 || c - '0' == 3){ //ocupacion
										ultimo = 0;
										*ocupacion = c - '0';
										printf("ocup:%d\n",*ocupacion );
										cant++;
										break;
										}
										if(c == ','){
											estado = ID;
											*id = 0;
											break;
										}
										if((int)c < 0 || (int)c > 127){
											break;
										}
										else{
											estado = ERROR;
											break;
										}
				case ID:
										if((int)c < 0 || (int)c > 127){
											break;
										}
										if(isdigit(c)){
											*id = (*id) * 10 + c - '0';
											break;
										}
										if(c == ','){ //termino el id
											estado = DEPTO;
											cant++;
											printf("id: %lu\n",*id );
											break;	
										}
										else{
											estado = ERROR;
											break;
										}
				case DEPTO:
										if((int)c >= 32 && (int)c <= 127 && c != ','){
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
											printf("depto:%s\n",departamento );
											k = 0;
											cant++;
											break;
										}
										else{
											estado = ERROR;
											break;
										}
				case PROV:		
										if(c == '\n' || (int)c == 13){//nuevo ingreso, nuevo habitante
											dimp++;
											provincia = realloc(provincia, dimp * sizeof(provincia[0]));
											provincia[m] = '\0';
											m = 0;
											ultimo = 1;
											provincia = NULL;
											departamento = NULL;
											estado = INICIAL;
											//termino = 1;
											cant++;
											break;	
										}
										if((int)c >= 32 && (int)c <= 127 && c != '\n'){	
											dimp++;
											provincia = realloc(provincia, dimp * sizeof(provincia[0]));
											provincia[m++] = c;
											break;
										}
										else{
											estado = ERROR;
											break;
										}
				case ERROR:
										if(c == '\n' || (int)c == 13){//termino
											estado = INICIAL;
											m = 0;
											k = 0;
											provincia = NULL;
											departamento = NULL;
											cant = -1;
										}
										break;
			}
		//}
		if(ultimo == 1){
			dimp++;
			provincia = realloc(provincia, dimp * sizeof(provincia[0]));
			provincia[m] = '\0';
			printf("prov:%s\n",provincia);
		}
		return cant;
}