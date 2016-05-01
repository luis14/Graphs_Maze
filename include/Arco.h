#ifndef ARCO_H
#define ARCO_H


class Arco
{
    public:
        Arco(int pNodoOrigen, int pNodoDestino){
            nodoOrigen = pNodoOrigen;
            nodoDestino = pNodoDestino;
        }
        ~Arco(){
        }
        void setNodoOrigen(int pNodoOrigen){
            nodoOrigen = pNodoOrigen;
        }
        void setNodoDestino(int pNodoDestino){
            nodoDestino = pNodoDestino;
        }
        int getNodoOrigen(){
            return nodoOrigen;
        }
        int getNodoDestino(){
            return nodoDestino;
        }
    private:
        int nodoOrigen;
        int nodoDestino;
};

#endif // ARCO_H
