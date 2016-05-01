#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <iostream>
#define DEFAULT_MAX_SIZE 2048
#include <stdexcept>
using namespace std;

template <typename E>
class ArrayList
    {
    private:
        E * elements;
        int max;
        int size;
        int pos;
    public:
        ArrayList(int pMax = DEFAULT_MAX_SIZE) //constructor
            {
            elements = new E[pMax];
            max = pMax;
            size = 0;
            pos = 0;
            }
        ~ArrayList() //destructor
            {
                delete[] elements;
            }
        void insert(E pElement) throw (runtime_error) //inserta seg�n la posici�n
            {
            if (size == max)
                {
                throw runtime_error("No hay espacio para insertar");
                }
            for (int i = size; i>pos; i--)
                {
                elements[i] = elements[i-1];
                }
            elements[pos] = pElement;
            size++;
            }
        void append(E pElement) throw (runtime_error) //inserta siempre al final de la lista
            {
            if (size == max)
                {
                throw runtime_error("No hay espacio para insertar");
                }
            elements[size] = pElement;
            size++;
            }
        E remove() throw (runtime_error) //borra seg�n la posici�n
            {
            if (size == 0)
                {
                throw runtime_error("La lista est� vac�a");
                }
            if ((pos<0)||(pos>=size))
                {
                throw runtime_error("Indice fuera del rango");
                }
            E result = elements[pos];
            for(int i = pos; i<size-1; i++)
                {
                elements[i] = elements[i+1];
                }
            size--;
            return result;
            }
        void clear() //borra todo llamando a los destructores y luego crea de nuevo el arreglo
            {
            size = 0;
            pos = 0;
            delete [] elements;
            elements = new E[max];
            }
        E getElement() throw (runtime_error) //retorna seg�n la posici�n
            {
            if ((pos < 0) || (pos >= size))
                {
                throw runtime_error("�ndice fuera del rango");
                }
            return elements[pos];
            }
        void goToStart()
            {
            pos = 0;
            }
        void goToEnd()
            {
            pos = size;
            }
        void goToPos(int nPos) throw (runtime_error) //va a la posici�n que recibe como par�metro
            {
            if ((nPos < 0) || (nPos > size))
                {
                throw runtime_error("�ndice fuera del rango");
                }
            pos = nPos;
            }
        void previous()
            {
            if (pos > 0)
                {
                pos--;
                }
            }
        void next()
            {
            if (pos < size)
                {
                pos++;
                }
            }
        int getPos()
            {
            return pos;
            }
        int getSize()
            {
            return size;
            }
        void invertir ()
            {
            E* nueva_lista = new E[max];

            int indice = 0;
            for (int i = size-1; i>=0; i--)
                {
                nueva_lista[indice] = elements[i];
                indice++;
                }
                elements = nueva_lista;
            }
        void concatenar ()
            {
            cout<<"No disponible";
            }
    };

#endif // ARRAYLIST_H
