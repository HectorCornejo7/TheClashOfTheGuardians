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
	Carta *Mazo_mano[15];
	Carta *Mazo_mesa[30];
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
void entregar_cartas(Carta *cabeza,Jugador *jugadores){
	int i;
	int contador_entregar=1;
	Carta *current=cabeza;
	
	for(i=0; i<15; i++){
		jugadores[0].Mazo_propio[i]= current;
		current= current->siguiente;
	}
	for(i=0; i<15; i++){
		jugadores[1].Mazo_propio[i]= current;
		current= current->siguiente;
	}
	
	current = cabeza;
	printf("\nLista de cartas del usuario: \n");
	for(i=0; i<15; i++){
    	printf("%d)Nombre: %s, Clase: %s, Vida: %d, Ataque: %d, Defensa: %d\n",contador_entregar, current->nombre ,current->clase,current->puntos_vida, current->puntos_ataque, current->puntos_defensa);
    	current = current->siguiente;
    	contador_entregar++;
	}
	printf("\nLista de cartas de la maquina:\n");
	contador_entregar= 1;
	for(i=0; i<15; i++){
    	printf("%d)Nombre: %s, Clase: %s, Vida: %d, Ataque: %d, Defensa: %d\n",contador_entregar, current->nombre ,current->clase,current->puntos_vida, current->puntos_ataque, current->puntos_defensa);
    	current = current->siguiente;
    	contador_entregar++;
	}
}
void escoger_3cartasPC(Jugador *jugadores){
	int i,j;
	int carta_por_escogerPC;	//Contador
    int carta_escogidaPC[3];	//Posiciones de la carta escogida por la maquina en el turno
    
    for (i = 0; i < 3; i++) {
        carta_escogidaPC[i] = rand() % 15; // Números aleatorios del 0 al 14
    }
	
	for(i=0; i<3; i++){
		
		//Se copia lo de un mazo a otro segun las cartas que escogio la maquina
		jugadores[1].Mazo_mano[i] = (Carta*)malloc(sizeof(Carta));
		strcpy(jugadores[1].Mazo_mano[i]->nombre, jugadores[1].Mazo_propio[carta_escogidaPC[i]]->nombre);
		strcpy(jugadores[1].Mazo_mano[i]->clase, jugadores[1].Mazo_propio[carta_escogidaPC[i]]->clase);
		jugadores[1].Mazo_mano[i]->puntos_vida = jugadores[1].Mazo_propio[carta_escogidaPC[i]]->puntos_vida;
		jugadores[1].Mazo_mano[i]->puntos_ataque = jugadores[1].Mazo_propio[carta_escogidaPC[i]]->puntos_ataque;
		jugadores[1].Mazo_mano[i]->puntos_defensa = jugadores[1].Mazo_propio[carta_escogidaPC[i]]->puntos_defensa;
		
		//Se eliminan las cartas de su maso 
		for (i = 0; i < 3; i++) {
        eliminar_carta(&jugadores[1], carta_escogidaPC[i]);
    	}
	}
}
void eliminar_carta(Jugador *jugador, int posicion){
	int i;
    free(jugador->Mazo_propio[posicion]);
    for(i = posicion; i < 14; i++){
        jugador->Mazo_propio[i] = jugador->Mazo_propio[i + 1];
    }
    jugador->Mazo_propio[14] = NULL;
}
void escoger_3cartas(Jugador *jugadores){	//escoger las 3 primeras cartas 
	int i,j;
	int carta_por_escoger;	//Numero de carta por escoger a su mazo (las 3 que debe de escoger de su mazo)
    int carta_escogida=1;	//Posicion de la carta escogida por el jugador en el turno
	
	printf("\nEscoga tres cartas de su mazo.\n");
	printf("-Para escoger tiene que indicar la posicion de su carta, osea su numero en la lista.(del 1 al 15)\n");
	printf("Para que salga correcto porfavor escoger de a mayor a menor en cuanto posicion.\n");
	carta_por_escoger=1;
	for(i=0; i<3; i++){
		do{
			printf("Carta numero %d a escoger: ",carta_por_escoger);
			scanf("%d",&carta_escogida);
		}while(carta_escogida >15 || carta_escogida <1);
		carta_por_escoger++;
		carta_escogida= carta_escogida-1;
		
		//Se copia lo de un mazo a otro segun las cartas que escogio el usuario
		jugadores[0].Mazo_mano[i] = (Carta*)malloc(sizeof(Carta));
		strcpy(jugadores[0].Mazo_mano[i]->nombre, jugadores[0].Mazo_propio[carta_escogida]->nombre);
		strcpy(jugadores[0].Mazo_mano[i]->clase, jugadores[0].Mazo_propio[carta_escogida]->clase);
		jugadores[0].Mazo_mano[i]->puntos_vida = jugadores[0].Mazo_propio[carta_escogida]->puntos_vida;
		jugadores[0].Mazo_mano[i]->puntos_ataque = jugadores[0].Mazo_propio[carta_escogida]->puntos_ataque;
		jugadores[0].Mazo_mano[i]->puntos_defensa = jugadores[0].Mazo_propio[carta_escogida]->puntos_defensa;
		
		printf("Carta seleccionada: Nombre: %s, Clase: %s, Vida: %d, Ataque: %d, Defensa: %d\n\n",jugadores[0].Mazo_mano[i]->nombre,
			jugadores[0].Mazo_mano[i]->clase, jugadores[0].Mazo_mano[i]->puntos_vida, jugadores[0].Mazo_mano[i]->puntos_ataque, 
			jugadores[0].Mazo_mano[i]->puntos_defensa);
			
		eliminar_carta(&jugadores[0], carta_escogida);
	}	
	
	printf("Nuestro mazo despues de escoger las cartas:\n");
    for (i = 0; i < 15; i++) {
        if (jugadores[0].Mazo_propio[i] != NULL) {
            printf("%d)Nombre: %s, Clase: %s, Vida: %d, Ataque: %d, Defensa: %d\n", i + 1,
                   jugadores[0].Mazo_propio[i]->nombre, jugadores[0].Mazo_propio[i]->clase,
                   jugadores[0].Mazo_propio[i]->puntos_vida, jugadores[0].Mazo_propio[i]->puntos_ataque,
                   jugadores[0].Mazo_propio[i]->puntos_defensa);
        }
    }
}
void dejar_en_mesa(Jugador *jugador) {
    int carta_a_dejar;
    do {
        printf("Indique el numero de la carta que desea dejar en la mesa(1 a 3): ");
        scanf("%d", &carta_a_dejar);
    } while (carta_a_dejar < 1 || carta_a_dejar > 15);

    //Copiar la carta seleccionada de nuestra mano a la mesa
    jugador[0].Mazo_mesa[carta_a_dejar - 1] = jugador[0].Mazo_mano[carta_a_dejar - 1];

    // Eliminar la carta seleccionada de nuestra mano
    eliminar_carta(jugador, carta_a_dejar - 1);

    printf("\nCarta dejada en la mesa: Nombre: %s, Clase: %s, Vida: %d, Ataque: %d, Defensa: %d\n", jugador[0].Mazo_mesa[carta_a_dejar - 1]->nombre,
        jugador[0].Mazo_mesa[carta_a_dejar - 1]->clase, jugador[0].Mazo_mesa[carta_a_dejar - 1]->puntos_vida,
		jugador[0].Mazo_mesa[carta_a_dejar - 1]->puntos_ataque, jugador[0].Mazo_mesa[carta_a_dejar - 1]->puntos_defensa);
}
void dejar_en_mesaPC(Jugador *jugador) {
    int carta_a_dejarPC = rand() % 15; // Números aleatorios del 0 al 14

    // Verificar si la carta seleccionada aleatoriamente está en la mano del jugador
    while (jugador[1].Mazo_mano[carta_a_dejarPC] == NULL) {
        carta_a_dejarPC = rand() % 15;
    }

    // Copiar la carta seleccionada de la mano a la mesa
    jugador[1].Mazo_mesa[carta_a_dejarPC] = jugador[1].Mazo_mano[carta_a_dejarPC];

    // Eliminar la carta seleccionada de la mano
    eliminar_carta(&jugador[1], carta_a_dejarPC);

    printf("\nCarta dejada en la mesa por la máquina: Nombre: %s, Clase: %s, Vida: %d, Ataque: %d, Defensa: %d\n",
           jugador[1].Mazo_mesa[carta_a_dejarPC]->nombre, jugador[1].Mazo_mesa[carta_a_dejarPC]->clase,
           jugador[1].Mazo_mesa[carta_a_dejarPC]->puntos_vida, jugador[1].Mazo_mesa[carta_a_dejarPC]->puntos_ataque,
           jugador[1].Mazo_mesa[carta_a_dejarPC]->puntos_defensa);
}
int main(){
	
	Carta *cabeza = NULL;
    Carta *cola = NULL;
    Carta *nueva_carta;
    int i;
    int opcion=0; 	//Variable que maneja el menu del juego
    int opcion_juego=0;	  //variable que maneja las decisiones en el juego
	srand(time(NULL));
    leer_archivo(&cabeza,&cola);	//llamamos a la funcion para que nos lea los datos desde el archivo txt
    revolver_mazo(&cabeza);		//funcion para revolver el mazo leido
    
	struct jugador jugadores[2];
    
	strcpy(jugadores[0].nombre,"Usuario");
    jugadores[0].vida_jugador= 5;
    strcpy(jugadores[1].nombre,"Maquina");
    jugadores[1].vida_jugador= 5;
	
	do{ //Menu del juego
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
			entregar_cartas(cabeza,jugadores);
			escoger_3cartas(jugadores);
			escoger_3cartasPC(jugadores);
			while(jugadores[0].vida_jugador>0 && jugadores[1].vida_jugador>0){	//bucle del juego hasta que uno pierda sus vidas
				printf("\nQue desea hacer ahora.\n1)Colocar carta en mesa.\n2)Atacar(solo si hay cartas del contrincante en mesa).\n");
				printf("Escoga una opcion entre 1 o 2: ");
				scanf("%d",&opcion_juego);
				if(opcion_juego==1){
					printf("Okey, que carta quisiera colocar en la mesa.\n");
					dejar_en_mesa(jugadores);
				}
				printf("Turno de la maquina de escoger cartas.");
				dejar_en_mesaPC(jugadores);
				if(opcion_juego==2){
					
				}
			}
		}
		if(opcion==3){
			print_cartas(cabeza);
		}
	}while(opcion<1 || opcion>4);
	
	
	
	return 0;
}
