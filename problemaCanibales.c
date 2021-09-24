//20.329.232-5  Jose Toro
//Seccion L7
//fecha de creacion del codigo 19/09/2020 (ultima vez que lo modifique)
#include <stdio.h>
#include <stdlib.h>

//estructura 
typedef struct estadoCanibales estadoCanibales;

struct estadoCanibales{
    //lado A
	int cantidadMisionerosA; 
	int canibalesA;
	//bote 0 si esta en A, 1 si esta en B
    int posBote; 	
	//lado B
    int cantidadMisionerosB; 
    int canibalesB;
	//estado actual (para identificar)
	int estadoActual;
	//estado anterior(para crear el trazado de respuesta)
	int estadoAnterior; 
	//transicion realizada(no lo uso pero al inicio del programa pensaba mostrarlo)
	char * transicion;
};

int correlativo;

//esta funcion crea un estado
estadoCanibales crearEstado(int cantidadMisionerosA, int cantidadMisionerosB, int canibalesA, int canibalesB, int posBote ,int estadoAnterior, char * t){
	estadoCanibales nuevoEstado;
    nuevoEstado.cantidadMisionerosA = cantidadMisionerosA;
    nuevoEstado.cantidadMisionerosB = cantidadMisionerosB;
    nuevoEstado.canibalesA = canibalesA;
    nuevoEstado.canibalesB = canibalesB;
    nuevoEstado.posBote = posBote;
	nuevoEstado.estadoActual = correlativo;
	nuevoEstado.estadoAnterior = estadoAnterior;
	nuevoEstado.transicion = t;
	correlativo = correlativo + 1;
	return nuevoEstado;
}
//esta funcion agrega un estado a un array
estadoCanibales *agregarEstado(estadoCanibales * lista, int * elementos, estadoCanibales estado){
	estadoCanibales * nuevaLista = (estadoCanibales *)malloc(sizeof(estadoCanibales)*(*elementos+1));
	for (int i = 0; i < *elementos; ++i){
		nuevaLista[i] = lista[i];
	}
	nuevaLista[*elementos] = estado;
	*elementos = *elementos+1;
	free(lista);
	return nuevaLista;
}
//esta funcion elimina un elemento de un array
estadoCanibales * sacarElemento(estadoCanibales * lista, int * elementos){
	estadoCanibales * nuevaLista = (estadoCanibales *)malloc(sizeof(estadoCanibales)*(*elementos-1));
	for (int i = 1; i < *elementos; ++i){
		nuevaLista[i-1]=lista[i];
	}
	*elementos = *elementos-1;
	free(lista);
	return nuevaLista;
}

//aqui estan los "movimientos"

estadoCanibales canibalAB(estadoCanibales estado){
	estadoCanibales Nuevo;
    estado.canibalesA = estado.canibalesA-1;
    estado.canibalesB = estado.canibalesB+1;
    estado.posBote = 1; //bote para B
    Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"un canibal A->B");
	return Nuevo;
}

estadoCanibales canibalBA(estadoCanibales estado){
    estado.canibalesB = estado.canibalesB-1;
    estado.canibalesA = estado.canibalesA+1;
    estado.posBote = 0; //bote para A
	estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"un canibal B->A");
	return Nuevo;
}

estadoCanibales dosCanibalAB(estadoCanibales estado){
    estado.canibalesA = estado.canibalesA-2;
    estado.canibalesB = estado.canibalesB+2;
    estado.posBote = 1;
    estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"dos canibales A->B");
	return Nuevo;
}

estadoCanibales dosCanibalBA(estadoCanibales estado){
    estado.canibalesB = estado.canibalesB-2;
    estado.canibalesA = estado.canibalesA+2;
    estado.posBote = 0; 
    estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"dos canibales B->A");
	return Nuevo;
}


estadoCanibales misioneroAB(estadoCanibales estado){
    estado.cantidadMisionerosA = estado.cantidadMisionerosA-1;
    estado.cantidadMisionerosB = estado.cantidadMisionerosB+1;
    estado.posBote = 1; 
	estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"un misionero A->B");
	return Nuevo;
}

