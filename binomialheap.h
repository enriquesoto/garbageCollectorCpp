#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <nodob.h>
#include <QDebug>
#include <climits>
#include <QFile>
#include <memory>

class BinomialHeap
{

    typedef typename list<NodoB*>::iterator myIterator;

public:

    BinomialHeap();
    void link(NodoB &a,NodoB &b);
    BinomialHeap *merge(BinomialHeap &b1, BinomialHeap &b2);
    BinomialHeap *junction(BinomialHeap &b1, BinomialHeap &b2);
    void decreaseKey(BinomialHeap &b,void *oldValue,int newKey);
    void increaseKeybyOne(BinomialHeap &b,void *oldValue);
    NodoB *extractMin(BinomialHeap &b);
    NodoB * findMin(NodoB &aNode);
    void insert(BinomialHeap &bh,NodoB &temp1);
    NodoB *myreverse(NodoB &b);
    NodoB *find(NodoB &b, void *pointer);
    NodoB *bfs(NodoB &b, void *pointer);
    BinomialHeap *deleteNode(BinomialHeap &bh,void *target);
    void binomialHeap2file(BinomialHeap &bh);
    void bfsPrint(NodoB &b);

    void *crearNodo(void * addressSource,unsigned int size, BinomialHeap &bh);
    void asignar(void *additional, void *source);
    void liberar(void *object);


    QFile *file;
    QTextStream *out;
    list<NodoB*> heap;

private:


    NodoB minPointer;
    NodoB* minDegree(NodoB &a,NodoB &b);
    void deleteObject();
    ~BinomialHeap();




};

#endif // BINOMIALHEAP_H
