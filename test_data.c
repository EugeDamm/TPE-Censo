#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INICIAL 0
#define ID 1
#define DEPTO 3
#define PROVS 4
#define ERROR 5
#define TRUE 111
#define FALSE 100


/*
*	CREAR UNA STRUCT CON CANT HAB + LISTA DE PROV (+ LIST DE DEPTO) + 
*/

typedef struct deptoCDT{
	char ** departamento;
	struct deptoCDT * next;
}deptoCDT;

typedef struct datosCDT{
	int cantidad_habitantes; //en el pais
	char * condicion;
	unsigned long * id_hogar; //es irrelevante
	struct deptoCDT * provincias[NRO_PROVINCIAS];
}tData;

typedef struct datosCDT * datosADT;

datosADT newData(){
	datosADT new = malloc(sizeof(*new));
	new->condicion = NULL;
	new->id_hogar = NULL;
	new->departamento = NULL;
	new->provincia = NULL;
	return new;
}

void addData(datosADT d, char * cdc, unsigned long * id, char ** dpto, char ** prv, int dim){
	d->cantidad_habitantes = dim;
	d->condicion = realloc(d->condicion, d->cantidad_habitantes * sizeof(d->condicion[0]));
	d->id_hogar = realloc(d->id_hogar, d->cantidad_habitantes * sizeof(d->id_hogar[0]));
	for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		d->condicion[i] = cdc[i];
	}
	for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		d->id_hogar[i] = id[i];
	}
	d->departamento = realloc(d->departamento, d->cantidad_habitantes * sizeof(d->departamento[0]));
	for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		d->departamento[i] = malloc(strlen(dpto[i])-1);
		strcpy(d->departamento[i], dpto[i]);
	}
	d->provincia = realloc(d->provincia, d->cantidad_habitantes * sizeof(d->provincia[0]));
	for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		d->provincia[i] = malloc(strlen(prv[i])-1);
		strcpy(d->provincia[i], prv[i]);
	}
	return;
}

void freeData(datosADT d){
	free(d->id_hogar);
	free(d->condicion);
	for(int i = 0 ; i < d->cantidad_habitantes ; i++){
	free(d->departamento[i]);
	}
	for(int i = 0 ; i < d->cantidad_habitantes ; i++){
	free(d->provincia[i]);
	}
	free(d);
	return;
}

void printData(datosADT d){
	if(d){
		printf("Cantidad de habitantes: %d\n",d->cantidad_habitantes );
		printf("Condiciones:\n");
		for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		printf("%c\n",d->condicion[i]);
		}
		printf("\nIdentificaciones:\n");
		for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		printf("%lu\n",d->id_hogar[i]);
		}
		printf("\nDepartamentos:\n");
		for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		printf("%s\n",d->departamento[i]);
		}
		printf("\nProvincias:\n");
		for(int i = 0 ; i < d->cantidad_habitantes ; i++){
		printf("%s\n",d->provincia[i]);
		}
		printf("\n");
	}
	return;
}


void writeProvincia(datosADT d, FILE * output){
	if(d){
		//ordenaAlfabeticamente(d->provincia, d->cantidad_habitantes);
		for(int i = 0 ; i < d->cantidad_habitantes ; i++){
			fwrite(d->provincia[i], 1, strlen(d->provincia[i]), output);
		}
	}
	return;
}

void writeDepartamento(datosADT d, FILE * output){
	if(d){
		for(int i = 0 ; i < d->cantidad_habitantes ; i++){
			fwrite(d->departamento[i], 1, strlen(d->departamento[i]), output);
			fprintf(output, ", ");
		}
	}
	return;
}

void writePais(datosADT d, FILE * output){
	if(d){
		int ocupado = 0, desocupado = 0;
		float indice;
		for(int i = 0 ; i < d->cantidad_habitantes ; i++){
			printf("condicion[%d]:%c\n",i,d->condicion[i] );
			if((d->condicion[i]-'0') == 1) //ocupado
				ocupado++;
			if((d->condicion[i]-'0') == 2) //desocupado
				desocupado++;
		}
		printf("ocupado: %d y desocupado: %d\n",ocupado, desocupado );
		if(desocupado != 0)
		{
			indice = (float)(desocupado / (float)(desocupado + ocupado));
			fprintf(output,"indice: %.2f, ",indice );
			
		}
	fprintf(output,"cantidad habitantes: %d",d->cantidad_habitantes);
	}
	return;
}

