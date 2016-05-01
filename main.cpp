#include <winbgim.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <conio.h>
#include <ctype.h>
#include "Grafo.h"
#include "LinkedList.h"

#define ENTRADA 0
#define SALIDA 1
#define TESORO 2
#define NORMAL 3

using namespace std;

LinkedList<int> *grafo;
int *tesoros;
int posX;
int posY;
int nodoActual;
int color;
int ancho;
int alto;
int cantidadTesoros;
int salida;
LinkedList<int> caminoDijkstra;

void temporizador(){
    int S;
    for(S=100; S >= 0; ){
        cout<<S--;
        Sleep(999);
        system("cls" );
    }
}

void pintarDijkstra(int colorDijkstra){
    int tempX = posX;
    int tempY = posY;
    int nodoActualTemp = nodoActual;
    int i;
    setfillstyle(1,colorDijkstra);
    caminoDijkstra.goToStart();
    for(i=0;i<caminoDijkstra.getSize();i++){
        if(caminoDijkstra.getElement() == nodoActualTemp - ancho){
            tempY -=20;
            if(tesoros[caminoDijkstra.getElement()] != TESORO && tesoros[caminoDijkstra.getElement()] != SALIDA)bar(tempX+10,tempY+10,tempX,tempY);
            bar(tempX+10,tempY+20,tempX,tempY+10);
        }
        if(caminoDijkstra.getElement() == nodoActualTemp + ancho){
            tempY +=20;
            if(tesoros[caminoDijkstra.getElement()] != TESORO && tesoros[caminoDijkstra.getElement()] != SALIDA)bar(tempX+10,tempY+10,tempX,tempY);
            bar(tempX+10,tempY,tempX,tempY-10);
        }
        if(caminoDijkstra.getElement() == nodoActualTemp - 1){
            tempX -=20;
            if(tesoros[caminoDijkstra.getElement()] != TESORO && tesoros[caminoDijkstra.getElement()] != SALIDA)bar(tempX+10,tempY+10,tempX,tempY);
            bar(tempX+20,tempY+10,tempX+10,tempY);
        }
        if(caminoDijkstra.getElement() == nodoActualTemp + 1){
            tempX +=20;
            if(tesoros[caminoDijkstra.getElement()] != TESORO && tesoros[caminoDijkstra.getElement()] != SALIDA)bar(tempX+10,tempY+10,tempX,tempY);
            bar(tempX,tempY+10,tempX-10,tempY);
        }
        nodoActualTemp = caminoDijkstra.getElement();
        caminoDijkstra.next();

    }

}

void insertarEnCaminoDijkstra(int *nodoProveniente, int nodo){
    caminoDijkstra.insert(nodo);
    if(nodoProveniente[nodo] != nodoActual)insertarEnCaminoDijkstra(nodoProveniente,nodoProveniente[nodo]);
}

bool existenDistanciasDefinitivas(bool *distanciasDefinitivas){
    int i;
    for(i = 0; i<(ancho*alto);i++){
        if(!distanciasDefinitivas[i]) return true;
    }
    return false;
}

int obtieneMenor(int *distancias, bool *distanciasDefinitivas){
    int i;
    int menor = 99999;
    int menorIndice;
    for(i = 0; i < (ancho*alto); i++){
        if(distancias[i] < menor && !distanciasDefinitivas[i]){
            menor = distancias[i];
            menorIndice = i;
        }
    }
    return menorIndice;
}

