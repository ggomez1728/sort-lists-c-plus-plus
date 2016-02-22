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
class List;

template <class Tipo>
class Node
{
   Tipo data;
   Node<Tipo>* next_node;
   friend class List<Tipo>; //La clase Lista puede acceder a sus atributos privados
};

template <class Tipo>
class List
{
	typedef Node<Tipo>* Pointer;
private:

	Node<Tipo>* first;

public:

         //inicializa la lista con su primer elemento como vacio
         List()
         {
        	 first = NULL;
         };

         Node<Tipo>* getFirst()
         {
        	  return first;
         };

         void setFirst(Node<Tipo>* p){
        	 first = p;
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
        	      first=nuevo;
        	      return true;
        	  }
       	      return false;
         };

         bool insertAfter(Pointer p,Tipo Valor){
        	 Pointer nuevo;
        	 if (!fullMemory())
        	 {
        		 if (p != NULL)
        		 {
        			 nuevo=new Node<Tipo>;
        		     nuevo->data=Valor;
        		     nuevo->next_node=p->next_node;
        		     p->next_node=nuevo;
        		     return true;
        		 }
        	 }
        	 return false;
         };

         bool deleteBegin(Tipo &Valor){
        	Pointer old;
        	if (!empty())
        	{
        		old=first;
        	    Valor=old->info;
        	    first=first->prox;
        	    delete old;
        	    return true;
        	}
        	return false;
         };

         bool deleteAfter(Pointer p,Tipo &Valor){
        	 Pointer old;
        	 if (p != NULL)
        	 {
        		 if (p->prox != NULL)
        		     return false;
        		 else
        		 {
        			 old=p->prox;
        		     Valor=old->info;
        		     p->next_node=old->next_node;
        		     delete old;
        		     return true;
        		  };
        	 }
        	 return false;
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
        	p->info = Valor;
         };

         //Destructor
         ~List()
         {
        	 Node<Tipo> *p;
        	 while (!empty())
        	 {
        		 p = first->next_node;
        	     delete first;
        	     first=p;
        	 };
         };
};

typedef Node<int>* Pointer;

template <class Tipo>
class Sort
{
	List<int>* ListSort;
public:
	Sort(List<int>* List_t){
		ListSort = List_t;
	};

	//muestra los datos ordenados
	void print()
	{
		Pointer this_pointer, next_pointer;
		this_pointer = ListSort->getFirst();
		while (this_pointer != NULL)
		{
			std::cout << ListSort->getData(this_pointer) << std::endl;
			next_pointer = ListSort->getNextNode(this_pointer);
			this_pointer = next_pointer;
		}
	};

	void bubble()
	{
		Pointer this_pointer, next_pointer;
		Tipo temp_data;
		this_pointer = ListSort->getFirst();
		while (this_pointer != NULL)
		{
			next_pointer = ListSort->getNextNode(this_pointer);
			if (ListSort->getData(this_pointer) > ListSort->getData(next_pointer))
			{
				temp_data = ListSort->getData(this_pointer);
				ListSort->setData(this_pointer, ListSort->getData(next_pointer));

			}
			this_pointer = next_pointer;
		}

	};
};


List<int> Lista1;
Pointer ap, sig;
int valor, valor_aux;

int main() {
	//Bubble, Selection, Insertion, Quick, Merge y Shell
	// burbuja mejorada
	int size_elements, rand_data;
	int sort_select;
	/* initialize random seed: */
	srand (time(NULL));
	std::cout << "cantidad de datos generados aleatoriamente: " << std::endl;
	std::cin >> size_elements;
	std::cout <<  "=============="<<size_elements<<"============== " << std::endl;



	std::cout << "Elija el ordenamiento requerido " << std::endl;
	std::cout <<  "=============================== " << std::endl;
	std::cout << "1- Bubble " << std::endl;
	std::cout << "2- Selection" << std::endl;
	std::cout << "3- Insertion" << std::endl;
	std::cout << "4- Quick" << std::endl;
	std::cout << "5- Merge" << std::endl;
	std::cout << "6- Shell" << std::endl;
	std::cout << "7- burbuja mejorada" << std::endl;
	std::cout <<  "=============================== " << std::endl;
	std::cout << "Introduzca el ordenamiento (1-7): " << std::endl;
	std::cin >> sort_select;

 /* generate secret number between 1 and 10: */
	 //iSecret = rand() % 10 + 1;

	for (int i=0; i<size_elements; i++)
	{
		rand_data = rand() % size_elements + 1;
		Lista1.insertBegin(valor);
	}

	Sort<int> sort(&Lista1);
	sort.print();
	return 0;
}