int main(){
	FILE * Pais, * Provincia, * Departamento;
	datosADT d = newData();
	int c, k = 0, m = 0, a = 0, b = 0, e = 0, f = 0, estado = INICIAL, flag = 1;
	unsigned long idnro = 0;
	int dim_dpto = 0, dim_prv = 0, dim = 0;
	char * cdc = NULL;
	unsigned long * id = NULL;
	char ** dpto = NULL;
	char ** prv = NULL;
	char * dpto_ind = NULL;
	char * prv_ind = NULL;
	int prov_bool = FALSE;
	//creo el o.txt donde quiero depositar mis datos
	while( (c = getchar()) != EOF ){
		switch(estado){
			case INICIAL:
										if(isdigit(c)){//condicion
											dim++;
											cdc = realloc(cdc, dim * sizeof(cdc[0]));
											cdc[a++] = c;
											break;
										}
										if(c == ','){
											estado = ID;
											break;
										}
										else{
											printf("hay un %i\n",c);
											estado = ERROR;
											break;
										}
			case ID:
										if(c == ','){
											id = realloc(id, dim * sizeof(id[0]));
											id[b++] = idnro;
											estado = DEPTO;
											idnro = 0;
											break;
										}
										if(isdigit(c)){
											idnro = idnro * 10 + c - '0';
											break;
										}
										else{
											estado = ERROR;
											break;
										}
			case DEPTO:
										if(isalpha(c) || c == ' '){
											dim_dpto++;
											dpto_ind = realloc(dpto_ind, dim_dpto * sizeof(dpto_ind[0]));
											dpto_ind[k++] = c;
											//printf("formacion dpto_ind: %s\n",dpto_ind );

											break;
										}
										if(c == ','){
											dpto = realloc(dpto, dim * sizeof(dpto[0]));
											dpto[f] = malloc(strlen(dpto_ind)-1);
											strcpy(dpto[f++], dpto_ind);
											estado = PROVS;
											dim_dpto = 0;
											k = 0;
											dpto_ind = NULL;
											prov_bool = FALSE;
											break;
										}										
										else{
											estado = ERROR;
											break;
										}		
			case PROVS:	
										if(isalpha(c) || c == ' '){//creo la palabra
											prov_bool = TRUE;
											dim_prv++;
											prv_ind = realloc(prv_ind, dim_prv * sizeof(prv_ind[0]));
											prv_ind[m++] = c;
										//	printf("formacion prv_ind: %s\n",prv_ind );
											break;
										}
										if(!isalpha(c) || c != '\n'){//otro ingreso
											prov_bool = FALSE;
											prv = realloc(prv, dim * sizeof(prv[0]));
											prv[e] = malloc(strlen(prv_ind)-1);
											strcpy(prv[e++], prv_ind);
											estado = INICIAL;
											dim_prv = 0;
											m = 0;
											prv_ind = NULL;
											break;
										}
										else{
											estado = INICIAL;
											break;
										}	
		case ERROR:
										if(flag){
											flag = 0;
											printf("Error\n");
											
										}
										break;														
		}
	}
	if(prov_bool == TRUE){//agrego lo ultimo que hubo
		prv = realloc(prv, dim * sizeof(prv[0]));
		prv[e] = malloc(strlen(prv_ind)-1);
		strcpy(prv[e++], prv_ind);
	}
	addData(d, cdc, id, dpto, prv, dim);
	printData(d);
	Pais = fopen("/Users/eugedamm/Desktop/ITBA/PI/TPE/out/pais.csv", "w");
	Departamento = fopen("/Users/eugedamm/Desktop/ITBA/PI/TPE/out/departamento.csv", "w");
	Provincia = fopen("/Users/eugedamm/Desktop/ITBA/PI/TPE/out/provincia.csv", "w");
	writePais(d, Pais);
	writeProvincia(d, Provincia);
	writeDepartamento(d, Departamento);
	freeData(d);
	fclose(Pais);
	fclose(Departamento);
	fclose(Provincia);
	return 0;
}
