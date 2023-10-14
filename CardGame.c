#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct carta{
	char nombre[70];
	char clase[50];
	int puntos_vida;
	int puntos_ataque;
	int puntos_defensa;
	struct carta *siguiente;
} Carta;
typedef struct jugador{
	char nombre[60];
	int vidas;
	Carta *Mazo_propio[15];
} Jugador;
#define linea_max 100
Carta* crear_carta(char *nombre, char *clase, int puntos_vida, int puntos_ataque, int puntos_defensa) {
    Carta *nueva_carta = (Carta*)malloc(sizeof(Carta));
    strcpy(nueva_carta->nombre, nombre);
    strcpy(nueva_carta->clase, clase);
    nueva_carta->puntos_vida = puntos_vida;
    nueva_carta->puntos_ataque = puntos_ataque;
    nueva_carta->puntos_defensa = puntos_defensa;
    nueva_carta->siguiente = NULL;
    return nueva_carta;
}
void leer_archivo(Carta **cabeza, Carta **cola){	//void para hacer la lectura del archivo texto 
	FILE *file = fopen("Cartas.txt", "r");
	if (file == NULL){
		perror("Error al abrir el archivo.");
		return;
	}
	char linea[linea_max];
	Carta *nueva_carta;
    Carta *ultimo = NULL;
	while(fgets(linea, linea_max, file)){

        Carta *nueva_carta = (Carta*)malloc(sizeof(Carta));

        strcpy(nueva_carta->nombre, strtok(linea, ","));
        strcpy(nueva_carta->clase, strtok(NULL, ","));
        nueva_carta->puntos_vida = atoi(strtok(NULL, ","));
        nueva_carta->puntos_ataque = atoi(strtok(NULL, ","));
        nueva_carta->puntos_defensa = atoi(strtok(NULL, ","));
		
        if (*cabeza == NULL) {
            *cabeza = nueva_carta;
            ultimo = nueva_carta;
        } else {
            ultimo->siguiente = nueva_carta;
            ultimo = nueva_carta;
        }
    }
    fclose(file);
}
void print_cartas(Carta *cabeza) {	//void para imprimir las cartas en pantalla
    printf("Lista de cartas:\n");
    Carta *current = cabeza;
    int contador_print = 1;
    while (current != NULL) {
        printf("%d)Nombre: %s, Clase: %s, Vida: %d, Ataque: %d, Defensa: %d\n",contador_print, current->nombre ,current->clase,current->puntos_vida, current->puntos_ataque, current->puntos_defensa);
        current = current->siguiente;
        contador_print++;
    }
}
void revolver_mazo(Carta **cabeza){		//void para revolver el mazo de cartas
	int contador_revolver=0;
	int i;
	Carta *current = *cabeza;
	
	while(current!=NULL){
		contador_revolver++;
		current= current->siguiente;
	}
	Carta **cartas= malloc(contador_revolver * sizeof(Carta *));
	current = *cabeza;
	
	for(i=0; i<contador_revolver; i++){		//Colocar las cartas en el arreglo
		cartas[i]= current;
		current = current->siguiente;
	}
	for(i=contador_revolver-1; i>=0; i--){
		int k = rand()%(i+1);
		Carta *aux =cartas[i];
		cartas[i]= cartas[k];
		cartas[k]= aux;
	}
	*cabeza = cartas[0];
	current = *cabeza;
	for(i=1; i<contador_revolver; i++){
		current->siguiente = cartas[i];
		current = current->siguiente;
	}
	current->siguiente=NULL;
	free(cartas);
}
void jugador_pc(){
	
}
int main(){
	
	
	/*1) carta *current = *cabeza. 2) contador en 0. 3)while hasta que current sea NULL. 4)arreglo para almacenar la posicion.
	5)copiar posicion en el arreglo 6)for con tamaño del contador */
	Carta *cabeza = NULL;
    Carta *cola = NULL;
    Carta *nueva_carta;
    Carta *nueva_carta_Cola;
    leer_archivo(&cabeza,&cola);
    print_cartas(cabeza);
	
	int opcion=0; //Variable que maneja el menu del juego
	
	srand(time(NULL)); 
	while(opcion!=4){ //Menu del juego
		printf("\nBienvenido al juego The clash of the guardians.\n");
		printf("Que desea realizar?\n");
		printf("1.Crear una nueva carta.\n2.Comenzar el juego.\n3.Historial de partida.\n4.Salir\n");
		printf("Escoga una opcion entre 1 y 4: ");
		scanf("%d",&opcion);
		if(opcion==1){
			revolver_mazo(&cabeza);
			print_cartas(cabeza);
		}
		if(opcion==2){
			//print_cartas(cabeza);
		}
		if(opcion==3){
			
		}
	}
	
	
	
	return 0;
}
