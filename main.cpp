#include <QtCore/QCoreApplication>
#include <QDebug>
#include <binomialheap.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BinomialHeap *bh = new BinomialHeap();
    int *entero = (int *) malloc(sizeof(int));
    *entero = 5;
//    int entero = 5;

    int *pint= (int*) bh->crearNodo(entero,sizeof(int),*bh);
    NodoB temp;
    NodoB *anode = (NodoB *) bh->crearNodo(&temp,sizeof(NodoB),*bh);
    NodoB *bnode;

    int *otropuntero;

    //qDebug()<<"entero "<<&entero<<" y "<<pint ;



    bh->asignar(otropuntero,entero);

    bh->asignar(bnode,anode);

    double pDouble=5,valor1=15;

    double *retorno = (double *) bh->crearNodo(&pDouble,sizeof(double),*bh);


  //  bh->liberar(&pDouble);
   bh->liberar(retorno);
   //bh->liberar(&entero);
    //Nodo *p =
   return a.exec();
}