void dijkstra(){

    int posActual = nodoActual;
    int vecino;
    int distanciaAcumulada;

    int distancias[ancho*alto];
    int contadorDistancias;
    for(contadorDistancias = 0; contadorDistancias < (ancho * alto); contadorDistancias++){
        if(contadorDistancias == nodoActual) distancias[contadorDistancias] = 0;
        else distancias[contadorDistancias] = 99999;
    }

    int nodoProveniente[ancho*alto];
    int contadorProveniente;
    for(contadorProveniente = 0; contadorProveniente < (ancho * alto); contadorProveniente++){
        if(contadorProveniente == nodoActual) nodoProveniente[contadorProveniente] = nodoActual;
        else nodoProveniente[contadorProveniente] = 99999;
    }

    bool distanciasDefinitivas[ancho*alto];
    int contadorDefinitivas;
    for(contadorDefinitivas = 0; contadorDefinitivas < (ancho * alto); contadorDefinitivas++){
        if(contadorDefinitivas == nodoActual) distanciasDefinitivas[contadorDefinitivas] = true;
        else distanciasDefinitivas[contadorDefinitivas] = false;
    }
    while(existenDistanciasDefinitivas(distanciasDefinitivas)){
        grafo[posActual].goToStart();
        int i = 0;
        while(i < 4){
            vecino = grafo[posActual].getElement();
            if(vecino != -1 && !distanciasDefinitivas[vecino]){
                distanciaAcumulada = distancias[posActual] + 1;
                if(distanciaAcumulada < distancias[vecino]){
                    distancias[vecino] = distanciaAcumulada;
                    nodoProveniente[vecino] = posActual;
                }
            }
            grafo[posActual].next();
            i++;
        }
        posActual = obtieneMenor(distancias, distanciasDefinitivas);
        distanciasDefinitivas[posActual] = true;
    }
    caminoDijkstra.clear();
    insertarEnCaminoDijkstra(nodoProveniente,salida);
    pintarDijkstra(7);
}

bool tieneTodosLosTesoros(){
    int conti;
    for(conti = 0;conti < (ancho*alto); conti++){
        if(tesoros[conti] == TESORO) return false;
    }
    return true;
}

void jugar(){
    bool noHaGanado = true;
    posX = 10;
    posY = 10;
    nodoActual = 0;
    bool dijkstraPresente = false;
    while(noHaGanado){
        char flecha = getch();
        if(flecha == 72){
            if(dijkstraPresente){
                dijkstraPresente = false;
                pintarDijkstra(color);
            }
            grafo[nodoActual].goToPos(0);
            if(grafo[nodoActual].getElement() != -1){
                if(tesoros[nodoActual] == TESORO) tesoros[nodoActual] = NORMAL;
                if(tesoros[nodoActual] == SALIDA && !tieneTodosLosTesoros()) setfillstyle(1,7);
                else setfillstyle(1,color);
                bar(posX+10,posY+10,posX,posY);
                posY-=20;
                setfillstyle(1,10);
                bar(posX+10,posY+10,posX,posY);
                nodoActual = grafo[nodoActual].getElement();
            }

        }
        if(flecha == 80){
            if(dijkstraPresente){
                dijkstraPresente = false;
                pintarDijkstra(color);
            }
            grafo[nodoActual].goToPos(1);
            if(grafo[nodoActual].getElement() != -1){
                if(tesoros[nodoActual] == TESORO) tesoros[nodoActual] = NORMAL;
                if(tesoros[nodoActual] == SALIDA && !tieneTodosLosTesoros()) setfillstyle(1,7);
                else setfillstyle(1,color);
                bar(posX+10,posY+10,posX,posY);
                posY+=20;
                setfillstyle(1,10);
                bar(posX+10,posY+10,posX,posY);
                nodoActual = grafo[nodoActual].getElement();
            }

        }
        if(flecha == 75){
            if(dijkstraPresente){
                dijkstraPresente = false;
                pintarDijkstra(color);
            }
            grafo[nodoActual].goToPos(2);
            if(grafo[nodoActual].getElement() != -1){
                if(tesoros[nodoActual] == TESORO) tesoros[nodoActual] = NORMAL;
                if(tesoros[nodoActual] == SALIDA && !tieneTodosLosTesoros()) setfillstyle(1,7);
                else setfillstyle(1,color);
                bar(posX+10,posY+10,posX,posY);
                posX-=20;
                setfillstyle(1,10);
                bar(posX+10,posY+10,posX,posY);
                nodoActual = grafo[nodoActual].getElement();
            }

        }
        if(flecha == 77){
            if(dijkstraPresente){
                dijkstraPresente = false;
                pintarDijkstra(color);
            }
            grafo[nodoActual].goToPos(3);
            if(grafo[nodoActual].getElement() != -1){
                if(tesoros[nodoActual] == TESORO) tesoros[nodoActual] = NORMAL;
                if(tesoros[nodoActual] == SALIDA && !tieneTodosLosTesoros()) setfillstyle(1,7);
                else setfillstyle(1,color);
                bar(posX+10,posY+10,posX,posY);
                posX+=20;
                setfillstyle(1,10);
                bar(posX+10,posY+10,posX,posY);
                nodoActual = grafo[nodoActual].getElement();
            }

        }
        if(flecha == 'h'){
            dijkstra();
            dijkstraPresente = true;
        }

        if(tesoros[nodoActual] == SALIDA && tieneTodosLosTesoros()) noHaGanado = false;
    }
}

