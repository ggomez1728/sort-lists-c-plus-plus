//============================================================================
// Name        : lists.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <string>
using namespace std;

template <class Tipo>
class ListDob;

template <class Tipo>
class Node_Double
{
    Tipo data;
    Node_Double<Tipo>* left;
    Node_Double<Tipo>* right;
    friend class Node_Double<Tipo>;
};

template <class Tipo>
class ListaDob
{
    typedef Node_Double<Tipo>* Pointer;
public:
    Pointer last;
    Node_Double<Tipo>* Primero();
    ListaDob(){
        last=NULL;
    };
    
    bool empty(){
        return last == NULL;
    };
    
    bool fullMemory(){
        Node_Double<Tipo> *p;
        p=new Node_Double<Tipo>;
        if (p == NULL)
            return true;
        else
        {
            delete p;
            return false;
        }
    };
    
    bool insertLeft(Pointer p,Tipo Value){
        Pointer newNode, ant;
        if (!fullMemory()) {
            newNode = new Node_Double<Tipo>;
            newNode->data=Value;
            if (last==NULL) //Es el primer nodo
            {
                newNode->right = newNode;
                newNode->left=newNode;
                last=newNode;
                return true;
            }
            else
                if (p!=NULL)
                {
                    ant=p->left;
                    newNode->right = p;
                    newNode->left = ant;
                    ant->right=newNode;
                    p->left=newNode;
                    return true;
                }
        }
        return false;
    };
    
    bool insertRight(Pointer p,Tipo Value){
        Pointer newNode,post;
        if (!fullMemory())    {
            newNode=new Node_Double<Tipo>;
            newNode->data=Value;
            if (last==NULL) //Es el primer nodo
            {
                newNode->right = newNode;
                newNode->left = newNode;
                last = newNode;
                return true;
            }
            else
                if (p!=NULL)
                {
                    post=p->right;
                    newNode->right=post;
                    newNode->left=p;
                    post->left=newNode;
                    p->right=newNode;
                    if (p==last)
                        last=newNode;
                    return true;
                }
        }
        return false;
    };
    
    bool Delete(Pointer p,Tipo &Value){
        Pointer ant, post;
        if (p==NULL)
            return false;
        else
        {
            Value=p->data;
            ant=p->left;
            post=p->right;
            if (post==p)
                last=NULL;
            else
            {
                ant->right=post;
                post->left=ant;
                if (last==p)last=ant;
            }
            delete p;
            return true;
        }
    };
    Node_Double<Tipo>* getRight(Pointer p){
        return p->right;
    };
    Node_Double<Tipo>* getLeft(Pointer p){
        return p->left;
    };
    void setRight(Pointer p,Pointer q){
        p->right=q;
    };
    void setLeft(Pointer p,Pointer q){
        p->left=q;
    };
    Tipo getData(Pointer p){
        return p->data;
    };
    void setData(Pointer p,Tipo Value){
        p->data=Value;
    };
    ~ListaDob(){
        Pointer p;
        Pointer Aux_last;
        Aux_last=last;
        while (!empty())
        {
            p=Primero();
            if (p==Aux_last)
                p=NULL;
            delete last;
            last=p;
        }
    };
};

template <class Tipo>
class List_Simple;

template <class Tipo>
class Node
{
    Tipo data;
    Node<Tipo>* next_node;
    friend class List_Simple<Tipo>; //La clase Lista puede acceder a sus atributos privados
};

template <class Tipo>
class List_Simple
{
    typedef Node<Tipo>* Pointer;
private:
    
    Node<Tipo>* first;
    
    Node<Tipo>* last;
    Node<Tipo>* node_reference;
    int counter;
public:
    //inicializa la lista con su primer elemento como vacio
    List_Simple()
    {
        first = NULL;
        last = NULL;
        node_reference = NULL;
        counter = 0;
    };
    int getCounter(){
        return counter;
    }
    
    Node<Tipo>* getLast(){
        return last;
    }
    
    Node<Tipo>* getFirst()
    {
        return first;
    };
    
    void setFirst(Node<Tipo>* p){
        first = p;
    };
    
    Node<Tipo>* getReference()
    {
        return node_reference;
    };
    
    void setReference(Node<Tipo>* p){
        node_reference = p;
    };
    void setReferenceFirst(){
        node_reference = first;
    };
    
    bool empty(){
        return first == NULL;
    };
    
    //Se usa para verificar espacio en memoria fisica
    bool fullMemory()
    {
        Node<Tipo> *p;
        p = new Node<Tipo>;
        if (p != NULL)
        {
            delete p;
            return false;
        }
        return true;
    };
    
