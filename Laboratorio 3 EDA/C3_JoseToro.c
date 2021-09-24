#include <stdio.h>
#include <stdlib.h>
#include "TDAgrafo.h"
//aqui almaceno todos los valores que se ingresen en el archivo .in
typedef struct EstadoCamion{
	int estadoActual;//esta es la id del estado
	int estadoAnterior;//esta es la id del estado anterior
	int posicion;//id del vacunatario/centro donde se encuentra el camion
	int Capacidad_Inicial;//carga inicial del camion
	int Capacidad_Actual;//carga actual del camion
	int Subsidio;//subsidio
	int Coste_Min;//coste actual
	int* ruta;//ruta seguida( lista de enteros)
	int tamanioRuta;//tamanio de la ruta actual(0 en caso no de salir aun)
	int** insumos;//matriz que almacena los insumos requeridos por cada centro de vacunacion
	int CantVacunatorios;
	
} EstadoCamion;
int correlativo;

//cabeceras
EstadoCamion crearEstado(int anterior,int tamanioRuta);
EstadoCamion * agregarEstado(EstadoCamion * lista, int * elementos, EstadoCamion estado);
EstadoCamion * sacarElemento(EstadoCamion * lista, int * elementos);
EstadoCamion LeerInsumos (EstadoCamion S);
void mostrarEstado(EstadoCamion C);
int* agregarRuta(int* a,int tamanio,int valor);
int estaEstado(EstadoCamion* lista, int largo,EstadoCamion estado);
int noVisitado(int* ruta,int pos,int L);
void Salida(EstadoCamion S);
int main() 
{
	//para resolver este lab, utilizare una especie de busqueda en anchura 
	TDAgrafo* grafo;

	grafo=leerGrafo("conexiones.in");

	
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	int i;
	EstadoCamion Actual,Siguiente; //estos estados iran variando y agregandoce en abierto / cerrado
	EstadoCamion * abiertos = (EstadoCamion *)malloc(sizeof(EstadoCamion)*canAbiertos);
	EstadoCamion * cerrados = (EstadoCamion *)malloc(sizeof(EstadoCamion)*canCerrados);
	//creo el primer camion
	EstadoCamion CamionInicial;
	CamionInicial = crearEstado(correlativo,1);
	CamionInicial = LeerInsumos(CamionInicial);
	CamionInicial.posicion=0;//como el camion no ha salido esta en la posicion 0
	CamionInicial.ruta[0]=0;
	CamionInicial.Capacidad_Actual=CamionInicial.Capacidad_Inicial;
	abiertos = agregarEstado(abiertos, &canAbiertos, CamionInicial);
	while(canAbiertos>0){
		Actual = abiertos[0]; //mi actual es el abierto posicion 0 
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados, Actual);
		i=0;
		while (i != grafo->cvertices){
			if(grafo->adyacencias[Actual.posicion][i]!=0){
				//ahora debo agregar el nuevo estado del camion 
				if(noVisitado(Actual.ruta,i,Actual.tamanioRuta)==1){
					Siguiente=crearEstado(Actual.estadoActual,Actual.tamanioRuta +1);
					Siguiente.posicion=i;
					Siguiente.insumos=Actual.insumos;
					Siguiente.Capacidad_Inicial=Actual.Capacidad_Inicial;
					int peso;
					peso=Siguiente.insumos[i-1][1];
					Siguiente.Capacidad_Actual=Actual.Capacidad_Actual-peso;
					Siguiente.Subsidio=Actual.Subsidio;
					int* b=agregarRuta(Actual.ruta,Actual.tamanioRuta,i);
					Siguiente.ruta=b;
					int distancia;
					int recorrido;
					distancia=grafo->adyacencias[Actual.posicion][i];
					recorrido=(distancia*Actual.Capacidad_Actual)/Siguiente.Subsidio;
					Siguiente.Coste_Min= Actual.Coste_Min + recorrido;
					if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) || (estaEstado(cerrados,canCerrados,Siguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
						abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
					}
					else{//si lo anterior no se cumple, disminuyo correlativo 
						correlativo--;
					}
				}
			}
			i++;
		}
	}
	//ahora filtrare entre todos los estados de cerrados las posibles soluciones
	int TamanioSol;
	TamanioSol=0;
	EstadoCamion * PosiblesSoluciones = (EstadoCamion *)malloc(sizeof(EstadoCamion)*TamanioSol);
	for(i=0;i<canCerrados;i++){
		//aqui debo filtrar y agregar estos estas posibles soluciones a una nueva lista
		if(cerrados[i].tamanioRuta==grafo->cvertices){
			PosiblesSoluciones=agregarEstado(PosiblesSoluciones,&TamanioSol,cerrados[i]);
		}
	}
	int min;
	int pos;
	min=PosiblesSoluciones[0].Coste_Min;
	for(i=0;i<TamanioSol;i++){
		if(min>PosiblesSoluciones[i].Coste_Min){
			min=PosiblesSoluciones[i].Coste_Min;
			pos=i;
		}
	}
	Salida(PosiblesSoluciones[pos]);

	free(cerrados);
	free(abiertos);
	
	free(PosiblesSoluciones);
	
	return 0;
}
void Salida( EstadoCamion S){
	FILE* SALIDA = fopen("salida.out","w");
	fprintf(SALIDA,"Capacidad: %dton\nSubsidio: %dum\nCoste minimo: %dum\nRuta:\n",S.Capacidad_Inicial,S.Subsidio,S.Coste_Min);
	int i;
	fprintf(SALIDA,"CENTRO->");
	for(i=1;i<S.tamanioRuta-1;i++){
		fprintf(SALIDA,"%d->",S.ruta[i]);
	}
	fprintf(SALIDA,"%d",S.ruta[S.tamanioRuta-1]);
	fclose(SALIDA);
}
EstadoCamion LeerInsumos(EstadoCamion S){
FILE* file=fopen("insumos.in","r");
int cantidadVacunatorios;
int Subsidio;
fscanf(file,"%d %d",&cantidadVacunatorios,&Subsidio);
S.Subsidio=Subsidio;
S.insumos=(int**)malloc(sizeof(int*)*cantidadVacunatorios);
S.CantVacunatorios=cantidadVacunatorios;
int i;
int Vacunatorio;
int Toneladas;
int ToneladasTotales;
ToneladasTotales=0;
for(i=0;i<cantidadVacunatorios;i++){
	S.insumos[i]=(int*)malloc(sizeof(int)*2);
	fscanf(file,"%d %d",&Vacunatorio,&Toneladas);
	S.insumos[i][0]=Vacunatorio;
	S.insumos[i][1]=Toneladas;
	ToneladasTotales=ToneladasTotales+Toneladas;
}
fclose(file);
S.Capacidad_Inicial=ToneladasTotales;
return S;
}
EstadoCamion crearEstado(int anterior,int tamanioRuta){
	EstadoCamion nuevoEstado;
	nuevoEstado.estadoActual = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.Capacidad_Actual=0;
	nuevoEstado.Capacidad_Inicial=0;
	nuevoEstado.Coste_Min=0;
	nuevoEstado.tamanioRuta=tamanioRuta;
	nuevoEstado.CantVacunatorios;
	nuevoEstado.ruta=(int*)malloc(sizeof (int)*tamanioRuta);
	correlativo = correlativo + 1;
	return nuevoEstado;
}
int* agregarRuta(int* a,int tamanio,int valor){
	int i;
	int* b= (int*)malloc(sizeof(int)*(tamanio+1));
	for(i=0;i<tamanio;i++){
		b[i]=a[i];
	}
	b[tamanio]=valor;
	return b;
}

