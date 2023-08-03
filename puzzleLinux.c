#include <stdio.h>
#include <stdlib.h>
#include "globales.h"

/*#ifdef _WIN32      ESTA ES OTRA FORMA DE LIMPIAR LA PANTALLA DE LA CONSOLA (PARA LA FUNCION MOSTRAR TABLERO COMPLETO)
#include <conio.h>
#endif
#ifdef linux
#define clrscr() printf("\033[H\033[2J")
#endif*/

int main(){

    int result = 1;
    do {
        x = 0;
        y = 0;
        indPartida++;
        obtenerPartida();
        mostrarTablero();
        apuesta = leerApuesta();
        movimientos = 0;
        do {
            mostrarTableroCompleto();
            result = ejecutarMov();
            if (result == 3)
                printf("El caracter es incorrecto \n");
            //result = ejecutarMov();
            if (result == 1)
                movimientos++;
            if(iguales()){
                mostrarTableroCompleto();
                printf("Puzzle resuelto!\n");
                mostrarPuntaje();
                guardarPartida();
                mostrarHistorial();
                result = contJuego();
            }
        } while (result!= 0 && result!= -1);
    } while(result!= 0);
    return 0;
}

void obtenerPartida()
{
    srand(time(NULL));
    int randomIndex = rand() % NUM_PARTIDAS;

    int k = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matriz[i][j] = inicPartidas[randomIndex][k++];
        }
    }
}


void mostrarTableroCompleto() {
    /*#ifdef linux    ESTO COMPLEMENTA LO QUE ESTÁ AL PRINCIPIO DEL CÓDIGO COMENTADO
    clrscr();
    #endif
    #ifdef _WIN32
    system("cls");
    #endif*/
    system("clear");     // ESTA FUNCIÓN REEMPLAZA TODO ESE CHORIZO DE COSAS COMENTADAS
    mostrarTablero();
    printf("Apuesta: %i     Movimientos: %i      Quedan: %i \n", apuesta, movimientos, apuesta - movimientos);
    printf("Utiliza las teclas W A S D para moverte por el tablero. 0 para finalizar, N para nuevo juego.\n");
}

void mostrarTablero()
{
    for(int i = 0; i < 4; i++){
        printf("\n");
        for(int j = 0; j < 4; j++){
            if(matriz[i][j] == 0)
                printf("[  ]");
            else
                printf("[%2i]", matriz[i][j]);
        }
    }
    printf("\n\n");
}

int leerApuesta(){
    do {
       printf("Cantidad de mov para resolver el puzzle (entre 40 y 200): ");
       scanf("%d", &cantMovParticipante);
    } while(cantMovParticipante<40 || cantMovParticipante>200);
    return cantMovParticipante;
}

int ejecutarMov()    //DENTRO DE ESTA FUNCIÓN SE ENCUENTRA EL ERROR QUE NO SE SOLUCIONAR.
{                    // CREO QUE TIENE QUE VER CON EL GETCHAR() (PARA WINDOWS USO EL GETCH() Y ANDA DE LO MÁS BIEN)
    int retVal = 1;  // MÁS ABAJO ESTÁ QUÉ ES LO QUE NO FUNCA
    char caracter = getchar();
    caracter = tolower(caracter);
    switch (caracter){
        case 'w':
            if(y <= 2){
                matriz[y][x]= matriz[y+1][x];
                matriz[y+1][x] = 0;
                y++;
            } else retVal = 2;
        break;
        case 's':
            if(y >= 1){
                matriz[y][x]= matriz[y-1][x];
                matriz[y-1][x] = 0;
                y--;
            } else retVal = 2;
        break;
        case 'a':
            if(x <= 2){
                matriz[y][x]= matriz[y][x+1];
                matriz[y][x+1] = 0;
                x++;
            } else retVal = 2;
        break;
        case 'd':
            if(x >= 1){
                matriz[y][x]= matriz[y][x-1];
                matriz[y][x-1] = 0;
                x--;
            } else retVal = 2;
        break;
        case '0':
            retVal = 0;
        break;
        case 'n':
            retVal = -1;
        break;
        case 'p':
            igualar();
        break;
        default:          //POR ALGUNA RAZÓN NO TOMA ESTE DEFAULT O LO TOMA MAL, SEGÚN EN DONDE SE ENCUENTRE
            retVal = 3;   // EL RESULT = EJECUTARMOV(). SI ESTÁ EN LA LINEA 25 (COMO ESTÁ AHORA), NO LO TOMA EL IF INMEDIATO
        break;            // SI ESTÁ EN LA LINEA 28, LO TOMA PERO IMPRIME TODO EL TIEMPO EL CARTEL DE QUE EL CARACTER ES INCORRECTO

    }
    return retVal;
}

int iguales()
{
    int sonIguales = 1;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (matriz[i][j] != matrizResuelta[i][j]){
                sonIguales = 0;
                break;
            }
        }
    }
    return sonIguales;
}

int igualar()
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matriz[i][j] = matrizResuelta[i][j];
        }
    }
}

int mostrarPuntaje()
{
    if (iguales())
    {
        if (movimientos >= apuesta-10 || movimientos < apuesta){
            puntos = 1200;
        } if(movimientos > apuesta || movimientos <= apuesta+10){
            puntos = 500;
        } if(movimientos == apuesta){
            puntos = 1000;
        } if (movimientos < apuesta-10){
            puntos = 1500;
        }
        printf("Puntaje obtenido: %d", puntos);
    }
}

int contJuego()
{
    printf("\nDesea jugar otra partida? (S/N)");
    char caracter = 0;
    while (caracter != 's' && caracter != 'n'){
        caracter = getchar();
        caracter = tolower(caracter);
    }
    if (caracter == 's')
        return -1;
    else
        return 0;
}


int guardarPartida()
{
        historial[indPartida][0] = apuesta;
        historial[indPartida][1] = movimientos;
        historial[indPartida][2] = puntos;
}

int mostrarHistorial()
{
    printf("\nPart nro:  |Apuesta:  |Movimientos:  |Puntaje:");
    for(int x = 0; x <= indPartida; x++){
        printf("\n%4i       |%4i      |%4i          |%4i", x+1, historial[x][0], historial[x][1], historial[x][2]);
    }
}


