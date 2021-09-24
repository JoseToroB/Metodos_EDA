#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//  datos alumno     /////////
//	Jose Javier Toro Bustos /
//	Seccion 0-A-1    ///////
///////////////////////////
struct nodo{
    int num;
    struct nodo *hijoIzquierdo;
    struct nodo *hijoDerecho;
};

typedef struct nodo nodo;

nodo * crearNodo(int num){
    nodo* nuevoNodo = (nodo*) malloc(sizeof(nodo));
    nuevoNodo->num = num;
    nuevoNodo->hijoIzquierdo = NULL;
    nuevoNodo->hijoDerecho = NULL;
    return nuevoNodo;
}


nodo * insertar(nodo * raiz, nodo * nuevoNodo){
    if(raiz == NULL)
    raiz = nuevoNodo;
    else{
        nodo * aux = raiz;
        nodo * auxAnterior = aux;
        while(aux != NULL){
            if(aux->num > nuevoNodo->num){
                auxAnterior = aux;
                aux = aux->hijoIzquierdo;
            }
            else{
                auxAnterior = aux;
                aux = aux->hijoDerecho;
            }
        }

    if(auxAnterior->num > nuevoNodo->num)
    auxAnterior->hijoIzquierdo = nuevoNodo;

    else{
        auxAnterior->hijoDerecho = nuevoNodo;
    }
    }
    return raiz;
}
// altura del arbol, funcion creada por alumno //////////////////
int calcularAltura(nodo *raiz){ 
	int Izq,Der;
	if (raiz!=NULL){ //si el nodo existe, ejecuto el codigo
		Izq=calcularAltura(raiz->hijoIzquierdo);
		Der=calcularAltura(raiz->hijoDerecho);
		if(Izq>Der){ //si el valor de la izq es mayor que en la derecha, retorno la izq+1 ya que si no tiene nodo hermano
			return Izq+1; //el nodo faltante, vale 0 y este valdra 1, asi guardara el valor 
		}
		else{//en caso de que la derecha sea mayor retorno derecha+1
			return Der+1; //el +1 tiene la misma funcion que en el return izq+1
		}
	}
	return 0;//si el nodo actual no existe, retorno 0 para que no aumente el contador
	
}
////////////////////////////////////////////////////////////
int main(){
	srand(time(NULL));
	nodo*raiz=NULL;
	int i,num;
	int cant=rand()%101; //para calcular la altura use cant=10 ya que los dibuje a mano
	printf("cant = %d\n",cant);
	for(i=0;i<cant;i++){
		num=rand()%101;
		raiz=insertar(raiz,crearNodo(num));
		printf("%d ",num);
	}
	printf("\n\n");
	printf("funcion mostrar nodo\n");
	int Altura;
	Altura=calcularAltura(raiz);
	printf("\n\nla altura del arbol es %d\n",Altura);
	return 0;
}