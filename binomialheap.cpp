#include "binomialheap.h"

BinomialHeap::BinomialHeap()
{
    //heap

}

void BinomialHeap::link(NodoB &a, NodoB &b)
{
    a.parent = &b;
    a.siblingDer = *b.pChild.begin();
    a.siblingIzq=NULL;

    if(!b.pChild.empty()){
        NodoB *nodob = *b.pChild.begin();
        nodob->siblingIzq = &a;
    }

    b.pChild.push_front(&a);
    b.degree ++;
}

BinomialHeap *BinomialHeap::merge(BinomialHeap& b1,BinomialHeap& b2)
{
    NodoB* a;
    NodoB* b;
    NodoB* c;
     // punteros al nodo mas izquierdo del heap
    if(b1.heap.empty())
        a=NULL;
    else
        a = *b1.heap.begin();
    if (b2.heap.empty())
        b = NULL;
    else
        b = *b2.heap.begin();

    if(b1.heap.empty())
        b1.heap.push_back(minDegree(*a,*b));
    else
        *b1.heap.begin()=minDegree(*a,*b);

    if (*b1.heap.begin() == NULL) return &b1;
    if (*b1.heap.begin() == b ) b=a;

    a = *b1.heap.begin();

    while (b != NULL){

        if(a->siblingDer == NULL){

            a->siblingDer = b;
            b->siblingIzq=a;
            *b2.heap.begin()=NULL; // liberando el primero de la lista de heaps de b2
            delete &b2;
            //b1.heap.push_back(b);

            return &b1;

        }
        else
            if(a->siblingDer->degree < b->degree){
                a = a->siblingDer; //recorre a
            } else{
                c = b->siblingDer;
                b->siblingDer = a->siblingDer;
                a->siblingDer->siblingIzq = b; //el hermano izq del hermano derecho de a es b;
                a->siblingDer = b; //b apunta al hermano de a
                b->siblingIzq = a;
                a=a->siblingDer;
                b=c;
            }
    }
    return &b1;
}

BinomialHeap* BinomialHeap::junction(BinomialHeap& b1, BinomialHeap& b2)
{
    NodoB* x;
    NodoB* prevX;
    NodoB* nextX;

    BinomialHeap* b=merge(b1,b2);

    if(b==NULL){ //warning
        return b;
    }
    prevX = NULL;
    x=*b->heap.begin();
    nextX = x->siblingDer;

    while(nextX != NULL){

        if( (x->degree != nextX->degree) || (nextX->siblingDer != NULL && nextX->siblingDer->degree == x->degree) ){
            prevX = x;
            x=nextX;
        }else{

            if(x->key <= nextX->key){
                x->siblingDer = nextX->siblingDer;
                if(nextX->siblingDer)
                    nextX->siblingDer->siblingIzq = x; // el hermano derecho de next-x sera el hermano derecho de x
                link(*nextX,*x); //(y,z) menor z
            }else{
                if(prevX == NULL){
                    *b->heap.begin() = nextX;
                }else
                    prevX->siblingDer = nextX;


                nextX->siblingIzq=x->siblingIzq;
                if(x->siblingIzq != NULL)
                    x->siblingIzq->siblingDer=nextX;
                link(*x,*nextX);
                x=nextX;

            }

        }
        nextX = x->siblingDer;
        //return b;
    }
    return b;
}

void BinomialHeap::decreaseKey(BinomialHeap &b, void *oldValue, int newKey)
{
    NodoB *y;
    NodoB *z;
    NodoB *foundNode;

//    if( newKey > oldValue)
//        qDebug()<<"error la nueva llave es mas grande que la actual llave";
    NodoB *headB=*b.heap.begin();
    foundNode = find(*headB,oldValue);
    foundNode->key=newKey;
    y = foundNode;
    z = foundNode->parent;



    while(z != NULL && y->key < z->key){

        int tempKey; //intercambio de llaves
        tempKey = y->key;
        y->key=z->key;
        z->key = tempKey;

        //cambiar satelites si los hay

        y = z;
        z = y->parent; //:D

    }

}

