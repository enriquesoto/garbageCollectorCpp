#include <QtCore/QCoreApplication>
#include <QDebug>
#include <binomialheap.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BinomialHeap *bh = new BinomialHeap();
//    int *entero = (int *) malloc(sizeof(int));
//    *entero = 5;
    int entero = 5;

    int *pint= (int*) bh->crearNodo(&entero,sizeof(int),*bh);
    NodoB temp;
    NodoB *anode = (NodoB *) bh->crearNodo(&temp,sizeof(NodoB),*bh);
    NodoB *bnode;

    int *otropuntero;

    //qDebug()<<"entero "<<&entero<<" y "<<pint ;

    bh->asignar(otropuntero,pint);

    int *otropuntero2;

    //qDebug()<<"entero "<<&entero<<" y "<<pint ;

    bh->asignar(otropuntero2,pint);

    bh->asignar(bnode,anode);

    double pDouble=5;

    double *retorno = (double *) bh->crearNodo(&pDouble,sizeof(double),*bh);

    //bh->increaseKeybyOne(*bh,anode);
    //bh->increaseKeybyOne(*bh,pint);

  //  bh->liberar(&pDouble);
   bh->liberar(pint);
   bh->liberar(pint);
   bh->liberar(pint);

   //bh->liberar(&entero);
    //Nodo *p =
   return a.exec();
}
