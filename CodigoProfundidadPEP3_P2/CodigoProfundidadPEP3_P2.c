#include <stdio.h>
#include <stdlib.h>

//struct del tablero
typedef struct EstadoTablero EstadoTablero;

struct EstadoTablero{
	int**tablero;//este es el tablero
	//estas dos variables son para tener almacenada la posicion del caballo
	int caballoX;
	int caballoY;
	//
	int peonesRestantes;//almacena cuantos peones quedan
	int estadoActual;//esta es la id del estado
	int estadoAnterior;//esta es la id del estado anterior
	char * transicion; //el movimiento realizo (se indicaran con los cambios de coordenadas)
};
int correlativo;


//esta funcion crea un tablero de 5x5 asignando memoria para este
int** crearTablero(){
	int**Tablero=(int**)malloc(sizeof(int*)*5);
	int i;
	for(i=0;i<5;i++){
		Tablero[i]=(int*)malloc(sizeof(int)*5);
	}
	return Tablero;
}

//crear estadosTablero
EstadoTablero crearEstado(int anterior, char * t){
	EstadoTablero nuevoEstado;
	nuevoEstado.tablero=crearTablero();
	nuevoEstado.estadoActual = correlativo;
	nuevoEstado.estadoAnterior = anterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}

//funcion para agregar estados a una lista
EstadoTablero * agregarEstado(EstadoTablero * lista, int * elementos, EstadoTablero estado){
	EstadoTablero * nuevaLista = (EstadoTablero *)malloc(sizeof(EstadoTablero)*(*elementos+1));
	int i;
	for (i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}

//funcion que quita el primer elemento de una lista
EstadoTablero * sacarElemento(EstadoTablero * lista, int * elementos){
	EstadoTablero * nuevaLista = (EstadoTablero *)malloc(sizeof(EstadoTablero)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}
//esta funcion me compara dos struct EstadoTablero comparando sus
//tableros  para ver si son iguales 
//si retorno un 1, quiere decir que son iguales, retorno 0 en caso de que no lo sean
int compararTableros(EstadoTablero a, EstadoTablero b){//retorno 1 (si son distintas) y 0 (si son iguales)
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(a.tablero[i][j]!=b.tablero[i][j]){
				return 0;//si encuentra dos valores que sean distintos entonces los tableros no son los mismos
			}
		}
	}
	return 1;//si termina el for y no encuentro un valor distinto dentro de los tableros , entonces retorno 1, son iguales los tableros
}



//esta funcion la utilice para ir comprobando mi avance mientras realizaba el codigo
//sin embargo no la volvi a utilizar al momento de mostrar las soluciones ya que no era lo que se me pedia
//por esto la dejo comentada en caso de querer utiliazarla usted y ver asi mas graficamente los movimientos