NodoB *BinomialHeap::extractMin(BinomialHeap &b)
{

    NodoB *headNode = *b.heap.begin();
    NodoB *minTemp= findMin(*headNode);
    BinomialHeap *btempExtractMin = new BinomialHeap();

    NodoB *nodoHead = myreverse(*minTemp);

    btempExtractMin->heap.push_front(nodoHead);

    if(minTemp->siblingIzq && minTemp->siblingDer){

        minTemp->siblingDer->siblingIzq = minTemp->siblingIzq;
        minTemp->siblingIzq->siblingDer = minTemp->siblingDer;

    }else
        if(!minTemp->siblingDer){ // si hermano derecho es nulo
            minTemp->siblingIzq->siblingDer = NULL;
        }else
            if(!minTemp->siblingIzq){
                minTemp->siblingDer->siblingIzq=NULL;

            }
    //borrar
//    NodoB *headTemp = *b.heap.begin();
//    headTemp=minTemp->siblingDer;
//    minTemp=NULL;
    b.junction(b,*btempExtractMin);

    *b.heap.begin() = minTemp->siblingDer;

    //delete(minTemp->address,minTemp->size);

//    headTemp = minTemp->siblingDer;
    minTemp->siblingDer=NULL;




    return minTemp;

    //btemp->heap.begin() = minTemp->pChild.reverse();
    //*minTemp = NULL; //borrado
    //b=junction(b,btemp);
}

NodoB *BinomialHeap::findMin(NodoB &aNode)
{
    //myIterator it= heap.begin();
    NodoB *ith = &aNode;
    NodoB *itNexth;
    NodoB *minTemp;
    int min= aNode.key;
    minTemp = &aNode;

    while(ith){

        if(ith->key<min){

            minTemp = ith;
        }
        ith = ith->siblingDer;

    }

    return minTemp;
}

void BinomialHeap::insert(BinomialHeap &bh, NodoB &nodo)
{

    BinomialHeap *bTemp=new BinomialHeap;
    nodo.parent = NULL;
    nodo.siblingDer = NULL;
    nodo.degree = 0;
    nodo.siblingIzq=NULL;
    bTemp->heap.push_back(&nodo);
    BinomialHeap *bhTemp;
    bhTemp=junction(bh,*bTemp);

}

NodoB *BinomialHeap::myreverse(NodoB &b)
{
    NodoB* x;
    NodoB* prevX=NULL;

    x=*b.pChild.begin();
    //NodoB* nextX = x->siblingDer;
    if(!x){
        NodoB *daddy = &b;
        daddy->siblingDer->siblingIzq =NULL;
    }
    while(x){ // costo n
        NodoB * tempNode;
        tempNode = x->siblingDer;
        x->siblingDer = prevX;
        x->siblingIzq = tempNode;
        prevX= x;
        x=tempNode;
    }

    b.pChild.reverse(); //costo n

    return prevX;

}

NodoB *BinomialHeap::find(NodoB &b,void *pointer)
{
    if(b.address==pointer)
        return &b;
    NodoB *x = &b;
    while(x){
        if(x->address == pointer)
            return x;
        NodoB *result = bfs(*x,pointer); //almaceno nodo encontrado
        if(result) //si existe
            return result;
        x=x->siblingDer;
    }
    return NULL;

}

NodoB *BinomialHeap::bfs(NodoB &b,void *pointer)
{
    //NodoB *x=b.pChild.begin();
    if(b.address == pointer ) //preorder operation
        return &b;
    for(list<NodoB*>::const_iterator it = b.pChild.begin(); it != b.pChild.end(); it++)
    {
        NodoB *temoNode = *it;
        NodoB *result=bfs(*temoNode,pointer);
        if(result)
            return result;
        qDebug()<<"xD";
    }
    return NULL;
}

BinomialHeap *BinomialHeap::deleteNode(BinomialHeap &bh, void *target)
{
    decreaseKey(bh,target,-INT_MAX);
    extractMin(bh);
}

