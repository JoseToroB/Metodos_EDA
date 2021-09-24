#include <stdio.h>
#include <stdlib.h>
//TDA DE LISTA DE VACUNAS
/*------------- estructura de datos -------------*/
typedef struct nodoV
{
  int IDV;
  char* codigoV;
  char* nombreV;
  int semanasV;
  int dosisNecesarias;
  struct nodoV* siguiente;
}nodoV;

typedef struct listaV
{
  nodoV* inicio;
}listaV;

/*------------- operaciones -------------*/

//crea una lista de vacunas
listaV* crearListaVaciaV()
{
  listaV* lista=(listaV*)malloc(sizeof(listaV));
  lista->inicio=NULL;
  return lista;
}
//revisa si una lista de vacunas es vacia
int esListaVaciaV(listaV* lista)
{
  if (lista->inicio == NULL)
    return 1;
  else
    return 0;
}
//recorre una lista de vacunas y printea la info en sus nodos
void recorrerListaV(listaV* lista)
{
  if (!esListaVaciaV(lista))
  {
    nodoV* a=lista->inicio;
    while (a!=NULL)
    {
      printf("%d %s %s %d\n",a->IDV,a->codigoV,a->nombreV,a->semanasV);
	  
      a=a->siguiente;
    }
    printf("\n");
  }
  else
    printf("lista vacia\n");
}
//funcion que calcula el largo de una lista de vacunas
int largoListaV(listaV* lista){
	int contador=0;
	nodoV* actual=lista->inicio;
	if(esListaVaciaV(lista)==1){
		return contador;
	}
	else if(actual->siguiente == NULL){
		return 1;
	}
	else{
		while(actual->siguiente != NULL ){
			actual=actual->siguiente;
			contador++;
		}
		return contador;
	}
}
//inserta un nodo vacuna al inicio de una lista
void insertarInicioV(listaV* lista, int ID, char codigo[20], char nombre[25], int semanas){
	nodoV* nuevo=(nodoV*)malloc(sizeof(nodoV));
	nuevo->IDV=ID;
	nuevo->codigoV=codigo;
	nuevo->nombreV=nombre;
	nuevo->semanasV=semanas;
	nuevo->siguiente = lista->inicio;
	lista->inicio=nuevo;
}
//inserta un nodo vacuna al final de una lista
void insertarnodoVFinalV(listaV* lista, int ID, char codigo[20], char nombre[25], int semanas){
	nodoV* nuevo=(nodoV*)malloc(sizeof(nodoV));
	nuevo->IDV=ID;
	nuevo->codigoV=codigo;
	nuevo->nombreV=nombre;
	nuevo->semanasV=semanas;
	nuevo->siguiente=NULL;
	if(esListaVaciaV(lista)==1){//si esta vacia se inserta al inicio
		insertarInicioV(lista,ID,codigo,nombre,semanas);
	}
	else{
		nodoV* actual=lista->inicio;
		while(actual->siguiente != NULL ){
			actual=actual->siguiente;
		}
		actual->siguiente=nuevo;
	}
}
//libera una lista de vacunas
void liberarListaV(listaV* lista){
	if(!esListaVaciaV(lista)){
		nodoV* auxiliar;
		auxiliar = lista->inicio;
		while(auxiliar!=NULL){
			lista->inicio = lista->inicio->siguiente;
			free(auxiliar);
			auxiliar = lista->inicio;
		}
	}
}
//entrega el codigo segun la id de una vacuna
char* vacunaCodigo(int id,listaV* lista){
	nodoV* actual;
	actual=lista->inicio;
	while(actual!=NULL){
		if(actual->IDV==id){
			return actual->codigoV;
		}
		actual=actual->siguiente;
	}
	return "Vacuna no registrada";
}
//lee un archivo y genera la lista vacunas
void leerVacunas(listaV* listaV){
  int cantidadV;
  int i;
  int IDV;
  int semanasV;
  FILE * archivoV = fopen("vacunas.in", "r");
  fscanf(archivoV,"%d",&cantidadV);
  for(i=0;i<cantidadV;i++){
    char* codigoV=(char*)malloc(sizeof(char)*25);
    char* nombreV=(char*)malloc(sizeof(char)*25);
    fscanf(archivoV,"%d %s %s %d\n",&IDV,codigoV,nombreV,&semanasV);
		insertarnodoVFinalV(listaV,IDV,codigoV,nombreV,semanasV);
	}
  //cierro archivo
  fclose(archivoV);
}
//busca un nodo vacuna en una lista
nodoV* buscarVacuna(listaV* entrada,int id){
	nodoV* nodoActual;
	nodoActual =entrada->inicio;
	while(nodoActual!=NULL){
		if(nodoActual->IDV==id){
			return nodoActual;
		}
		nodoActual=nodoActual->siguiente;
	}
	return NULL;
}