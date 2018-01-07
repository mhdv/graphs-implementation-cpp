#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>

// STRUKTURA WEZLA ####################################

template <typename T>
class MyQueue;
template <typename T>
struct MyNode{
private:
	int key; // klucz do kolejki priorytetowej
    T element; // zawartosc elementu
    MyNode<T>* next; // wskaznik na nastepny element
    MyNode<T>* previous; // wskaznik na poprzedni element
    friend class MyQueue<T>;
public:
    T getElement() {return element;} // zwraca element
    MyNode<T>* getPrevious() {return previous;} // zwraca previous
    MyNode<T>* getNext() {return next;} // zwraca next
    int getKey() {return key;} // zwraca key
    void setElement(T newE) {element=newE;} // ustala element
    void setNext(MyNode<T>* newN) {next=newN;} // ustala next
    void setPrevious(MyNode<T>* newP) {previous=newP;} // ustala previous
    void setKey(unsigned int k) {key=k;}
};

// ###################################################
// KOLEJKA PRIORYTETOWA ##############################

template <typename T>
class MyQueue{
protected:

	int size;
	MyNode<T>* head;
	MyNode<T>* tail;
public:

	MyQueue();
	~MyQueue();

	int getSize();
	T min();
	MyNode<T>* minNode();
	T find(int k);
	MyNode<T>* findNode(int k);
	int remove(int k);
	int removeMin();
	void insert(int k, const T& elem);
	bool isEmpty();
	MyNode<T>* getHead() {return head;}
	MyNode<T>* getTail() {return tail;}

};
// METODY KOLEJKI ####################################




// KONSTRUKTOR
template <typename T>
MyQueue<T>::MyQueue(){

	// stworzenie wezlow glowy i ogona
	head = new MyNode<T>;
	tail = new MyNode<T>;

	// deklaracje kluczy glowy i ogona - ustawienie wskaznikow glowy i ogona
	tail->setKey(-1);
	head->setKey(-1);
	tail->setNext(head);
	head->setPrevious(tail);

	// początkowy rozmiar to 0
	size=0;
}


// DESTRUKTOR
template <typename T>
MyQueue<T>::~MyQueue(){}


// FUNKCJA ZWRACAJACA ROZMIAR KOLEJKI
template <typename T>
int MyQueue<T>::getSize(){
	return size;
}

// FUNKCJA DODAJACA ELEMENT DO KOLEJKI - (k- klucz, elem- wartosc elementu)
template <typename T>
void MyQueue<T>::insert(int k, const T& elem){

	// deklaracja nowego wezla
	MyNode<T>* newnode = new MyNode<T>;

	// warunek zapobiegajacy wpisaniu blednego klucza
	if(k<=0) { std::cout << "Nieprawidlowy klucz\n"; return;}
	else{

		// warunek dzielacy funkcje na dodawanie PIERWSZEGO elemntu do kolejki oraz KAZDEGO INNEGO elementu
		if(isEmpty()){

			// pierwsza deklaracja zaleznosci miedzy ogonem, glowa, a pierwszym wezlem
			head->setNext(newnode);
			tail->setPrevious(newnode);

			// ustawienie wartosci pierwszego wezla
			newnode->setKey(k);
			newnode->setElement(elem);

			// ustawienie zaleznosci dla pierwszego wezla
			newnode->setNext(tail);
			newnode->setPrevious(head);

			// inkrementacja rozmiaru
			size++;
		}else{
			// wezel pomocniczy ustawiony jako glowa
			MyNode<T>* tmp = head;

			// petla ustawiajaca tmp na odpowiedni wezel
			do{
				tmp = tmp->getNext();
			}while(k>tmp->getKey() && tmp->getKey()!=-1);
			tmp = tmp->getPrevious();

			// ustawienie wartosci nowego wezla
			newnode->setKey(k);
			newnode->setElement(elem);

			// ustawienie odpowiednich zaleznosci dla nowego wezla
			newnode->setNext(tmp->getNext());
			newnode->setPrevious(tmp);

			// ustawienie odpowiednich zaleznosci sasiednich wezlow
			tmp->getNext()->setPrevious(newnode);
			tmp->setNext(newnode);

			// inkrementacja rozmiaru
			size++;
		}
	}
}

// FUNKCJA USUWAJACA ELEMENT O NAJMNIEJSZYM KLUCZU
template <typename T>
int MyQueue<T>::removeMin(){
	if(isEmpty()) { return 0;}
	else{
		MyNode<T>* tmp = head->getNext();
		int key = tmp->getKey();
		// T tmp2 = head->getNext()->getElement();
		delete head->getNext();
		head->setNext(tmp->getNext());
		tmp = tmp->getNext();
		tmp->setPrevious(head);
		size--;
		return key;
	}
}

// FUNKCJA ZWRACAJACA ELEMENT O NAJMNIEJSZYM KLUCZU
template <typename T>
T MyQueue<T>::min(){
	return head->getNext()->getElement();
}

template <typename T>
MyNode<T>* MyQueue<T>::minNode(){
	return head->getNext();
}

// FUNKCJA SPRAWDZAJACA CZY KOLEJKA JEST PUSTA
template <typename T>
bool MyQueue<T>::isEmpty(){
	if(size>0) return false;
	else return true;
}

template <typename T>
T MyQueue<T>::find(int k){
	MyNode<T>* tmp = head->getNext();
	int counter = 0;
	do{
		if(tmp->getKey()==k) return tmp->getElement();
		else{
			counter++;
			tmp=tmp->getNext();
		}
	}while(counter!=size);
	// std::cerr << "\nNie ma takiego wezla!\n";
	return nullptr;
}

template <typename T>
MyNode<T>* MyQueue<T>::findNode(int k){
	MyNode<T>* tmp = head->getNext();
	int counter = 0;
	do{
		if(tmp->getKey()==k) return tmp;
		else{
			counter++;
			tmp=tmp->getNext();
		}
	}while(counter!=size);
	// std::cerr << "\nNie ma takiego wezla (tego konkretnego)!\n";
	return nullptr;
}

template <typename T>
int MyQueue<T>::remove(int k){
	if(isEmpty()) { return 0;}
	else{
		MyNode<T>* tmp = findNode(k);
		int key = k;
		tmp->getNext()->setPrevious(tmp->getPrevious());
		tmp->getPrevious()->setNext(tmp->getNext());
		delete findNode(k);
		size--;
		return key;
	}
}

#endif // QUEUE_H