void BinomialHeap::binomialHeap2file(BinomialHeap &bh)
{

    file = new QFile("out.dot");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    out = new QTextStream(file);

    *out<<"digraph G { "<<endl;

    NodoB *x = *bh.heap.begin();

    while(x){

        if(x->siblingDer){
            *out<<"\"\\"<<x<<"\" [label = \""<<x->key<<"\"] "<<endl;
            *out<<"\"\\"<<x->siblingDer<< "\" [ label=\""<<x->siblingDer->key<<"\"] ;" <<endl ;
            *out<<"\"\\"<<x<<"\""<<" -> \"\\"<<x->siblingDer<< "\" [constraint=false] "<<endl ;
        }


        if(x->siblingIzq){
            *out<<"\"\\"<<x<<"\" [label = \""<<x->key<<"\"] "<<endl;
            *out<<"\"\\"<<x->siblingIzq<< "\" [ label=\""<<x->siblingIzq->key<<"\"] ;"<<endl;
            *out<<"\"\\"<<x<<"\""<<" -> \"\\"<<x->siblingIzq<< "\" [constraint=false] "<<endl ;
        }
        for(list<NodoB*>::const_iterator it = x->pChild.begin(); it != x->pChild.end(); it++)
        {
            NodoB *aNode = *it;
            *out<<"\"\\"<<x<<"\" [label = \""<<x->key<<"\"] "<<endl;
            *out<<"\"\\"<<aNode<<"\" [label=\""<<aNode->key<<"\" ]"<<endl;
            *out<<"\"\\"<<x<<"\" -> \"\\"<<aNode<<"\""<<endl;
            bfsPrint(*aNode);
        }

//        NodoB *result = bfs(*x,value); //almaceno nodo encontrado
//        if(result) //si existe
//            return result;



        x=x->siblingDer;
    }
    *out<<"} "<<endl;
    file->close();
}

void BinomialHeap::bfsPrint(NodoB &b)
{

    if(b.siblingDer){
        *out<<"\"\\"<<&b<<"\" [label = \""<<b.key<<"\"] "<<endl;
        *out<<"\"\\"<<b.siblingDer<< "\" [label=\""<<b.siblingDer->key<<"\"] ;" <<endl ;
        *out<<"\"\\"<<&b<<"\" -> \"\\"<<b.siblingDer<< "\" [constraint=false]"<<endl ;
    }
    if(b.siblingIzq){
        *out<<"\"\\"<<&b<<"\" [label = \""<<b.key<<"\"] "<<endl;
        *out<<"\"\\"<<b.siblingIzq<< "\" [label=\""<<b.siblingIzq->key<<"\"] ;"<<endl;
        *out<<"\"\\"<<&b<<"\" -> \"\\"<<b.siblingIzq<< "\" [constraint=false]"<<endl;
     }
    //out<<b.key<<" -> "<<b.siblingDer->key<<endl ;

    for(list<NodoB*>::const_iterator it = b.pChild.begin(); it != b.pChild.end(); it++)
    {
        NodoB *temoNode = *it;
        *out<<"\"\\"<<&b<<"\" [label = \""<<b.key<<"\"] "<<endl;
        *out<<"\"\\"<<temoNode<<"\" [label = \""<<temoNode->key<<"\"] "<< endl ;
        *out<<"\"\\"<<&b<<"\" -> \"\\"<<temoNode<<"\""<< endl ;
        bfsPrint(*temoNode);

        qDebug()<<"xD";
    }
    //return NULL;

}

void *BinomialHeap::crearNodo(void *address, unsigned int size,BinomialHeap &bh)
{
    NodoB *myNode=new NodoB();
    myNode->setKey(1);
    myNode->setSize(size);
    myNode->setAdress(address);
    BinomialHeap *temp= &bh;
    this->insert(*temp,*myNode);
    //address
    return address;

}

void BinomialHeap::asignar(void *additional, void *source) // q , p(ya existe)
{
    //this->find(this->heap,pointer);
    NodoB *temp = NULL;
    NodoB *aNodo = *this->heap.begin();
    temp = this->find(*aNodo,source);
    if(!temp){
        qDebug()<<"error! no existe el objeto del segundo argumento";
        return ;
    }
    temp->key++;

}

void BinomialHeap::liberar(void *object)
{
    NodoB *temp = NULL;
    NodoB *aNodo = *this->heap.begin();
    temp = this->find(*aNodo,object);
    if(!temp){
        qDebug()<<"error! no existe el objeto del segundo argumento";
        return ;
    }
    temp->key--;
    if(temp->key==0){
        deleteNode(*this,object);
        //delete(object,temp->size);
        delete object;

    }

}


NodoB *BinomialHeap::minDegree(NodoB &a, NodoB &b)
{
    if(&a == NULL) return &b;
    if(&b == NULL) return &a;
    if(a.degree<=b.degree)
        return &a;
    return &b;

}

void BinomialHeap::deleteObject()
{
    delete this;
}

BinomialHeap::~BinomialHeap()
{
    for(list<NodoB*>::const_iterator it = heap.begin(); it != heap.end(); it++)
    {
        delete *it;
    }
    heap.clear();

}