estadoCanibales misioneroBA(estadoCanibales estado){
    estado.cantidadMisionerosB = estado.cantidadMisionerosB-1;
    estado.cantidadMisionerosA = estado.cantidadMisionerosA+1;
    estado.posBote = 0; 
    estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"un misionero B->A");
	return Nuevo;
}

estadoCanibales dosMisioneroAB(estadoCanibales estado){
    estado.cantidadMisionerosA = estado.cantidadMisionerosA-2;
    estado.cantidadMisionerosB = estado.cantidadMisionerosB+2;
    estado.posBote = 1; 
    estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"dos misionero A->B");
	return Nuevo;
}

estadoCanibales dosMisioneroBA(estadoCanibales estado){
    estado.cantidadMisionerosB = estado.cantidadMisionerosB-2;
    estado.cantidadMisionerosA = estado.cantidadMisionerosA+2;
    estado.posBote = 0;
	estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"dos misionero B->A");
	return Nuevo;
}
    

estadoCanibales canibalMisioneroAB(estadoCanibales estado){
    estado.canibalesA = estado.canibalesA-1;
    estado.canibalesB = estado.canibalesB+1;
    estado.cantidadMisionerosA = estado.cantidadMisionerosA-1;
    estado.cantidadMisionerosB = estado.cantidadMisionerosB+1;
    estado.posBote = 1; 
    estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"un misionero y un canibal A->B");
	return Nuevo;
}

estadoCanibales canibalMisioneroBA(estadoCanibales estado){
    estado.canibalesB = estado.canibalesB-1;
    estado.canibalesA = estado.canibalesA+1;
    estado.cantidadMisionerosB = estado.cantidadMisionerosB-1;
    estado.cantidadMisionerosA = estado.cantidadMisionerosA+1;
    estado.posBote = 0; 
    estadoCanibales Nuevo;
	Nuevo=crearEstado(estado.cantidadMisionerosA,estado.cantidadMisionerosB,estado.canibalesA,estado.canibalesB,estado.posBote,estado.estadoActual,"un misionero y un canibal B->A");
	return Nuevo;
}
//verificaciones
//esta funcion verifica si es posible mover un canibal de A hacia B
int verificarCanibalAB(estadoCanibales estado){
    if(estado.posBote == 1){
        return 0;
    }
    if(estado.canibalesA == 0){
        return 0;
    }
    if(estado.canibalesA-1 <= estado.cantidadMisionerosA || estado.cantidadMisionerosB == 0){
        if(estado.cantidadMisionerosB+1 <= estado.cantidadMisionerosB || estado.cantidadMisionerosB == 0){
            return 1;
        }
    }
    return 0;
}