EstadoCamion * agregarEstado(EstadoCamion * lista, int * elementos, EstadoCamion estado){
	EstadoCamion * nuevaLista = (EstadoCamion *)malloc(sizeof(EstadoCamion)*(*elementos+1));
	int i;
	for (i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

EstadoCamion * sacarElemento(EstadoCamion * lista, int * elementos){
	EstadoCamion * nuevaLista = (EstadoCamion *)malloc(sizeof(EstadoCamion)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}
void mostrarEstado(EstadoCamion C){
	printf("%d estadoActual, %d estadoAnterior\n",C.estadoActual,C.estadoAnterior);
	printf("%d capacidad inicial,%d capacidad actual\n",C.Capacidad_Inicial,C.Capacidad_Actual);
	printf("%d subsidio, %d coste actual\n",C.Subsidio,C.Coste_Min);
	printf("%d posicion\n",C.posicion);
	printf("tamanio ruta %d \n",C.tamanioRuta);
	int i;
	for(i=0;i<C.tamanioRuta;i++){
		printf("%d ",C.ruta[i]);
	}
	printf("\n----------\n");
}

int revisarRutas(int* a, int* b,int L){
	int i;
	for(i=0;i<L;i++){
		if(a[i]!=b[i]){
			return 0;
		}
	}
	return 1;
}
int estaEstado(EstadoCamion* lista, int largo,EstadoCamion estado){
	int i;
	for(i=1;i<largo;i++){
		if(revisarRutas(lista[i].ruta,estado.ruta,largo)==1){
			return 1;
		}
	}
	return 0;
}
int noVisitado(int* ruta,int pos,int L){
	int i;
	for(i=0;i<L;i++){
		if(ruta[i]==pos){
			return 0;
		}
	}
	return 1;
}