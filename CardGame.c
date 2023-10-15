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
	int vida_jugador;
	Carta *Mazo_propio[15];
} Jugador;
#define linea_max 100
Carta* crear_carta(Carta **cabeza) {	//funcion para crear una nueva carta
    Carta *nueva_carta = (Carta*)malloc(sizeof(Carta));
    printf("\nIngrese el nombre de su carta(sin espacios): ");
    scanf("%s",nueva_carta->nombre);
    printf("\nIngrese la clase de su carta(sin espacios): ");
    scanf("%s",nueva_carta->clase);
    printf("\nIngrese los puntos de vida de su carta: ");
    scanf("%d",&nueva_carta->puntos_vida);
    printf("\nIngrese los puntos de ataque de su carta: ");
    scanf("%d",&nueva_carta->puntos_ataque);
    printf("\nIngrese los puntos de defensa de su carta: ");
    scanf("%d",&nueva_carta->puntos_defensa);
    nueva_carta->siguiente = NULL;
    
    if(*cabeza==NULL){
    	*cabeza = nueva_carta;
	}
	else{
		Carta *aux = *cabeza;
		while(aux->siguiente != NULL){
			aux = aux->siguiente;
		}
		aux->siguiente=nueva_carta;
	}
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
int main(){
	
	Carta *cabeza = NULL;
    Carta *cola = NULL;
    Carta *nueva_carta;
    int i;
    int opcion=0; 	//Variable que maneja el menu del juego
    //Carta *nueva_carta_Cola;
    leer_archivo(&cabeza,&cola);	//llamamos a la funcion para que nos lea los datos desde el archivo txt
    struct jugador jugadores[2];
    
	strcpy(jugadores[0].nombre,"Usuario");
    jugadores[0].vida_jugador= 5;
    strcpy(jugadores[1].nombre,"Maquina");
    jugadores[1].vida_jugador= 5;
	
	srand(time(NULL));
	print_cartas(cabeza);	//comprobacion de que esten todas las cartas
	while(opcion!=4){ //Menu del juego
		printf("\nBienvenido al juego The clash of the guardians.\n");
		printf("Que desea realizar?\n");
		printf("1.Crear una nueva carta.\n2.Comenzar el juego.\n3.Historial de partida.\n4.Salir\n");
		printf("Escoga una opcion entre 1 y 4: ");
		scanf("%d",&opcion);
		if(opcion==1){
			crear_carta(&cabeza);
			print_cartas(cabeza);
		}
		if(opcion==2){
			
		}
		if(opcion==3){
			//revolver_mazo(&cabeza);
			//print_cartas(cabeza);
		}
	}
	
	
	
	return 0;
}
