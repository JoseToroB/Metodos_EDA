#include <stdio.h>
#include <stdlib.h>
#include "listaV.h"
#include "listaG.h"
#include <time.h>
void salidaLAUX(listaG* listaGente1D,listaV* listaVacunas);
void segundaDosis(nodoG* nodo,listaV* vacunas);
void calcularSegundaDosis(listaG* lista,listaV* vacunas);
void salidaVacunacionCompleta(listaG* vc,listaV* vacunas,listaG* dosis2);
void calcularProvisiones(listaG* v1d,listaV* vacunas);
void salidaListado(listaG* v1d,listaV* vacunas);
int main()
{
  //creo la lista de vacunas
  listaV * listaVacunas=crearListaVaciaV();
  leerVacunas(listaVacunas);//lista vacunas

  //creo las listas para vacunados con 1 y 2 dosis y una tercera donde almaceno la interseccion de ambas (incluyendo a quienes solo tienen 2da dosis)
  listaG* listaGente1D=crearlistaVaciaG();
  listaG* listaGente2D=crearlistaVaciaG();
  listaG* vacunados1D=crearlistaVaciaG();
  listaG* listGente=crearlistaVaciaG();

  //COMIENZO A TOMAR EL TIEMPO
  //clock_t start_t, end_t, total_t;
	//start_t = clock();
  
  //al momento de leer los archivos se insertan ordenados x apellido
  leerGente(listaGente1D,"vacunados1D.in");//primera dosis
  leerGente(listaGente2D,"vacunados2D.in");//segunda dosis

  //esta funcion me llena la lista de vacunados totales
  vacunacionCompleta(listaGente1D,listaGente2D,listGente);

  //elimino de la lista gente1d, los que ya tengan su 2da dosis lista
  eliminarVacunados(listaGente1D,listaGente2D);
  
  //como ahora solo tengo gente con su 1ra dosis, calculo la fecha de la 2da
  calcularSegundaDosis(listaGente1D,listaVacunas);

  //esta funcion ordena la gente de la primera dosis segun su fecha de segunda dosis
  ordenarDia(listaGente1D,vacunados1D);

  //SALIDAS//
  //esta funcion genera el vacunadosCompletos.out
  salidaVacunacionCompleta(listGente,listaVacunas,listaGente2D);
  //esta funcion genera el provision.out
  calcularProvisiones(listaGente1D,listaVacunas);
  //esta funcion genera el listado.out
  salidaListado(vacunados1D,listaVacunas);

  //LIBERO LAS LISTAS
  liberarlistaG(listaGente1D);
  liberarlistaG(listaGente2D);
  liberarlistaG(vacunados1D);
  liberarlistaG(listGente);
  liberarListaV(listaVacunas);

  //TERMINO DE CALCULAR EL TIEMPO
  //end_t = clock();
	//total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	//printf("%f segs\n", total_t  );

  return 0;
}
//funcion que genera vacunacioncompleta.out
void salidaVacunacionCompleta(listaG* vc,listaV* vacunas,listaG* dosis2){
  FILE* salida1=fopen("vacunacionCompleta.out","w");
  fprintf(salida1,"%d\n",largolistaG(dosis2));
  nodoG* agregar;
  agregar= vc->inicio;
  while(agregar!=NULL){
    char* CODIGO;
    CODIGO=vacunaCodigo(agregar->idVacuna,vacunas);
    fprintf(salida1,"%s %s %s %d %d/%d/%d %s\n",agregar->rut,agregar->nombre,agregar->apellido,agregar->edad,agregar->dia,agregar->mes,agregar->year,CODIGO);
    agregar=agregar->siguiente;
  }
  fclose(salida1);
}
//funcion que genera provision.out
void calcularProvisiones(listaG* v1d,listaV* vacunas){
  nodoG* gActual;
  nodoV* vacunaActual;
  int i;
  int vacunasMes;
  char mes[12];
  FILE* salida2=fopen("provision.out","w");
  for(i=1;i<13;i++){
    gActual=v1d->inicio;
    vacunasMes=0;
    vacunaActual=vacunas->inicio;
    while(vacunaActual!=NULL){
        vacunaActual->dosisNecesarias=0;
        vacunaActual=vacunaActual->siguiente;
    }
    while(gActual!=NULL){
      if(gActual->mes2dosis==i){
        vacunaActual=buscarVacuna(vacunas,gActual->idVacuna);
        vacunaActual->dosisNecesarias=vacunaActual->dosisNecesarias+1;
        vacunasMes++;
      }
      gActual=gActual->siguiente;
    }
    if(vacunasMes!=0){
      char meses[12][12]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre", "Octubre","Noviembre","Diciembre"};
      fprintf(salida2,"%s %d\n",meses[i-1],vacunasMes);
      vacunaActual=vacunas->inicio;
      while(vacunaActual!=NULL){
        fprintf(salida2,"%s %d\n",vacunaActual->codigoV,vacunaActual->dosisNecesarias);
        vacunaActual->dosisNecesarias=0;
        vacunaActual=vacunaActual->siguiente;
      }
      fprintf(salida2,"\n");
    }
  }
  fclose(salida2);
}
//funcion que genera listado.out
void salidaListado(listaG* v1d,listaV* vacunas){
  int i;
  nodoG* gActual;
  int vacunadosMES;
  FILE* salida3=fopen("listado.out","w");
  for(i=1;i<13;i++){
    gActual=v1d->inicio;
    vacunadosMES=0;
    while(gActual!=NULL){
      if(gActual->mes2dosis==i){
        vacunadosMES++;
      }
      gActual=gActual->siguiente;
    }
    if(vacunadosMES!=0){
      char meses[12][12]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre", "Octubre","Noviembre","Diciembre"};
      fprintf(salida3,"%s %d\n",meses[i-1],vacunadosMES);
      gActual=v1d->inicio;
      while(gActual!=NULL){
        if(gActual->mes2dosis==i){
          //12573685-8 Esther Alves 46 26/04/21 24/05/21 BTN162B2
          char* codigo;
          codigo=vacunaCodigo(gActual->idVacuna,vacunas);
          fprintf(salida3,"%s %s %s %d %d/%d/%d %d/%d/%d %s\n",gActual->rut,gActual->nombre,gActual->apellido,gActual->edad,gActual->dia,gActual->mes,gActual->year,gActual->dia2dosis,gActual->mes2dosis,gActual->year2dosis,codigo);
        }
        gActual=gActual->siguiente;
      }
    }
  }
  fclose(salida3);
}

