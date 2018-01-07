#ifndef EDGENODE_H
#define EDGENODE_H
#include "queue.h"


//
// STRUKTURA WEZLA
//



template <typename T>
struct Edge;
template <typename T>
struct Node{
private:
	T element;
	int position;

public:
	bool visited = false;
	T setElement(T e) {element=e; return e;}
	int setPosition(int p) {position=p; return p;}

	T getElement() {return element;}
	int getPosition() {return position;}
	MyQueue<Edge<T>*>* listofedges = new MyQueue<Edge<T>*>;
};


//
// STRUKTURA KRAWEDZI
//



template <typename T>
struct Edge{
private:
	T element;
	Node<T>* start;
	Node<T>* end;
	int position;

public:
	T setElement(T e) {element=e; return e;}
	T getElement() {return element;}
	T getStartElement() {return start->getElement();}
	T getEndElement() {return end->getElement();}
	Node<T>* getStart() {return start;}
	Node<T>* getEnd() {return end;}
	int setPosition(int p) {position=p; return p;}
	int getPosition() {return position;}
	void setStart(Node<T>* s) {start=s;}
	void setEnd(Node<T>* e) {end=e;}
};

#endif