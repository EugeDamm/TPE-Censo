#include "CensoADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _censo_h
#define _censo_h


int
main(void){
    PaisADT Argentina=newPais();
    FILE * archEntrada=fopen("prueba.txt","r");
    
    if(archEntrada==NULL){
        printf("No se pudo leer el archivo.\n");
        return 1;
    }
    int ocupacion;
    unsigned long codigoCasa;
    char departamento[70];
    char provincia [70];
    while(!feof(archEntrada)){
        if(fscanf(archEntrada,"%d,%lu,%[a-zA-Z],%[^\n]",&ocupacion,&codigoCasa,departamento,provincia)==4){
            addProvincia(Argentina, provincia,departamento, ocupacion);
            }
    }
    fclose(archEntrada);

    	FILE * Pais=fopen("Pais.csv","w+");
	CargarPais(Pais,Argentina);
    	fclose(Pais);


	FILE * Provincia=fopen("Provincia.csv","w+");
	CargarProvincia(Provincia, Argentina);
	fclose(Provincia);

	FILE * Departamento=fopen("Departamento.csv","w+");
	CargarDepartamento(Departamento, Argentina);
	fclose(Departamento);
	

	return 0;
}

#endif
