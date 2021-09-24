#include <stdio.h>
#include <stdlib.h>
//reviso que cumplan las tripletas y la cantidad de cuadrados "pintados negros" ( 1 es negro, 0 es blanco)
//la tripleta a,b,c sigfinica que la fila 1 tiene "a" cuadrados negros, la fila 2 tiene "b" cuadrados negros y la fila 3 tiene "c" cuadrados negros
//lo mismo para la tripleta d,e,f pero en las columnas
//esto hace que para verificar deba simplemente sumar cuantos cuadrados negros tengo
int verificarSolucion(int a,int b,int c,int d,int e,int f, int ** matriz){
	int fila1,fila2,fila3,columna1,columna2,columna3;
	fila1=matriz[0][0] + matriz[0][1] + matriz[0][2];
	fila2=matriz[1][0] + matriz[1][1] + matriz[1][2];
	fila3=matriz[2][0] + matriz[2][1] + matriz[2][2];
	columna1=matriz[0][0] + matriz[1][0] + matriz[2][0];
	columna2=matriz[0][1] + matriz[1][1] + matriz[2][1];
	columna3=matriz[0][2] + matriz[1][2] + matriz[2][2];
	//ahora compruebo que todo se cumpla ya que un 1 significa negro, por ejemplo si mi "a" es 3 y fila1 vale 3 entonces se cumple
    if((a == fila1)&&(b == fila2)&&(c == fila3)&&(d == columna1)&&(e == columna2)&&(f == columna3)){
        return 1;
    }
	else{
		return 0; //No cumple la condicion de las tripletas
	}
}
//esta funcion crea un array nuevo de tamanio+1 que el array ingresado en parametros y agrega una matriz al final del nuevo array
int *** agregarSolucion(int *** conjunto, int * cantElementos, int ** solucion){
	//Se crea el nuevo conjunto de soluciones
	int*** conjuntoNuevo = (int ***)malloc(sizeof(int**)*(*cantElementos+1));
	int i,j;
	for ( i = 0; i < *cantElementos+1; i++){
		conjuntoNuevo[i] = (int **)malloc(sizeof(int *)*3);
		for ( j = 0; j < 3; j++){
			conjuntoNuevo[i][j] = (int *)malloc(sizeof(int)*3);
		}
	}
	//Se copian las soluciones existentes
	int numSolucion,ejeX,ejeY;
	for ( numSolucion = 0; numSolucion < *cantElementos; numSolucion++){
		for( ejeX = 0; ejeX < 3; ejeX ++){
			for ( ejeY = 0; ejeY < 3; ejeY++){
				conjuntoNuevo[numSolucion][ejeX][ejeY] = conjunto[numSolucion][ejeX][ejeY];
			}
		}
	}
	//Se agrega la nueva solución
	int ejeXSol,ejeYSol;
	for ( ejeXSol = 0; ejeXSol < 3; ejeXSol++){
		for ( ejeYSol = 0; ejeYSol < 3; ejeYSol++){
			conjuntoNuevo[*cantElementos][ejeXSol][ejeYSol] = solucion[ejeXSol][ejeYSol];
		}
	}
	*cantElementos = *cantElementos+1;//Se actualiza la cantidad de elementos
	free(conjunto);//Se libera memoria del conjunto de soluciones que ya no se usara
	return conjuntoNuevo;
}
//funcion que asigna memoria a un array de arrays
int ** crearMatriz(){
	int ** matriz = (int **)malloc(sizeof(int*)*3);
	int i;
	for (i = 0; i < 3; i++){
		matriz[i] = (int *)malloc(sizeof(int)*3);
	}
	return matriz;
}

//esta funcion imprime matrices de un array de matrices 
void imprimirSoluciones(int *** soluciones, int cantidadSoluciones){
	int nSol,i,j;
	for(nSol = 0; nSol < cantidadSoluciones; nSol ++){
		printf("Solucion N=%d\n", nSol);
		for (i = 0; i < 3; i++){
			for (j = 0; j < 3; j++){
				printf("%d ", soluciones[nSol][i][j]);
			}
			printf("\n");
		}
	}
}