    //inserta al principio de la lista
    bool insertBegin(Tipo Valor){
        Pointer nuevo;
        if (!fullMemory())
        {
            nuevo = new Node<Tipo>;
            nuevo->data=Valor;
            nuevo->next_node=first;	//apunta al nodo anterior
            if(first==NULL){
        	    	  last=nuevo;
            }
            first=nuevo;
            counter++;
            return true;
        }
        return false;
    };
    
    bool insertAfter(Pointer &p,Tipo Valor){
        Pointer nuevo;
        if (!fullMemory())
        {
            if (p != NULL)
            {
                nuevo=new Node<Tipo>;
                nuevo->data=Valor;
                nuevo->next_node = p->next_node;
                if(p->next_node==NULL){
                    last = nuevo;
                }
                p->next_node=nuevo;
                counter++;
                return true;
            }
        }
        return false;
    };
    
    bool automat_insert(Pointer &p,Tipo value){
        if (p == NULL) {
            return insertBegin(value);
        }
        else{
            return insertAfter(p, value);
        }
    };
    
    bool deleteBegin(Tipo &value){
        Pointer old;
        if (!empty())
        {
            old=first;
            value=old->data;
            if(old->next_node == NULL){
                last=NULL;
            }
            first=first->next_node;
            delete old;
            counter--;
            return true;
        }
        return false;
    };
    
    bool deleteAfter(Pointer &p,Tipo &value){
        Pointer old;
        if (p != NULL)
        {
            if (p->next_node != NULL)
            {
                old = p->next_node;
                value = old->data;		//retorna el dato eliminado
                if(old->next_node==NULL){
                    last = p;
                }
                p->next_node = old->next_node;
                delete old;
                counter--;
                return true;
        		  };
        }
        return false;
    };
    
    
    
    bool automat_delete(Pointer &p,Tipo& value){
        if (p == NULL) {
            return deleteBegin(value);
        }
        else{
            return deleteAfter(p, value);
        }
    };
    
    
    Node<Tipo>* getNextNode(Pointer p)
    {
        return p->next_node;
    };
    
    void setNextNode(Pointer p,Pointer q)
    {
        p->next_node = q;
    };
    
    Tipo getData(Pointer p)
    {
        return p->data;
    };
    
    void setData(Pointer p,Tipo Valor)
    {
        p->data = Valor;
    };
    
    //Destructor
    /* ~List_Simple()
     {
     Node<Tipo> *p;
     while (!empty())
     {
     p = first->next_node;
     delete first;
     first=p;
     };
     };
     */
};

typedef Node<int>* Pointer;

template <class Tipo>
class Sort
{
    List_Simple<Tipo> ListSort;
public:
    Sort(List_Simple<Tipo>& List_t){
        ListSort = List_t;
    };
    //muestra los datos ordenados
    void print()
    {
        int elements = 0;
        Pointer this_pointer, next_pointer;
        this_pointer = ListSort.getFirst();
        while (this_pointer != NULL)
        {
            std::cout << ListSort.getData(this_pointer);
            if (elements < 9)	{
                std::cout << "	";
                elements++;
            }
            else {
                std::cout << "\n";
                elements = 0;
            }
            
            next_pointer = ListSort.getNextNode(this_pointer);
            this_pointer = next_pointer;
        }
        std::cout << std::endl;
    };
    
    
    
    void swapList(Pointer & before_this_pointer, Pointer before_min_pointer, bool references = true)
    {
        
        Tipo value_pointer_this, value_pointer_min;
        ListSort.automat_delete(before_min_pointer, value_pointer_min); //siempre tiene un puntero que antecede
        
        if (before_this_pointer != NULL)
        {
            if (ListSort.getNextNode(before_this_pointer) != before_min_pointer)
            {
                //si no estan seguidos los dos nosdos
                ListSort.automat_delete(before_this_pointer, value_pointer_this);
                ListSort.insertAfter(before_min_pointer, value_pointer_this);
            }
        }
        ListSort.automat_insert(before_this_pointer, value_pointer_min);
        if (references){
            if (before_this_pointer == NULL)
            {
                ListSort.setReferenceFirst();
            }
            else
            {
                ListSort.setReference(ListSort.getNextNode(ListSort.getReference()));
            }
        }
        
    }
    
