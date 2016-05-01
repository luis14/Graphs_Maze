#ifndef GRAFO_H
#define GRAFO_H

#include <winbgim.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <time.h>
#include "LinkedList.h"

using namespace std;

class Grafo{
    public:
        Grafo(int anchoLaberinto, int altoLaberinto){
            ancho = anchoLaberinto;
            alto = altoLaberinto;
            visitados = new bool[ancho*alto];
            headGrafoInicial = new LinkedList<int>[ancho*alto];
            headArbolExpansion = new LinkedList<int>[ancho*alto];
            generarGrafoInicial();
            generarArbolExpansion();
            agregarArcosExtras();
        }
        ~Grafo(){
        }
        void generarGrafoInicial(){

            /*
                Genera el grafo en el que cada nodo tiene asignado a sus vecinos correspondientes
            */

            int valorNodo;
            int tamanoGrafo = (ancho*alto);

            for(valorNodo = 0; valorNodo < tamanoGrafo; valorNodo++){
                //ciclo que recorre el arreglo de nodos para ir asignandole sus vecinos correspondientes
                if(valorNodo == 0){
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoAbajo(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoDerecha(valorNodo));
                }
                else if(valorNodo == (ancho-1)){
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoAbajo(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoIzquierda(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                }
                else if(valorNodo == ((ancho*alto)-ancho)){
                    headGrafoInicial[valorNodo].append(vecinoArriba(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoDerecha(valorNodo));
                }
                else if(valorNodo == ((ancho*alto)-1)){
                    headGrafoInicial[valorNodo].append(vecinoArriba(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoIzquierda(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                }
                else if(valorNodo < ancho){
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoAbajo(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoIzquierda(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoDerecha(valorNodo));
                }
                else if(valorNodo % ancho == 0){
                    headGrafoInicial[valorNodo].append(vecinoArriba(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoAbajo(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoDerecha(valorNodo));
                }
                else if(valorNodo % ancho == ancho-1){
                    headGrafoInicial[valorNodo].append(vecinoArriba(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoAbajo(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoIzquierda(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                }
                else if(valorNodo > ((ancho*alto)-ancho)){
                    headGrafoInicial[valorNodo].append(vecinoArriba(valorNodo));
                    headGrafoInicial[valorNodo].append(-1);
                    headGrafoInicial[valorNodo].append(vecinoIzquierda(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoDerecha(valorNodo));
                }
                else{
                    headGrafoInicial[valorNodo].append(vecinoArriba(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoAbajo(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoIzquierda(valorNodo));
                    headGrafoInicial[valorNodo].append(vecinoDerecha(valorNodo));
                }
                headArbolExpansion[valorNodo].append(-1);
                headArbolExpansion[valorNodo].append(-1);
                headArbolExpansion[valorNodo].append(-1);
                headArbolExpansion[valorNodo].append(-1);

            }
        }
        void generarArbolExpansion(){
            int valorNodo;
            for(valorNodo = 0; valorNodo<ancho*alto;valorNodo++){
                visitados[valorNodo] = false;
            }
            srand((unsigned)time(NULL));
            generarArbolExpansionAux(0);
        }
        void generarArbolExpansionAux(int valorNodo){
            visitados[valorNodo] = true;
            while(tieneVecinosSinVisitar(valorNodo)){
                int numVecino = vecinoRandom(valorNodo);
                headArbolExpansion[valorNodo].goToPos(numVecino);
                headGrafoInicial[valorNodo].goToPos(numVecino);
                int vecino = headGrafoInicial[valorNodo].getElement();
                headArbolExpansion[valorNodo].remove();
                headArbolExpansion[valorNodo].insert(vecino);

                int numPadre = obtienePadre(numVecino);
                headArbolExpansion[vecino].goToPos(numPadre);
                headArbolExpansion[vecino].remove();
                headArbolExpansion[vecino].insert(valorNodo);

                generarArbolExpansionAux(vecino);
            }
        }
        void agregarArcosExtras(){
            int cincoPorciento = (ancho*alto) * 0.05;
            while(cincoPorciento>0){
                int nodoRand = rand()%(ancho*alto);
                int vecinoRand = rand()%4;
                headArbolExpansion[nodoRand].goToPos(vecinoRand);
                headGrafoInicial[nodoRand].goToPos(vecinoRand);
                if(headArbolExpansion[nodoRand].getElement() == -1 && headGrafoInicial[nodoRand].getElement() != -1){
                    headArbolExpansion[nodoRand].remove();
                    headArbolExpansion[nodoRand].insert(headGrafoInicial[nodoRand].getElement());
                    headArbolExpansion[headGrafoInicial[nodoRand].getElement()].goToPos(obtienePadre(vecinoRand));
                    headArbolExpansion[headGrafoInicial[nodoRand].getElement()].remove();
                    headArbolExpansion[headGrafoInicial[nodoRand].getElement()].insert(nodoRand);
                    cincoPorciento--;
                }
            }
        }
        void setHeadGrafoInicial(LinkedList<int> *pHead){
            headGrafoInicial = pHead;
        }
        LinkedList<int> *getHeadGrafoInicial(){
            return headGrafoInicial;
        }
        void setHeadArbolExpansion(LinkedList<int> *pHead){
            headArbolExpansion = pHead;
        }
        LinkedList<int> *getHeadArbolExpansion(){
            return headArbolExpansion;
        }

    private:
        int ancho;
        int alto;
        LinkedList<int> *headGrafoInicial;
        LinkedList<int> *headArbolExpansion;
        bool *visitados;

        bool tieneVecinosSinVisitar(int valorNodo){
            int i=0;
            for(headGrafoInicial[valorNodo].goToStart();i<headGrafoInicial[valorNodo].getSize();i++){
                if(headGrafoInicial[valorNodo].getElement() != -1)if(!visitados[headGrafoInicial[valorNodo].getElement()]) return true;
                headGrafoInicial[valorNodo].next();
            }
            return false;
        }
        int vecinoRandom(int valorNodo){
            int vecino = rand()%4;
            headGrafoInicial[valorNodo].goToPos(vecino);
            if(headGrafoInicial[valorNodo].getElement() == -1) return vecinoRandom(valorNodo);
            else if(visitados[headGrafoInicial[valorNodo].getElement()]) return vecinoRandom(valorNodo);
            else return vecino;
        }
        int obtienePadre(int numVecino){
            if(numVecino == 0) return 1;
            else if(numVecino == 1) return 0;
            else if(numVecino == 2) return 3;
            else return 2;
        }
        int vecinoArriba(int nodo){
            return nodo - ancho;
        }
        int vecinoAbajo(int nodo){
            return nodo + ancho;
        }
        int vecinoIzquierda(int nodo){
            return nodo - 1;
        }
        int vecinoDerecha(int nodo){
            return nodo + 1;
        }
        void imprimirGrafo(){

            /*
                Imprime el grafo
            */

            int valorNodo;
            int tamanoGrafo = (ancho*alto);
            int vecino;
            for(valorNodo = 0; valorNodo < tamanoGrafo; valorNodo++){
                cout<<valorNodo<<"(";
                headArbolExpansion[valorNodo].goToStart();
                for(vecino = 0;vecino<4;vecino++){
                    cout<<headArbolExpansion[valorNodo].getElement()<<", ";
                    headArbolExpansion[valorNodo].next();
                }
                cout<<")";
                if(valorNodo % ancho == ancho-1) cout<<endl;
            }
        }
};

#endif // GRAFO_H