void generarTesoros(){
    tesoros = new int[ancho*alto];

    int entrada = 0;
    salida = rand()%((ancho*alto)/2) + ((ancho*alto)/2);
    int tesoro;

    int contadorNormal;
    for(contadorNormal = 0; contadorNormal < (ancho*alto); contadorNormal++){
        tesoros[contadorNormal] = NORMAL;
    }
    tesoros[entrada] = ENTRADA;
    tesoros[salida] = SALIDA;

    int contadorTesoros;
    for(contadorTesoros = 0; contadorTesoros < cantidadTesoros; contadorTesoros++){
        tesoro = rand()%(ancho * alto);
        if(tesoros[tesoro] == NORMAL) tesoros[tesoro] = TESORO;
        else contadorTesoros--;
    }
}

void dibujarLaberinto(){
    initwindow(ancho*20+20,alto*20 + 20);
    color = (rand()%13)+1;
    if(color == 7 || color == 10) color = 15;
    setfillstyle(1,color);
    int valorNodo = 0;
    int xInicio = 10;
    int yInicio = 10;
    int xFinal = 20;
    int yFinal = 20;
    int i;
    int j;
    for(i = 0; i<alto; i++){
        for(j = 0; j<ancho; j++){
            grafo[valorNodo].goToStart();
            if(grafo[valorNodo].getElement() != -1) bar(xFinal,yInicio,xInicio,yInicio-10);
            grafo[valorNodo].next();
            if(grafo[valorNodo].getElement() != -1) bar(xFinal,yFinal+10,xInicio,yFinal);
            grafo[valorNodo].next();
            if(grafo[valorNodo].getElement() != -1) bar(xInicio,yFinal,xInicio-10,yInicio);
            grafo[valorNodo].next();
            if(grafo[valorNodo].getElement() != -1) bar(xFinal+10,yFinal,xFinal,yInicio);

            if(tesoros[valorNodo] == TESORO) setfillstyle(1,14);
            if(tesoros[valorNodo] == SALIDA) setfillstyle(1,7);
            if(tesoros[valorNodo] == ENTRADA) setfillstyle(1,10);
            bar(xFinal,yFinal,xInicio,yInicio);
            setfillstyle(1,color);
            xInicio+=20;
            xFinal+=20;
            valorNodo++;
        }
        xInicio=10;
        xFinal=20;
        yInicio+=20;
        yFinal+=20;
    }
}

void creaJuego(){
    Grafo laberinto(ancho, alto);
    grafo = laberinto.getHeadArbolExpansion();
    generarTesoros();
    dibujarLaberinto();
    jugar();
    ancho+=2;
    alto+=2;
    cantidadTesoros++;
    closegraph();
    creaJuego();
}

int main(){
    ancho = 10;
    alto = 10;
    cantidadTesoros = 3;
    creaJuego();
    return 0;
}
