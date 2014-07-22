#ifndef NODOB_H
#define NODOB_H

#include <list>
#include <stddef.h>

using namespace std;


class NodoB
{
public:
    NodoB();
    int key; //numero de punteros q lo apuntan
    NodoB *parent;
    list<NodoB *> pChild;
    int degree;
    NodoB *siblingDer;
    NodoB *siblingIzq;
    void setKey(int);

    void *address; //direccion de memoria de lo que sea
    unsigned int size; //tamaño del objeto que se aloja
    void setSize(int size);
    void setAdress(void *address);
    void increseaseKey();
    ~NodoB();
};

#endif