void  mostrarTablero(EstadoTablero estado){
	int i,j;//creo estas variables para copiar los tableros mediante dos ciclos fors
	printf("\n");
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			printf("%d ",estado.tablero[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


//esta funcion copia los tableros de un estado a un "nuevoEstado" 
EstadoTablero copiarTableros(EstadoTablero nuevoEstado,EstadoTablero estado){
	int i,j;//creo estas variables para copiar los tableros mediante dos ciclos fors
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			nuevoEstado.tablero[i][j]=estado.tablero[i][j];
		}
	}
	//copio las coordenadas del caballo de "estado" 
	
	nuevoEstado.caballoX=estado.caballoX;
	nuevoEstado.caballoY=estado.caballoY;
	//retorno nuevoEstado ya que copie el tablero y la posicion del caballo

	return nuevoEstado;
}
//esta funcion revisa si el estado actual ya fue creado (esta repetido o no ) (sirve para revisar en abiertos o en cerrados)
//retorno 1 si esta repetido y 0 si no lo esta
int estaEstado(EstadoTablero* lista,int elementos,EstadoTablero estado){
	int i;
	for (i=0;i<elementos;i++){
		if((compararTableros(lista[i],estado))==1){
			return 1;
		}
	}
	return 0;
}
//esta funcion solo muestra las transiciones(movimientos) a realizar
void mostrarSolucion(EstadoTablero* lista, int ultimo){
	printf("Los pasos son, del ultimo al primero: \n");
	while(lista[ultimo].estadoActual != 0){
		printf("%d,%d\n", lista[ultimo].caballoX,lista[ultimo].caballoY);
		ultimo = lista[ultimo].estadoAnterior;
	}
}
//esta funcion revisa si un estado es solucion
//para eso debe cumplirse que no queden peones
//retorno 1 si es el estado final, 0 si no lo es
int esFinal(EstadoTablero estado){
	if(estado.peonesRestantes==0){
		return 1;
	}
	else{
		return 0;
	}
}
//movimientos del caballo
//el caballo se mueve en "L" y tiene un total de 8 movimientos posibles
//2 arriba a la izq      (caballoX-2,caballoY-1)(CREADA) y (caballoX-1,caballoY-2)(CREADA)
//2 arriba a la derecha  (caballoX-2,caballoY+1)(CREADA) y (caballoX-1,caballoY+2)(CREADA)
//2 abajo a la izq       (caballoX+2,caballoY-1)(CREADA) y (caballoX+1,caballoY-2)(CREADA)
//2 abajo a la derecha   (caballoX+2,caballoY+1)(CREADA) y (caballoX+1,caballoY+2)(CREADA)
//como se ve en la figura 1 


//movimientos arriba a la izq y su comprobacion (revisa si es posible ejecutar el movimiento)
//arriba izq 1(caballoX-2,caballoY-1)  y  arribaIZQ2 (caballoX-1,caballoY-2)
//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero arribaIZQ1(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado;
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo dos hacia arriba y  uno la izquierda\n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX-2][nuevoEstado.caballoY-1])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-2][nuevoEstado.caballoY-1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-2;
		nuevoEstado.caballoY=nuevoEstado.caballoY-1;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-2][nuevoEstado.caballoY-1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-2;
		nuevoEstado.caballoY=nuevoEstado.caballoY-1;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarArribaIZQ1(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//caballoX-2,caballoY-1 sea un movimineto posible (no se salga del tablero)
	//((estado.caballoX-2)>=0)&&((estado.caballoY-1)>=0) si esto se cumple entonces no se sale del tablero ya que este movimiento 
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX-2)>=0)&&((estado.caballoY-1)>=0)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}
//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo (caballoX-1,caballoY-2)
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero arribaIZQ2(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado;
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo uno hacia arriba y  dos la izquierda\n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX-1][nuevoEstado.caballoY-2])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-1][nuevoEstado.caballoY-2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-1;
		nuevoEstado.caballoY=nuevoEstado.caballoY-2;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-1][nuevoEstado.caballoY-2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-1;
		nuevoEstado.caballoY=nuevoEstado.caballoY-2;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarArribaIZQ2(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//(caballoX-1,caballoY-2)sea un movimineto posible (no se salga del tablero)
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX-1)>=0)&&((estado.caballoY-2)>=0)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}


//aqui van los movimientos arriba a la derecha y sus comprobaciones

//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero arribaDER1(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado;
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo dos hacia arriba y  uno a la derecha \n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX-2][nuevoEstado.caballoY+1])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-2][nuevoEstado.caballoY+1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-2;
		nuevoEstado.caballoY=nuevoEstado.caballoY+1;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-2][nuevoEstado.caballoY+1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-2;
		nuevoEstado.caballoY=nuevoEstado.caballoY+1;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarArribaDER1(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//(caballoX-2,caballoY+1)sea un movimineto posible (no se salga del tablero)
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX-2)>=0)&&((estado.caballoY+1)<=4)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}

//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero arribaDER2(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado; 
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo uno hacia arriba y  dos a la derecha \n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX-1][nuevoEstado.caballoY+2])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-1][nuevoEstado.caballoY+2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-1;
		nuevoEstado.caballoY=nuevoEstado.caballoY+2;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX-1][nuevoEstado.caballoY+2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX-1;
		nuevoEstado.caballoY=nuevoEstado.caballoY+2;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarArribaDER2(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//(caballoX-1,caballoY+2)sea un movimineto posible (no se salga del tablero)
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX-1)>=0)&&((estado.caballoY+2)<=4)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}

//ahora hare los moviminetos que son abajo a la izq y abajo a la der
//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero abajoIZQ1(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado;
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo uno hacia abajo y  dos a la izquierda \n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX+1][nuevoEstado.caballoY-2])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+1][nuevoEstado.caballoY-2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+1;
		nuevoEstado.caballoY=nuevoEstado.caballoY-2;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+1][nuevoEstado.caballoY-2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+1;
		nuevoEstado.caballoY=nuevoEstado.caballoY-2;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarAbajoIZQ1(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//x+1,y-2 sea un movimineto posible (no se salga del tablero)
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX+1)<=4)&&((estado.caballoY-2)>=0)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}
//ahora hare los moviminetos que son abajo a la izq y abajo a la der
//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero abajoIZQ2(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado;
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo dos hacia abajo y  uno a la izquierda \n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX+2][nuevoEstado.caballoY-1])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+2][nuevoEstado.caballoY-1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+2;
		nuevoEstado.caballoY=nuevoEstado.caballoY-1;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+2][nuevoEstado.caballoY-1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+2;
		nuevoEstado.caballoY=nuevoEstado.caballoY-1;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarAbajoIZQ2(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//x+2,y-1 sea un movimineto posible (no se salga del tablero)
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX+2)<=4)&&((estado.caballoY-1)>=0)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}