    void selection()
    {
        Pointer min_pointer, this_pointer, next_pointer, before_this_pointer, before_min_pointer;
        this_pointer = ListSort.getFirst();
        before_this_pointer = NULL;
        before_min_pointer = NULL;
        ListSort.setReferenceFirst();
        while (this_pointer != NULL)
        {
            min_pointer = this_pointer;
            next_pointer = this_pointer;
            while (ListSort.getNextNode(next_pointer) != NULL)
            {
                if (ListSort.getData(ListSort.getNextNode(next_pointer)) < ListSort.getData(min_pointer)) {
                    min_pointer = ListSort.getNextNode(next_pointer);
                    before_min_pointer = next_pointer;
                }
                next_pointer = ListSort.getNextNode(next_pointer);
            }
            //cambio
            if (min_pointer != this_pointer ) {
                swapList(before_this_pointer, before_min_pointer);
                before_this_pointer = ListSort.getReference();
            }
            else
            {
                ListSort.setReference(ListSort.getNextNode(ListSort.getReference()));
                before_this_pointer = ListSort.getReference();
            }
            this_pointer = ListSort.getNextNode(before_this_pointer);
        }
    };
    
    void swapp_next(Pointer & this_pointer, Pointer & next_pointer){
        Tipo value_this;
        value_this = ListSort.getData(this_pointer);
        ListSort.setData(this_pointer, ListSort.getData(next_pointer));
        ListSort.setData(next_pointer, value_this);
    };
    
    void Insertion()
    {	Tipo value_temp;
        Pointer this_pointer, next_pointer, search_pointer, shift_point;
        this_pointer = ListSort.getFirst();
        next_pointer = ListSort.getNextNode(this_pointer);
        search_pointer = next_pointer;
        while (search_pointer != NULL)
        {
            value_temp = ListSort.getData(next_pointer);
            shift_point = NULL;
            while (ListSort.getData(shift_point) < ListSort.getData(search_pointer))
            {
                
                this_pointer = ListSort.getNextNode(this_pointer);
            }
            search_pointer = ListSort.getNextNode(search_pointer);
        }
        
        
    };
    
    void optimizingBubble()
    {
        bool swapped =true;
        Pointer this_pointer, next_pointer, limit_pointer;
        limit_pointer = NULL;
        while(swapped)
        {
            this_pointer = ListSort.getFirst();
            next_pointer = ListSort.getNextNode(this_pointer);
            swapped = false;
            while (next_pointer != limit_pointer)
            {
                if(ListSort.getData(this_pointer) > ListSort.getData(next_pointer) )
                {
                    //falta swap
                    swapp_next(this_pointer,next_pointer);
                    swapped = true;
                }
                this_pointer = ListSort.getNextNode(this_pointer);
                next_pointer = ListSort.getNextNode(this_pointer);
            }
            limit_pointer = this_pointer;
        }
    };
    
    void bubble()
    {
        bool swapped =true;
        Pointer this_pointer, next_pointer;
        while(swapped){
            this_pointer = ListSort.getFirst();
            next_pointer = ListSort.getNextNode(this_pointer);
            swapped = false;
            while (next_pointer != NULL)
            {
                if(ListSort.getData(this_pointer) > ListSort.getData(next_pointer) ){
                    //falta swap
                    swapp_next(this_pointer,next_pointer);
                    swapped = true;
                }
                this_pointer = ListSort.getNextNode(this_pointer);
                next_pointer = ListSort.getNextNode(this_pointer);
            }
        }
    };
    
    void Shell()
    {
        Pointer this_pointer, contrast_pointer, ref_this_pointer, ref_contrast_pointer;
        int selector = 0;
        int gaps[] ={701, 301, 132, 57, 23, 10, 4, 1};
        int jump=0;
        int elements = ListSort.getCounter();
        bool swapped;
        //saltos en la lista
        while (selector < 8){
            if (elements > gaps[selector]){
                //inicializo primer variable
                ref_this_pointer = ListSort.getFirst();
                ref_contrast_pointer = ref_this_pointer;
                jump = gaps[selector];
                while (jump>0)
                {
                    ref_contrast_pointer = ListSort.getNextNode(ref_contrast_pointer);
                    jump--;
                }
                swapped =true;
                //datos preparados para la comparacion
                while(swapped){
                    swapped=false;
                    this_pointer=ref_this_pointer;
                    contrast_pointer = ref_contrast_pointer;
                    while (contrast_pointer != NULL)
                    {
                        if (ListSort.getData(this_pointer) > ListSort.getData(contrast_pointer)){
                            swapp_next(this_pointer,contrast_pointer);
                            swapped=true;
                        }
                        this_pointer = ListSort.getNextNode(this_pointer);
                        contrast_pointer = ListSort.getNextNode(contrast_pointer);
                    }
                }
            }
            selector++;
        }
    }
    
