#include "CensoADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maquinaParaProbar.h"
#ifndef _censo_h
#define _censo_h


int
main(void){
	//PaisADT Argentina=newPais();
	FILE * archEntrada = stdin;
	
	if(archEntrada == NULL){
		printf("No se pudo leer el archivo.\n");
		return 1;
	}
	int ocupacion = 0;
	unsigned long codigoCasa = 0;
	char * departamento = NULL;
	char * provincia = NULL;
	while(!feof(archEntrada)){
		if(leerArchivos(archEntrada,&ocupacion,&codigoCasa,departamento,provincia)==4){
			//addProvincia(Argentina, provincia,departamento, ocupacion);
			printf("anduvo bien\n");
		}
		else{
			printf("anduvo mal\n");
		}
	}
	/*fclose(archEntrada);

	FILE * Pais=fopen("Pais.csv","w+");
	CargarPais(Pais,Argentina);
	fclose(Pais);

	FILE * Provincia=fopen("Provincia.csv","w+");
	CargarProvincia(Provincia, Argentina);
	fclose(Provincia);

	FILE * Departamento=fopen("Departamento.csv","w+");
	CargarDepartamento(Departamento, Argentina);
	fclose(Departamento);
	
	FreePais(Argentina);
	*/
	return 0;
}

#endif