//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero abajoDER1(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado;
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo uno hacia abajo y  dos a la derecha \n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX+1][nuevoEstado.caballoY+2])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+1][nuevoEstado.caballoY+2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+1;
		nuevoEstado.caballoY=nuevoEstado.caballoY+2;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+1][nuevoEstado.caballoY+2]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+1;
		nuevoEstado.caballoY=nuevoEstado.caballoY+2;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarAbajoDER1(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//x+1,y+2 sea un movimineto posible (no se salga del tablero)
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX+1)<=4)&&((estado.caballoY+2)<=4)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}
//esta funcion ejecuta el movimiento cambiando el tablero y las coordenadas del caballo
//para esto crea un nuevo estado y lo retorna una vez creado 
//tambien revisa si al mover el caballo a esta nueva posicion, come o no un peon, 
EstadoTablero abajoDER2(EstadoTablero estado){
	//creo el estado
	EstadoTablero nuevoEstado;
	nuevoEstado=crearEstado(estado.estadoActual,"mover el caballo dos hacia abajo y  uno a la derecha \n");
	//copio el tablero
	nuevoEstado=copiarTableros(nuevoEstado,estado);
	//reviso si en la posicion destino hay un peon (1)
	//en caso de ser asi, lo resto a peonesRestantes, y muevo el caballo
	
	if((nuevoEstado.tablero[nuevoEstado.caballoX+2][nuevoEstado.caballoY+1])==1){
    //como eliminare un peon, hago la resta a peones restantes y guardo el resultado en su variable de nuevoEstado
		nuevoEstado.peonesRestantes=estado.peonesRestantes-1;
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+2][nuevoEstado.caballoY+1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+2;
		nuevoEstado.caballoY=nuevoEstado.caballoY+1;
		return nuevoEstado;
	}
	else{
		//ahora muevo el caballo
		nuevoEstado.tablero[nuevoEstado.caballoX][nuevoEstado.caballoY]=0;//como muevo el caballo, queda la casilla vacia
		nuevoEstado.tablero[nuevoEstado.caballoX+2][nuevoEstado.caballoY+1]=2;//el caballo lo represento por un 2
		//ahora cambio las coordenadas del caballo dentro de la struct
		nuevoEstado.caballoX=nuevoEstado.caballoX+2;
		nuevoEstado.caballoY=nuevoEstado.caballoY+1;
		//como no elimine peones, el valor queda igual
		nuevoEstado.peonesRestantes=estado.peonesRestantes;

		return nuevoEstado;
	}
}
//esta funcion revisa si es posible ejecutar el movimiento de arriba
//retorna 1 si es posible, retorna 0 si no lo es
int comprobarAbajoDER2(EstadoTablero estado){
	//necesito comprobar que la coordenada 
	//x+2,y+1 sea un movimineto posible (no se salga del tablero)
	//solo se realiza hacia arriba a la izq, solo se podra acercar a 0,0
	if(((estado.caballoX+2)<=4)&&((estado.caballoY+1)<=4)){//si se cumplen estos parametros, entonces retorno 1(el movimiento es posible)
		return 1;//si esas dos se cumplen, entonces el movimiento si es posible
	}
	else{//si el movimiento no se puede realizar retorno 0
		return 0;
	}
}