    List_Simple<int> & mergesort(List_Simple<int> & list_t){
        List_Simple<int> leftList, rightList, resultList;
        if (list_t.getCounter()>1){
            int middle = (int)(list_t.getCounter()/2);
            append_list_element(leftList, list_t, middle);
            append_list(rightList, list_t);
            leftList = mergesort(leftList);
            rightList = mergesort(rightList);
            if((int)rightList.getData(rightList.getFirst()) > (int)leftList.getData(leftList.getLast())){
                append_list(leftList, rightList);
                return leftList;
            }
            resultList = merge(leftList,rightList);
            return resultList;
        }
        else{
            return list_t;
        }
    }
    
    List_Simple<int> merge(List_Simple<int> leftList, List_Simple<int> rightList){
        List_Simple<int> resultList;
        int value=0;
        while((leftList.getCounter()>0) && (rightList.getCounter()>0)){
            if(rightList.getFirst() > leftList.getFirst()){
                leftList.deleteBegin(value);
                resultList.insertBegin(value);
            }
            else {
                rightList.deleteBegin(value);
                resultList.insertBegin(value);
            }
        }
        if (leftList.getCounter() > 0){
            append_list(resultList,leftList);
        }
        else if (rightList.getCounter() > 0){
            append_list(resultList,rightList);
        }
        return resultList;
    }
    
    void append_list_element(List_Simple<int> & appendList, List_Simple<int> & addList , int elements){
        int value;
        while((!addList.empty()) && (elements>0)){
            addList.deleteBegin(value);
            appendList.insertBegin(value);
            elements--;
        }
    }
    
    void append_list(List_Simple<int> & appendList, List_Simple<int>  addList ){
        int value;
        while(!addList.empty()){
            addList.deleteBegin(value);
            appendList.insertBegin(value);
        }
    }
    
};


List_Simple<int> Lista1;
Pointer ap, sig;
int valor, valor_aux;

int main() {
    //Bubble, Selection, Insertion, Quick, Merge y Shell
    // burbuja mejorada
    int size_elements;
    int sort_select;
    /* initialize random seed: */
    srand (time(NULL));
    std::cout << "cantidad de datos generados aleatoriamente: ";
    std::cin >> size_elements;
    
    std::cout <<  "=============================== " << std::endl;
    
    std::cout << "Elija el ordenamiento requerido " << std::endl;
    std::cout <<  "=============================== " << std::endl;
    std::cout << "1- Bubble " << std::endl; //Usando Lista simple
    std::cout << "2- Optimizing Bubble " << std::endl; //Usando Lista simple
    std::cout << "3- Insertion" << std::endl;  //falta
    std::cout << "4- Quick" << std::endl; //falta
    std::cout << "5- Merge" << std::endl; //falta
    std::cout << "6- Shell" << std::endl; //Usando Lista simple
    std::cout << "7- Selection" << std::endl; //Usando Lista simple
    std::cout <<  "=============================== " << std::endl;
    std::cout << "Introduzca el ordenamiento (1-7): " << std::endl;
    
    
    std::cin >> sort_select;
    
    
    
    for (int i=0; i<size_elements; i++)
    {
        Lista1.insertBegin(rand() % size_elements + 1);
    }
    
    Sort<int> sort(Lista1);
    std::cout << "DATA GENERADA " << std::endl;
    sort.print();
    std::cout << "espere, calculando.... " <<std::endl;
    
    switch (sort_select) {
        case 1:
            std::cout << "1- Bubble " << std::endl; //Usando Lista simple
            sort.bubble();
            break;
        case 2:
            std::cout << "2- Optimizing Bubble " << std::endl; //Usando Lista simple
            sort.optimizingBubble();
        case 3:
            std::cout << "3- Insertion" << std::endl;  //falta necesita listas dobles
            break;
        case 4:
            std::cout << "4- Quick" << std::endl; //falta necesita listas dobles
            break;
        case 5:
            std::cout << "5- Merge" << std::endl; //falta problemas- cor la recursion
            Lista1 = sort.mergesort(Lista1);
            break;
        case 6:
            std::cout << "6- Shell" << std::endl; //Usando Lista simple
            sort.Shell();
            break;
        case 7:
            std::cout << "7- Selection" << std::endl; //Usando Lista simple  break;
            sort.selection();
            break;
        default:
            cout << "la opcion es invalida";
    }
    std::cout << "DATA ORDENADA " << std::endl;
    sort.print();
    return 0;
}
