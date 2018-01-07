#ifndef GRAPH_H
#define GRAPH_H
#include "queue.h"
#include "edgenode.h"

template <typename T>
class Graph{
private:
	MyQueue<Node<T>*>* nodes;
	MyQueue<Edge<T>*>* edges;
	int size, connections;
	int sizeM;
	Edge<T>*** matrix;
	char graphtype;

public:
	Graph(char type = 'g', int s=5);
	~Graph();

	int getSize() {return size;}
	int getConnections() {return connections;}
	Node<T>* insert(T e);
	Edge<T>* connect(int s, int e, T elem = 0);
	Edge<T>* removeConnection(int k);
	Node<T>* getNode(int ind) {return nodes->find(ind);}
	Edge<T>* getEdge(int ind) {return edges->find(ind);}
	MyQueue<Edge<T>*>* getListofedges(int ind){ return nodes->find(ind)->listofedges;}

	bool isEmpty();
	bool existnode(int key);
	bool existconnection(int key);
	bool areConnected(int s, int e);
};

//
// KONSTRUKTOR
//

template <typename T>
Graph<T>::Graph(char type, int s){
	if (type!='g' || type!='m') type = 'g';
	switch(type){
	case 'g':
		{
			graphtype='g';
			nodes = new MyQueue<Node<T>*>;
			edges = new MyQueue<Edge<T>*>;
			size = 1;
			connections = 1;
		}
		break;
		case 'm':
		{
			graphtype='m';
			nodes = new MyQueue<Node<T>*>;
			sizeM=s;
			matrix = new Edge<T>**[sizeM];
			for(int i=0; i<sizeM; i++){
				matrix[i] = new Edge<T>*[sizeM];
				for(int j=0; j<sizeM; j++){
					matrix[i][j] = nullptr;
				}
			}
			size = 1;
			connections = 1;
		}
		break;
	}
}

//
// DESTRUKTOR
//

template <typename T>
Graph<T>::~Graph(){ }

template <typename T>
bool Graph<T>::existnode(int key){
	if(nodes->isEmpty()) return false;
	else{
		if(nodes->find(key)!=nullptr) return true;
	}
	return false;
}

//
// SPRAWDZA ISTNIENIE POLACZENIA
//

template <typename T>
bool Graph<T>::existconnection(int key){
	if(edges->isEmpty()) return false;
	switch(graphtype){
	case 'g':
	{
		if(edges->find(key)!=nullptr) return true;
		else return false;
	}
	break;
	case 'm':
	{
		for(int i=0; i<sizeM; i++){
			for(int j=0; j<sizeM; j++){
				if(matrix[i][j]->getPosition()==key) return true;
			}
		}
	}
	break;
	default: return false;
	break;
	}
	return false;
}

//
// SPRAWDZA CZY GRAF ISTNIEJE
//


template <typename T>
bool Graph<T>::isEmpty(){
	if(nodes->isEmpty()) return true;
	else return false;
}

//
// WSTAWIA WEZEL DO GRAFU
//


template <typename T>
Node<T>* Graph<T>::insert(T e){
	Node<T>* n = new Node<T>;
	n->setPosition(size);
	n->setElement(e);
	nodes->insert(size, n);
	size++;
	return n;
}

//
// LACZY DWA WEZLY
//


template <typename T>
Edge<T>* Graph<T>::connect(int s, int e, T elem){
	switch(graphtype){
	case 'g':
		{
			if(existnode(s) && existnode(e)){
				Edge<T>* n = new Edge<T>;
				n->setPosition(size);
				n->setElement(elem);
				n->setStart(nodes->find(s));
				n->setEnd(nodes->find(e));
				edges->insert(connections, n);
				nodes->find(s)->listofedges->insert(connections, n);
				connections++;
			}else return nullptr;
		}
		break;
		case 'm':
		{
			if(existnode(s) && existnode(e)){
				Edge<T>* n = new Edge<T>;
				n->setPosition(size);
				n->setElement(elem);
				n->setStart(nodes->find(s));
				n->setEnd(nodes->find(e));
				matrix[s-1][e-1] = n;
				nodes->find(s)->listofedges->insert(connections, n);
				connections++;
			}else return nullptr;
		}
		break;
	}
	
	return nullptr;
}

//
// USUWA POLACZENIE
//


template <typename T>
Edge<T>*  Graph<T>::removeConnection(int k){
	switch(graphtype){
	case 'g':
	{
		if(existconnection(k)){
			Node<T>* tmp = nodes->find(k);
			Edge<T>* tmp2 = tmp->listofedges->min();
			tmp->listofedges->removeMin();
			connections--;
			return tmp2;
		}else return nullptr;
	}
	break;
	case 'm':
	{
		if(existconnection(k)){
			Node<T>* tmp = nodes->find(k);
			Edge<T>* tmp2 = tmp->listofedges->min();
			tmp->listofedges->removeMin();
			connections--;
			return tmp2;
		}else return nullptr;
	}
	}
	return nullptr;
}

//
// SPRAWDZA CZY DWIE CZESCI GRAFU SA W JAKIS SPOSOB POLACZONE
//



template <typename T>
bool Graph<T>::areConnected(int s, int e){
	

	// std::cout << s << "TU BYŁEM\n";
	// bool* check = new bool[nodes->find(s)->listofedges->getSize()];
	bool checker = false;
	nodes->find(s)->visited = true;
	MyNode<Edge<T>*>* tmp = nodes->find(s)->listofedges->getHead();
	if(!(nodes->find(s)->listofedges->isEmpty())){
		for(int i=0; i<nodes->find(s)->listofedges->getSize(); i++){
			tmp = tmp->getNext();
			if(tmp->getElement()->getEnd()->getPosition()==e) return true;
			if(checker == true) return true;
			// std::cout << i;
			if(!(tmp->getElement()->getEnd()->visited)){
				checker = areConnected(tmp->getElement()->getEnd()->getPosition(),e);
			}
		}
	}
	return false;
}

#endif // GRAPH_H