//esta funcion verifica si es posible mover un canibal de B hacia A
int verificarCanibalBA(estadoCanibales estado){
    if(estado.posBote == 0){
        return 0;
    }
    if(estado.canibalesB <= 0){
        return 0;
    }
    if(estado.canibalesB-1 <= estado.cantidadMisionerosB || estado.cantidadMisionerosB == 0){
        if(estado.canibalesA+1 <= estado.cantidadMisionerosA || estado.cantidadMisionerosA == 0){
            return 1;
        }
    }
    return 0;
}
//esta funcion verifica si es posible mover un misionero de A hacia B
int verificarMisioneroAB(estadoCanibales estado){
    if(estado.posBote == 1){
        return 0;
    }
    if(estado.cantidadMisionerosA == 0){
        return 0;
    }
    if(estado.cantidadMisionerosA > estado.canibalesA && estado.canibalesA != 0){
        if(estado.cantidadMisionerosB+1 >= estado.canibalesB){
            return 1;
        }
    }
    return 0;
}
//esta funcion verifica si es posible mover un misionero de B hacia A
int verificarMisioneroBA(estadoCanibales estado){
    if(estado.posBote == 0){
        return 0;
    }
    if(estado.cantidadMisionerosB == 0){
        return 0;
    }
    if(estado.cantidadMisionerosB-1 >= estado.canibalesB || estado.cantidadMisionerosB-1 == 0){
        if(estado.cantidadMisionerosA+1 >= estado.canibalesA){
            return 1;
        }
    }
    return 0;
}
//esta funcion verifica si es posible mover DOS canibales de A hacia B
int verificarDosCanibalesAB(estadoCanibales estado){
    if(estado.posBote == 1){
        return 0;
    }
    if(estado.canibalesA-2 < 0){
        return 0;
    }
    if(estado.cantidadMisionerosB >= estado.canibalesB+2){
        return 1; 
    }
    if(estado.cantidadMisionerosB == 0 && estado.canibalesA >= 2){
        return 1;
    }
    return 0;
}
//esta funcion verifica si es posible mover DOS canibales de B hacia A
int verificarDosCanibalesBA(estadoCanibales estado){
    if(estado.posBote == 0){
        return 0;
    }
    if(estado.canibalesB-2 < 0){
        return 0;
    }
    if(estado.cantidadMisionerosA >= estado.canibalesA+2){
        return 1;
    }
    if(estado.cantidadMisionerosA == 0 && estado.canibalesB >= 2){
        return 1;
    }
    return 0;
}
//esta funcion verifica si es posible mover DOS misioneros de A hacia B
int verificarDosMisionerosAB(estadoCanibales estado){
    if(estado.posBote == 1){
        return 0;
    }
    if(estado.cantidadMisionerosA < 2){
        return 0;
    }
    if(estado.cantidadMisionerosA-2 == 0){
        if(estado.cantidadMisionerosB+2 >= estado.canibalesB){
            return 1;
        }
    }
    if(estado.cantidadMisionerosA-2 >= estado.canibalesA){
        if(estado.canibalesB <= estado.cantidadMisionerosB+2){
            return 1;
        }
    }
    return 0;
}
//esta funcion verifica si es posible mover DOS misioneros de B hacia A
int verificarDosMisionerosBA(estadoCanibales estado){
    if(estado.posBote == 0){
        return 0;
    }
    if(estado.cantidadMisionerosB < 2){
        return 0;
    }
    if(estado.cantidadMisionerosB-2 > estado.canibalesB){
        return 1;
    }
    if(estado.canibalesA == 0){
        return 1;
    }
    return 0;
}
//esta funcion verifica si es posible mover UNO Y UNO de A hacia B
int verificarCanibalMisioneroAB(estadoCanibales estado){
    if(estado.posBote == 1){
        return 0;
    }
    if(estado.canibalesA == 0){
        return 0;
    }
    if(estado.cantidadMisionerosA == 0){
        return 0;
    }
    if(estado.cantidadMisionerosA >= estado.canibalesA){
        if(estado.cantidadMisionerosB+1 <= estado.cantidadMisionerosB+1){
            return 1;
        }
        return 0;
    }
    return 0;
}
//esta funcion verifica si es posible mover UNO Y UNO de B hacia A
int verificarCanibalMisioneroBA(estadoCanibales estado){
    if(estado.posBote == 0){
        return 0;
    }
    if(estado.canibalesB == 0){
        return 0;
    }
    if(estado.cantidadMisionerosB == 0){
        return 0;
    }
    if(estado.cantidadMisionerosB >= estado.canibalesB){
        if(estado.canibalesA+1 <= estado.cantidadMisionerosA+1){
            return 1;
        }
        return 0;
    }
    return 0;
}
//revisa un estado es el final
//para eso deben estar todos lo canibales y misioneros en B (0 en A ya que pueden ser N personas)
int esFinal(estadoCanibales estado){
    if(estado.canibalesA == 0 && estado.cantidadMisionerosA == 0 && estado.posBote == 1){
        return 1; 
    }
	return 0;
}
//revisa si un estado esta en una lista
int estaEstado(estadoCanibales * lista, int tamanio, estadoCanibales estado){
    if(estado.canibalesA == 0 && estado.cantidadMisionerosA == 0 && estado.posBote == 1){
        return 0; 
    }
    int i;
	for (i = 0; i < tamanio; i++){
        if(lista[i].canibalesB == estado.canibalesB && lista[i].cantidadMisionerosB == estado.cantidadMisionerosB && lista[i].posBote == estado.posBote){
			return 1;
		}
	}
    return 0; 
}
//esta funcion muestra por pantalla el paso a paso de una solucion
void mostrarSolucion(estadoCanibales * lista, int ultimo){
	int tamanio = 0;//esta variables es para la lista de soluciones que se crea a continuacion
    estadoCanibales * solucion = (estadoCanibales *)malloc(sizeof(estadoCanibales)*ultimo);//se crea con tamanio (ultimo) 
	printf("0,0,0\n");//como inicia
	while(lista[ultimo].estadoActual != 0){//este while va agregando los pasos en orden
        solucion[tamanio] = lista[ultimo];
        tamanio = tamanio+1;
		ultimo = lista[ultimo].estadoAnterior;
	}
    int i;
	for(i=tamanio-1;i!=0;i--){//esta for va imprimiendo los pasos en el orden que se hace por el while
		printf("%d,%d,%d\n",solucion[i].canibalesB,solucion[i].cantidadMisionerosB,solucion[i].posBote);
    }
	printf("%d,%d,%d\n",solucion[0].canibalesB,solucion[0].cantidadMisionerosB,solucion[0].posBote);
    printf("\n");
    free(solucion);
}

