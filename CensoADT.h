#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef censoADT_h

#define censoADT_h

typedef struct DepartamentoCDT * DepartamentoADT;
typedef struct ProvinciaCDT * ProvinciaADT;
typedef struct PaisCDT * PaisADT;



struct PaisCDT * newPais(); //Crea un nuevo pais, que no contiene provincias, habitantes y su numero de desempleados es 0 y de empleados es 0;

void addProvincia(PaisADT pais, char * provincia, char * departamento, int estado); /*Crea una nueva Provincia (si esta no esta en el Pais), 
aumenta el numero de habitantes, desempleados y empleados en el pais; */

ProvinciaADT addProvinciaRec(ProvinciaADT primerProvincia, char * nombre, char * departamento, int estado); /*Agrega de manera recursiva una provincia,
en el caso de que no exista la crea, si ya existe modifica los valores de esta provincia (cantidad de personas, empleados y desempleados); */

DepartamentoADT addDepartamento(DepartamentoADT primerDepartamento,char * departamento, int estado); /*Agrega de manera recursiva un departamento,
en el caso que no exista lo crea, si existe modificasus los valores (cantidad de personas, cantidad de empleados y de desempleados); */

float Desocupacion(int conempleo, int desempleo); //Con los parametros de personas ocupadas y de personas desocupadas genera el indice de desempleo;

void changeEmpleoProv(ProvinciaADT provincia, int estado); //Modifica los parametros de desempleo y conempleo de la provincia recien "creada";

void changeEmpleoDep(DepartamentoADT departamento, int estado); //Modifica los paramentros de desempleo y conempleo de el departamento recien "creado";

void CargarPais(FILE * Paiscvs,PaisADT Pais); /* Carga en el archivo el pais 
con las caracteristicas solicitadas */

void CargarProvincia(FILE * Provinciacvs,PaisADT Pais); /*Carga en el archivo la provincia 
con las caracteristicas solicitadas */

void CargarDepartamento(FILE * Departamentocvs, PaisADT Pais); /*Carga en el archivo el departamento 
con las caracteristicas solicitadas*/

void FreePais(PaisADT pais); /*Borra por completo un pais */

#endif

