#ifndef NODO_H
#define NODO_H

class Nodo
{
    private:
        int valor;
        int tipoNodo;
        int pesos[4];
        Nodo *vecinos[4];
    public:
        Nodo(int pValor, int pTipoNodo, Nodo *arriba = NULL, Nodo *abajo = NULL, Nodo *izquierda = NULL, Nodo *derecha = NULL){
            valor = pValor;
            tipoNodo = pTipoNodo;
            vecinos[0] = arriba;
            vecinos[1] = abajo;
            vecinos[2] = izquierda;
            vecinos[3] = derecha;

            int i;
            for(i = 0; i < 4; i++){
                pesos[i] = 1;
            }
        }
        ~Nodo(){}
        void setValor(int pValor){
            valor = pValor;
        }
        void setTipoNodo(int pTipoNodo){
            tipoNodo = pTipoNodo;
        }
        void setPesoArriba(){
            pesos[0] = 1;
        }
        void setPesoAbajo(){
            pesos[1] = 2;
        }
        void setPesoIzquierda(){
            pesos[2] = 3;
        }
        void setPesoDerecha(){
            pesos[3] = 4;
        }
        void setVecinoArriba(Nodo *pArriba){
            vecinos[0] = pArriba;
        }
        void setVecinoAbajo(Nodo *pAbajo){
            vecinos[1] = pAbajo;
        }
        void setVecinoIzquierda(Nodo *pIzquierda){
            vecinos[2] = pIzquierda;
        }
        void setVecinoDerecha(Nodo *pDerecha){
            vecinos[3] = pDerecha;
        }

        int getValor(){
            return valor;
        }
        int getTipoNodo(){
             return tipoNodo;
        }
        int getPesoArriba(){
            return pesos[0];
        }
        int getPesoAbajo(){
            return pesos[1];
        }
        int getPesoIzquierda(){
            return pesos[2];
        }
        int getPesoDerecha(){
            return pesos[3];
        }
        Nodo *getVecinoArriba(){
            return vecinos[0];
        }
        Nodo *getVecinoAbajo(){
            return vecinos[1];
        }
        Nodo *getVecinoIzquierda(){
            return vecinos[2];
        }
        Nodo *getVecinoDerecha(){
            return vecinos[3];
        }
};

#endif // NODO_H
