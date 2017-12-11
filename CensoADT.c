#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CensoADT.h"

typedef struct DepartamentoCDT{
	char * nombre;
	int cantPersonas;
	int desempleo;
	int conempleo;
	struct DepartamentoCDT * tail;
}DepartamentoCDT;


typedef struct ProvinciaCDT{
	char * nombre;
	int cantPersonas;
	int conempleo;
	int desempleo;
	struct DepartamentoCDT * primerDepartamento;
	struct ProvinciaCDT * tail;
}ProvinciaCDT;

typedef struct PaisCDT{
	int habitantes;
	int desempleo;
	int conempleo;
	struct ProvinciaCDT * primerProvincia;
}PaisCDT;




struct PaisCDT * 
newPais(){
	PaisADT aux=malloc(sizeof(*aux));
	if(aux!=NULL){
		ProvinciaADT aux2=malloc(sizeof(*aux));
		if(aux2!=NULL){
			aux->habitantes=0;
			aux->desempleo=0;
			aux->conempleo=0;
			aux->primerProvincia=NULL;
			return aux;
			}
		return NULL;
	}
	return NULL;
}

void
addProvincia(PaisADT pais, char * provincia, char * departamento, int estado){
	pais->habitantes++;
	if(estado==2){
		pais->desempleo++;
	}
	if(estado==1){
		pais->conempleo++;
	}
	pais->primerProvincia=addProvinciaRec(pais->primerProvincia, provincia, departamento, estado);
}


ProvinciaADT
addProvinciaRec(ProvinciaADT primerProvincia, char * nombre, char * departamento, int estado){
	if(primerProvincia==NULL || strcmp(primerProvincia->nombre,nombre)>0){
		ProvinciaADT aux=malloc(sizeof(*aux));
		if(aux!=NULL){
			aux->nombre=malloc(strlen(nombre));
			if(aux->nombre!=NULL){
				strcpy(aux->nombre,nombre);
				aux->cantPersonas=1;
				changeEmpleoProv(aux,estado);
				aux->primerDepartamento=NULL; 
				aux->primerDepartamento=addDepartamento(aux->primerDepartamento, departamento, estado);
				return aux;
			}
			return NULL;
		}
		return NULL;
	}else if (strcmp(primerProvincia->nombre,nombre)==0){
		primerProvincia->cantPersonas++;
		if(estado==2){
				primerProvincia->desempleo++;
		}
		if(estado==1){
			primerProvincia->conempleo++;
		}
			primerProvincia->primerDepartamento=addDepartamento(primerProvincia->primerDepartamento, departamento, estado);
			return primerProvincia;
	}

		primerProvincia=addProvinciaRec(primerProvincia->tail, nombre, departamento, estado);
		return primerProvincia;
	
}

DepartamentoADT
addDepartamento(DepartamentoADT primerDepartamento,char * departamento, int estado){
	if(primerDepartamento==NULL || strcmp(primerDepartamento->nombre,departamento)>0){
		DepartamentoADT aux=malloc(sizeof(*aux));
		if(aux!=NULL){
			aux->nombre=malloc(strlen(departamento));
			if(aux->nombre!=NULL){
				strcpy(aux->nombre,departamento);
				aux->cantPersonas=1;
				changeEmpleoDep(aux,estado);
				return aux;
			}
			return NULL;
		}
		return	NULL;
	}else if(strcmp(primerDepartamento->nombre,departamento)==0){
		primerDepartamento->cantPersonas++;
		if(estado==2){
			primerDepartamento->desempleo++;
		}
		if(estado==1){
			primerDepartamento->conempleo++;
		}
		return primerDepartamento;
	}
	primerDepartamento=addDepartamento(primerDepartamento->tail,departamento,estado);
	return primerDepartamento;
}

float
Desocupacion(int conempleo, int desempleo){
	float resp;
	if(conempleo+desempleo==0)
		return 0;
	resp=(desempleo/(((float)conempleo)+desempleo));
	return resp;
}

void
changeEmpleoProv(ProvinciaADT provincia, int estado){
	if(estado==1){
		provincia->conempleo=1;
	}else{
		provincia->conempleo=0;
	}
	if(estado==2){

		provincia->desempleo=1;
	}else{
		provincia->desempleo=0;
	}
}

void
changeEmpleoDep(DepartamentoADT departamento, int estado){
	if(estado==1){
		departamento->conempleo=1;
	}else{
		departamento->conempleo=0;
	}
	if(estado==2){
		departamento->desempleo=1;
	}else{
		departamento->desempleo=0;
	}
}


void
CargarPais(FILE * Paiscvs,PaisADT Pais){
	float desocupacion;
	desocupacion=Desocupacion(Pais->conempleo,Pais->desempleo);
	fprintf(Paiscvs,"%d, %.2f",Pais->habitantes,desocupacion);
}

void
CargarProvincia(FILE * Provinciacvs,PaisADT Pais){
	float desocupacion;
	ProvinciaADT Prov=Pais->primerProvincia;
	while(Prov!=NULL){
		desocupacion=Desocupacion(Prov->conempleo,Prov->desempleo);
		fprintf(Provinciacvs, "%s, %d, %.2f\n",Prov->nombre,Prov->cantPersonas,desocupacion);
		Prov=Prov->tail;
	}
}

void
CargarDepartamento(FILE * Departamentocvs, PaisADT Pais){
	float desocupacion;
	ProvinciaADT Prov=Pais->primerProvincia;
	DepartamentoADT Dept;
	while(Prov!=NULL){
		Dept=Prov->primerDepartamento;
		while(Dept!=NULL){
			desocupacion=Desocupacion(Dept->conempleo,Dept->desempleo);
			fprintf(Departamentocvs, "%s, %s, %d, %.2f\n",Prov->nombre,Dept->nombre,Dept->cantPersonas,desocupacion );
			Dept=Dept->tail;
		}
		Prov=Prov->tail;
	}
}

void
FreePais(PaisADT pais){
	ProvinciaADT Prov=pais->primerProvincia;
	DepartamentoADT Dept=Prov->primerDepartamento;
	while(Prov!=NULL){
		while(Dept!=NULL){
			DepartamentoADT aux;
			aux=Dept->tail;
			free (Dept);
			Dept=aux;
		}
		ProvinciaADT aux2;
		aux2=Prov->tail;
		free(Prov);
		Prov=aux2;
	}
	free(pais);
}