int canibales(){
    int cantidad;
    printf("cantidad misioneros/canibales (valor n): ");
    scanf("%d",&cantidad);
	correlativo = 0;
	int canAbiertos = 0; 
	int canCerrados = 0; 
	estadoCanibales Actual,Siguiente;
	estadoCanibales * abiertos = (estadoCanibales *)malloc(sizeof(estadoCanibales)*canAbiertos); 
	estadoCanibales * cerrados = (estadoCanibales *)malloc(sizeof(estadoCanibales)*canCerrados);
    
    estadoCanibales inicial = crearEstado(cantidad,0,cantidad,0,0,correlativo,"");
    
	abiertos = agregarEstado(abiertos, &canAbiertos, inicial); 
    
    int numerosolucion =1; 
    int canSol = 0; 
	while(canAbiertos > 0){ 
		Actual = abiertos[0]; 
		abiertos = sacarElemento(abiertos, &canAbiertos);
		cerrados = agregarEstado(cerrados, &canCerrados, Actual);
        //Si el estado actual es el final.
		if(esFinal(Actual) == 1){
			printf("Solucion %d \n",numerosolucion);
            numerosolucion = numerosolucion+1;
            canSol = canSol+1;
			mostrarSolucion(cerrados,canCerrados-1);
		}
		else{
			//ahora hago los movimientos
			if(verificarCanibalAB(Actual) == 1){ 
				Siguiente = canibalAB(Actual); 
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			
			if(verificarCanibalBA(Actual) == 1){
				Siguiente = canibalBA(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarMisioneroAB(Actual) == 1){
				Siguiente = misioneroAB(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarMisioneroBA(Actual) == 1){
				Siguiente = misioneroBA(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarDosCanibalesAB(Actual) == 1){
				Siguiente = dosCanibalAB(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarDosCanibalesBA(Actual) == 1){
				Siguiente = dosCanibalBA(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarDosMisionerosAB(Actual) == 1){
				Siguiente = dosMisioneroAB(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarDosMisionerosBA(Actual) == 1){
				Siguiente = dosMisioneroBA(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarCanibalMisioneroAB(Actual) == 1){
				Siguiente = canibalMisioneroAB(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
			if(verificarCanibalMisioneroBA(Actual) == 1){
				Siguiente = canibalMisioneroBA(Actual);
				if((estaEstado(abiertos,canAbiertos,Siguiente) == 0) && (estaEstado(cerrados,canCerrados,Siguiente) == 0)){
					abiertos = agregarEstado(abiertos,&canAbiertos,Siguiente);
				}else{
					correlativo = correlativo - 1;
				}
			}
		}
	}
    if(canSol == 0){
        printf("no hay solucion \n");
    }
	return 1;
}


//
//
//
// funciones del cuadrado magico
//
//
//

//esta funcion revisa si los valores que iran dentro de la matriz cumplen los requisitos de las sumas
//retorno 1 si cumple los requisitos, 0 si no los cumple
int revisarCuadrado(int pos1,int pos2,int pos3,int pos4,int pos5,int pos6,int pos7,int pos8,int pos9){
	
	int fila1,fila2,fila3; //para revisar la suma de sus filas
	int columna1,columna2,columna3; //para revisar la suma de sus columnas
	int diagonalMayor,diagonalMenor; //para revisar la suma de las diagonales del cuadrado

	//aqui hago la suma de las filas
	fila1=pos1+pos2+pos3;
	fila2=pos4+pos5+pos6;
	fila3=pos7+pos8+pos9;
	//aqui hago la suma de las columnas
	columna1=pos1+pos4+pos7;
	columna2=pos2+pos5+pos8;
	columna3=pos3+pos6+pos9;
	//aqui hago las sumas de las diagonales
	diagonalMayor=pos1+pos5+pos9;
	diagonalMenor=pos7+pos5+pos3;
	//una vez creadas todas las sumas, reviso todas las filas, todas las columnas y las diagonales
	if((fila1==fila2)&&(fila1==fila3)){ //si las tres filas son iguales, revisare si sus columnas es igual a sus filas
		if((fila1==columna1)&&(columna1==columna2)&&(columna1==columna3)){ //si las tres columnas son iguales y su columna1 es igual a fila 1, entonces la suma de filas es igual a suma de columnas
			if((fila1==diagonalMayor)&&(diagonalMayor==diagonalMenor)){//si se cumple que sus diagonales sean iguales y a su vez iguales a sus fila, entonces filas,columnas y diagonales dan el mismo resultado 
				return 1; //como cumple todo, retorno un 1
			}
		}
		else{
			return 0;//en caso de que no cumpla retorno 0
		}
	}
	else{
		return 0;//en caso de que no cumpla retorno 0
	}
	return 0;
}
//esta funcion crea la matriz cuadrada de tamanio (n)
int** crearMatriz(int tamanio){
	int i;
	int** matriz=(int**)malloc(sizeof(int*)*tamanio);
	for(i=0;i<tamanio;i++){
		matriz[i]=(int*)malloc(sizeof(int)*tamanio);
	}
	return matriz;
}
//esta funcion agrega la una matriz solucion al array soluciones
int *** agregarSolucion(int *** conjunto, int * cantElementos, int ** solucion,int tamanio){
	//Se crea el nuevo conjunto de soluciones
	
	int*** conjuntoNuevo = (int ***)malloc(sizeof(int**)*(*cantElementos+1));
	int i,j;
	for (i = 0; i < *cantElementos+1; i++){
		conjuntoNuevo[i] = (int **)malloc(sizeof(int *)*3);
		for (j = 0; j < 3; j++){
			conjuntoNuevo[i][j] = (int *)malloc(sizeof(int)*3);
		}
	}
	//Se copian las soluciones existentes
	int numSolucion;
	int ejeX,ejeY;
	for (numSolucion = 0; numSolucion < *cantElementos; numSolucion++){
		for(ejeX = 0; ejeX < tamanio; ejeX ++){
			for (ejeY = 0; ejeY < tamanio; ejeY++){
				conjuntoNuevo[numSolucion][ejeX][ejeY] = conjunto[numSolucion][ejeX][ejeY];
			}
		}
	}
	//Se agrega la nueva solución
	int ejeXSol,ejeYSol;
	for (ejeXSol = 0; ejeXSol < tamanio; ejeXSol++){
		for (ejeYSol = 0; ejeYSol < tamanio; ejeYSol++){
			conjuntoNuevo[*cantElementos][ejeXSol][ejeYSol] = solucion[ejeXSol][ejeYSol];
		}
	}
	*cantElementos = *cantElementos+1;//Se actualiza la cantidad de elementos
	free(conjunto);//Se libera memoria del conjunto de soluciones que ya no se utilizará
	return conjuntoNuevo;
}

//esta funcion muestra una matriz entregada
void mostrarMatriz(int ** matriz){
	int i,j;
	int suma;
	suma=matriz[0][0]+matriz[0][1]+matriz[0][2];
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
	printf("suma: %d\n\n",suma);
}
//esta funcion llama a mostrarMatriz n veces, la cual se encarga de mostrar una matriz en particular
void mostrarSoluciones(int***Soluciones,int canSoluciones){ 
	printf("las soluciones son:\n");
	int i;
	for(i=0;i<canSoluciones;i++){
		printf("solucion %d\n",i+1);
		mostrarMatriz(Soluciones[i]);
		
	}
	printf("\n\n");
}
//esta funcion revisa si los valores que van dentro de una matriz son un solo digito (por ejemplo matriz repleta de 1's )
//retorna 1 en caso de ser True (todos iguales), y 0 en caso de ser False(distintos)
int Digitos(int pos1,int pos2,int pos3,int pos4,int pos5,int pos6,int pos7,int pos8,int pos9){
	if((pos1==pos2) && (pos2==pos3) && (pos3==pos4) && (pos4==pos5) && (pos6==pos7) && (pos7==pos8) && (pos8==pos9)){
		return 1;//todos iguales
	}
	else{
		return 0;//almenos uno distinto
	}
}
//esta funcion revisa si una matriz dada tiene una traspuesta dentro de una lista de matrices
//retorno 0 en caso de no tener transpuesta, y 1 en caso de tener transpuesta
int estaTranspuesta(int** matriz,int***Soluciones,int canSoluciones){
	if(canSoluciones==0){//si la lista esta vacia entonces la matriz no tendra una transpuesta dentro de esta lista
		return 0;
	}
	else{
		//copio la matriz en las  variables pos siguientes
		int pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9;
		pos1=matriz[0][0];
		pos2=matriz[0][1];
		pos3=matriz[0][2];
		pos4=matriz[1][0];
		pos5=matriz[1][1];
		pos6=matriz[1][2];
		pos7=matriz[2][0];
		pos8=matriz[2][1];
		pos9=matriz[2][2];
		//ahora mediante un for recorrele las matrices comparando con esta matriz
		int numero;//para recorrer el for
		for(numero=0;numero<canSoluciones;numero++){//con este for recorro la lista de matrices
			//este if revisa las posiciones con la matriz
			if(((pos1)==(Soluciones[numero][0][0]))&&((pos2)==(Soluciones[numero][1][0]))&&((pos3)==(Soluciones[numero][2][0]))&&((pos4)==(Soluciones[numero][0][1]))&&((pos5)==(Soluciones[numero][1][1]))&&((pos6)==(Soluciones[numero][2][1]))&&((pos7)==(Soluciones[numero][0][2]))&&((pos8)==(Soluciones[numero][1][2]))&&((pos9)==(Soluciones[numero][2][2]))){
				//en caso de que encuentre una matriz donde todo esto sea igual, retornare un 1
				//yaque sera la misma matriz pero transpuesta
				return 1;
			}
		}
		return 0; //con esto si recorro todo el for y no encuentro una matriz transpuesta retorno 0
	}
}
//esta funcion revisa que todos los valores entregados (valores que iran en la matriz) sean distintos entre si
//retorno 0 si no son distintos, retorno 1 en caso de ser distintos
int Distintos(int pos1,int pos2,int pos3,int pos4,int pos5,int pos6,int pos7,int pos8,int pos9){
	if((pos1!=pos2)&&(pos1!=pos3)&&(pos1!=pos4)&&(pos1!=pos5)&&(pos1!=pos6)&&(pos1!=pos7)&&(pos1!=pos8)&&(pos1!=pos9)){//si todos los valores son distintos a pos1
		if((pos2!=pos3)&&(pos2!=pos4)&&(pos2!=pos5)&&(pos2!=pos6)&&(pos2!=pos7)&&(pos2!=pos8)&&(pos2!=pos9)){//todos los valores distintos a pos 2
			if((pos3!=pos4)&&(pos3!=pos5)&&(pos3!=pos6)&&(pos3!=pos7)&&(pos3!=pos8)&&(pos3!=pos9)){//todos los valores distintos a pos3
				if((pos4!=pos5)&&(pos4!=pos6)&&(pos4!=pos7)&&(pos4!=pos8)&&(pos4!=pos9)){//todos los valores distintos a pos4
					if((pos5!=pos6)&&(pos5!=pos7)&&(pos5!=pos8)&&(pos5!=pos9)){//todos los valores distintos a pos5
						if((pos6!=pos7)&&(pos6!=pos8)&&(pos6!=pos9)){//todos los valores distintos a pos6
							if((pos7!=pos8)&&(pos7!=pos9)){//todos los valores distintos a pos7
								if((pos8!=pos9)){//todos los valores distintos a pos8
									return 1; //en caso de que un solo if no se cumpla quiere decir que hay  almenos 2 valores iguales
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;//su no llega al return 1 quiere decir que un if no se cumplio asique retorno 0
}
void cuadradoMagico(){
	int m;//valor maximo para posicion matriz[i][j]
	int canSoluciones=0;//es la cantidad de soluciones la cual ira aumentando en caso de encontrar soluciones
	int*** Soluciones = (int ***)malloc(sizeof(int**)*(canSoluciones));//este array almacenara las soluciones encontradas
	
	printf("ingrese el valor maximo (m) : ");
	scanf("%d",&m);
	printf("\n");
	//aqui creare las posibles matrices mediante ciclos iterativos
	int** matriz; //esta es la matriz sin ser creada aun
	int cumple;//esta variable tomara valores 0 o 1 
	int soloUnDigito;
	int variosDigitos;
	int pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9;//estas variables sirven para cada for que representan cada posicion [i][j] siendo pos1 [0][0]
	for(pos1=1;pos1<=m;pos1++){
		for(pos2=1;pos2<=m;pos2++){
			for(pos3=1;pos3<=m;pos3++){
				for(pos4=1;pos4<=m;pos4++){
					for(pos5=1;pos5<=m;pos5++){
						for(pos6=1;pos6<=m;pos6++){
							for(pos7=1;pos7<=m;pos7++){
								for(pos8=1;pos8<=m;pos8++){
									for(pos9=1;pos9<=m;pos9++){
										//reviso si los valores pos cumplen con los siguientes parametros
										//revisar cuadrado es revisar la suma de sus filas columnas y diagonales
										cumple=revisarCuadrado(pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9);
										//la funcion digitos verifica si todos los valores son iguales
										soloUnDigito=Digitos(pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9);
										//la funcion distintos revisa que todos los digitos sean distintos
										variosDigitos=Distintos(pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9);
										if((cumple==1)&&(soloUnDigito==0)&&(variosDigitos==1)){//si cumple toma el valor de 1, y soloUnDigito es 0,entonces creo la matriz 
											//creo una nueva matriz cada vez que se cambia un valor
											matriz=crearMatriz(3);
											//lleno la matriz con los valores actuales
											matriz[0][0]=pos1;
											matriz[0][1]=pos2;
											matriz[0][2]=pos3;
											matriz[1][0]=pos4;
											matriz[1][1]=pos5;
											matriz[1][2]=pos6;
											matriz[2][0]=pos7;
											matriz[2][1]=pos8;
											matriz[2][2]=pos9;
											//ahora revisare si la matriz creada esta transpuesta
											if(estaTranspuesta(matriz,Soluciones,canSoluciones)==0){
												Soluciones=agregarSolucion(Soluciones,&canSoluciones,matriz,3);
											}
											else{//si ya esta transpuesta entonces hago free de la matriz y genero otra cuando sea necesario
												free(matriz[0]);
												free(matriz[1]);
												free(matriz[2]);
											}
										}
									}
								}
							}
						}
					}
				}	
			}
		}
	}
	if(canSoluciones>0){
		mostrarSoluciones(Soluciones,canSoluciones);//aqui muestro las soluciones
		//limpio la memoria
		int i,j;
		for(i=0;i<canSoluciones;i++){
			for(j=0;j<3;j++){
				free(Soluciones[i][j]);
			}
		}
	}
	else{
		printf("no se encontraron soluciones\n\n\n");
	}
	
	
	//////
	//fin de cuadradoMagico
	//////
}

int funcionMenu(){
	char opcion;
	printf("1) Canibales y misioneros\n2) Cuadrado magico\n3) Salir\nIngrese opcion: ");
	scanf("%c",&opcion);

	if(opcion=='1'){
		printf("\nCanibales y misioneros\n");
		canibales();
		char opcion;
		return 0;
	}
	else{
		if(opcion=='2'){
			printf("\nCuadrado magico\n");
			cuadradoMagico();
			char opcion;
			return 0;
		}
		else{
			if(opcion=='3'){
				printf("\nsalir\n");
				char opcion;
				return 1;
			}
			else{
				printf("\nopcion no valida\n");
				char opcion;
				return 0;
			}
		}
	}
}

int main(){
  int validar=0;
  while(validar==0){
    validar=funcionMenu();
  }
	return 0;
}