//estas funciones sirven para calcular la fecha de la segunda dosis
//entra un nodo y la lista de vacunas
//mediante iteraciones calcula la segunda fecha de vacunacion de un nodo
void segundaDosis(nodoG* nodo,listaV* vacunas){
	int diasEspera;
  nodoV* vacunaActual;
  vacunaActual=vacunas->inicio;
  while(vacunaActual->IDV!=nodo->idVacuna){
    vacunaActual=vacunaActual->siguiente;
  }
  diasEspera=(vacunaActual->semanasV)*7;
  int i;
  nodo->dia2dosis=nodo->dia;
  nodo->mes2dosis=nodo->mes;
  nodo->year2dosis=nodo->year;
  for(i=0;i<diasEspera;i++){
    if(nodo->dia2dosis == limiteMes(nodo->mes2dosis,nodo->year)){
      nodo->dia2dosis=1;
      nodo->mes2dosis=nodo->mes2dosis+1;
      if(nodo->mes2dosis==13){
        nodo->mes2dosis=1;
        nodo->year2dosis=nodo->year2dosis+1;
      }
    }
    nodo->dia2dosis=nodo->dia2dosis+1;
  }

}
//esta funcion realiza llamados nodo a nodo para calcular la segunda fecha de una lista
void calcularSegundaDosis(listaG* lista,listaV* vacunas){
	nodoG* actual;
	actual=lista->inicio;
	while(actual!=NULL){
		segundaDosis(actual,vacunas);
		actual=actual->siguiente;
	}
}