int main(){
	int caballoX,caballoY;//par coordenado inicial del caballo, el caballo lo represento con un 2
	int cantidadPeones;//cuantos peones agregara el usuario, los peones los represento con 1's
	int peonX,peonY;//par coordenado para agregar peones
	
	correlativo = 0;
	int canAbiertos = 0;
	int canCerrados = 0;
	EstadoTablero tActual,tSiguiente; //estos estados iran variando y agregandoce en abierto / cerrado
	EstadoTablero * abiertos = (EstadoTablero *)malloc(sizeof(EstadoTablero)*canAbiertos);
	EstadoTablero * cerrados = (EstadoTablero *)malloc(sizeof(EstadoTablero)*canCerrados);
	//aqui creo el tablero inicial
	EstadoTablero TableroInicial=crearEstado(correlativo,"");
	TableroInicial.peonesRestantes=cantidadPeones;
	//ahora llenare el tablero inicial
	//primero relleno el tablero inicial con 0's
	int i,j;//para recorrer el tablero
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			TableroInicial.tablero[i][j]=0;
		}
	}
	//pido las coords del caballo
	printf("tenga en cuenta que el tablero es de 5x5 y que sus coordenadas van desde 0,0 hasta 4,4\n");
	printf("ingrese la posicion de la forma X,Y donde inicia el caballo:");
	scanf("%d,%d",&caballoX,&caballoY);
	if(caballoX<0 || caballoX>4){
		printf("posicion invalida\n");
		return 0;
	}
	if(caballoY<0 || caballoY>4){
		printf("posicion invalida\n");
		return 0;
	}
	printf("el caballo iniciara en %d,%d\n",caballoX,caballoY);
	//ingreso el caballo al tablero
	TableroInicial.caballoY=caballoY;
	TableroInicial.caballoX=caballoX;
	TableroInicial.tablero[caballoX][caballoY]=2;
	//pido la cantidad de peones en caso de ingresar 0 peones, se retorna un 0 y un mensaje 
	printf("ingrese la cantidad (maximo 24 por el tamanio del tablero) de peones: ");
	scanf("%d",&cantidadPeones);
	if(cantidadPeones<=0){
    printf("como la cantidad de peones es menor o igual a 0 y aun no se \nhan realizado movimientos, se termina el ejercicio\n");
    return 0;
	}
	if(cantidadPeones>24){
    printf("la cantidad maxima de peones es 24 ya que es un tablero de 5x5 \n");
    return 0;
	}
	TableroInicial.peonesRestantes=cantidadPeones;
	//ahora pedire que ingrese las coords de cada peon
	for(i=0;i<cantidadPeones;i++){
		printf("ingrese las coords del peon numero %d de la forma X,Y :",i+1);
		scanf("%d,%d",&peonX,&peonY);
		TableroInicial.tablero[peonX][peonY]=1;
		printf("\n");
	}
	abiertos = agregarEstado(abiertos, &canAbiertos, TableroInicial);
	//ahora crear un ciclo iterativo que vaya generando distintos estados para asi buscar una solucion
	while(canAbiertos>0){
    tActual = abiertos[0]; //mi actual es el abierto posicion 0 
	abiertos = sacarElemento(abiertos, &canAbiertos);
	cerrados = agregarEstado(cerrados, &canCerrados, tActual);
    if(esFinal(tActual) == 1){
		mostrarSolucion(cerrados,canCerrados-1);
		return 0;
	}
    else{
		//ahora debo realizar los ocho movientos, realizare los movimientos en direccion de las agujas del reloj
		//primer movimiento
		if(comprobarArribaDER1(tActual)==1){//compruebo si puedo realizar el movimiento
			tSiguiente = arribaDER1(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo 
				correlativo = correlativo - 1;
			}
		}
		//segundo movimiento
		if(comprobarArribaDER2(tActual)==1){
			tSiguiente = arribaDER2(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo
				correlativo = correlativo - 1;
			}
		}
		//tercer movimiento
		if(comprobarAbajoDER1(tActual)==1){
			tSiguiente = abajoDER1(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo
				correlativo = correlativo - 1;
			}
		}
		//cuarto movimiento ( ultimo movimiento del lado derecho)
		if(comprobarAbajoDER2(tActual)==1){
			tSiguiente = abajoDER2(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo
				correlativo = correlativo - 1;
			}
		}
		//quinto movimiento (primer movimiento lado izq)
		if(comprobarAbajoIZQ2(tActual)==1){
			tSiguiente = abajoIZQ2(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo
				correlativo = correlativo - 1;
			}
		}
		//sexto movimiento (2do movimiento del lado izq
		if(comprobarAbajoIZQ1(tActual)==1){
			tSiguiente = abajoIZQ1(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo
				correlativo = correlativo - 1;
			}
		}
		//septimo movimiento (3er movimiento del lado izq)
		if(comprobarArribaIZQ2(tActual)==1){
			tSiguiente = arribaIZQ2(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo
				correlativo = correlativo - 1;
			}
		}
		//octavo movimiento (ultimo del lado izq)
		if(comprobarArribaIZQ1(tActual)==1){
			tSiguiente = arribaIZQ1(tActual);//hago el movimiento
			if((estaEstado(abiertos,canAbiertos,tSiguiente) == 0) && (estaEstado(cerrados,canCerrados,tSiguiente) == 0)){//reviso que el estado no este ni en abiertos ni en cerrados en caso de que se cumpla, lo agrego en abiertos
				abiertos = agregarEstado(abiertos,&canAbiertos,tSiguiente);
			}
			else{//si lo anterior no se cumple, disminuyo correlativo
				correlativo = correlativo - 1;
			}
		}
	}
  }
  return 0;
}