int main(){
    int a,b,c;//primera tripleta(filas)
    int d,e,f;//segunda tripleta(columnas)
    printf("Ingrese los numeros de la tripleta filas: por ejemplo si la tripleta es (1,2,3) ingresar 1,2,2 Separado por comas\n");
    scanf("%d,%d,%d", &a,&b,&c);
    printf("Ingrese los numeros de la tripleta columnas: por ejemplo si la tripleta es (1,2,3) ingresar 1,2,3 Separado por comas\n");
    scanf("%d,%d,%d", &d,&e,&f);
    //creo las variables que almacenaran el numero 0 o 1 representando blanco o negro respectivamente
	//siendo casilla1 la posicion 0,0 de la matriz, casilla 2 la posicion 0,1 y asi respectivamente
    int casilla1,casilla2,casilla3,casilla4,casilla5,casilla6,casilla7,casilla8,casilla9; 
    int cantidadSoluciones = 0;//defino cantidadSoluciones como 0 ya que aun no genero ninguna
	int *** conjuntoSoluciones = (int ***)malloc(sizeof(int**)*cantidadSoluciones);//creo mi conjunto soluciones el cual se genera vacio actualmente
    int ** matriz;//defino matriz, pero aun no le asigno memoria
	
    //mediante 9 ciclos for anidados genero todas las posibilidades de matrices (incluso las inviables como tripletas 0,0,0 y 1,1,1)
	//sin embargo solo agrego a mi conjunto soluciones las tripletas validas ( cumplan con verificar solucion)
    for(casilla1=0;casilla1<=1;casilla1++){
        for(casilla2=0;casilla2<=1;casilla2++){
            for(casilla3=0;casilla3<=1;casilla3++){
                for(casilla4=0;casilla4<=1;casilla4++){
                    for(casilla5=0;casilla5<=1;casilla5++){
                        for(casilla6=0;casilla6<=1;casilla6++){
                            for(casilla7=0;casilla7<=1;casilla7++){
                                for(casilla8=0;casilla8<=1;casilla8++){
                                    for(casilla9=0;casilla9<=1;casilla9++){
                                        //asigno la memoria a matriz
                                        matriz = crearMatriz();
										//lleno las posiciones de matriz
                                        matriz[0][0] = casilla1;
					                    matriz[0][1] = casilla2;
					                    matriz[0][2] = casilla3;
					                    matriz[1][0] = casilla4;
					                    matriz[1][1] = casilla5;
					                    matriz[1][2] = casilla6;
					                    matriz[2][0] = casilla7;
					                    matriz[2][1] = casilla8;
                                        matriz[2][2] = casilla9;
                                        //verifico que esta matriz cumpla con las tripletas
                                        if(verificarSolucion(a,b,c,d,e,f,matriz) == 1){
                                            //si la matriz creada cumple, la agrego en soluciones
                                            conjuntoSoluciones = agregarSolucion(conjuntoSoluciones, &cantidadSoluciones, matriz);
                                        } 
										else{//si la matriz no cumple con los requisitos de verificar solucion entonces libero la memoria de esta matriz
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
	//una vez terminan los ciclos for, reviso si la cantidad de soluciones ha cambiado y dependiendo de su valor entrego una respuesta al usuario
    if(cantidadSoluciones == 0){
        printf("no hay solucion para las tripletas \n");
        return 0;
    } 
    if(cantidadSoluciones == 1){
        printf("las tripletas ingresadas tienen solucion unica \n");
        imprimirSoluciones(conjuntoSoluciones,cantidadSoluciones);
        return 0;
    }
    if(cantidadSoluciones > 1){
        printf("las tripletas ingresadas tienen multiples soluciones \n");
        imprimirSoluciones(conjuntoSoluciones,cantidadSoluciones);
		return 0;
    }
}