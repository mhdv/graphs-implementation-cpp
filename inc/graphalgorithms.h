#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H
#include "graph.h"
#include "edgenode.h"
#include "queue.h"

//
// PRIM ALGORITHM
//


template <typename T>
int Prim(Graph<T>* graph){
	int weight = 0;
	Graph<T>* tmp = new Graph<T>;
	if(graph->isEmpty()) return -1;
	else{
		for(int i=1; i<graph->getSize(); i++){
			if(tmp->isEmpty()){
				tmp->insert(graph->getNode(i)->getElement());
				tmp->insert(graph->getListofedges(i)->min()->getEndElement());
				tmp->connect(i, i+1, graph->getListofedges(i)->min()->getElement());
				weight+=graph->getListofedges(i)->min()->getElement();
				graph->removeConnection(graph->getListofedges(i)->minNode()->getKey());
				i++;
			}else{
				int key = -1;
				int k = 1;
				for(int j=1; j<tmp->getSize(); j++){
					if(key==-1) key =graph->getListofedges(1)->minNode()->getKey();
					if(!graph->getListofedges(j)->isEmpty())
					if(graph->getListofedges(j)->minNode()->getKey()<key){
						key = graph->getListofedges(j)->minNode()->getKey();
						k=j;
					}
				}
				Edge<T>* tmp2 = graph->removeConnection(k);
				if(tmp2 == nullptr){
					return weight;
				}
				tmp->insert(tmp2->getEndElement());
				tmp->connect(tmp2->getStart()->getPosition(), tmp2->getEnd()->getPosition(), tmp2->getElement());
				weight+=tmp2->getElement();
			}
		}
	}
	delete tmp;
	return weight;
}

//
// KRUSKAL ALGORITHM
//


template <typename T>
int Kruskal(Graph<T>* graph){
	int weight = 0;
	Graph<T>* tmp = new Graph<T>;
	if(graph->isEmpty()) return -1;
	else{
		for(int i=1; i<graph->getConnections(); i++){
			if(tmp->isEmpty()){
				tmp->insert(graph->getEdge(i)->getStartElement());
				tmp->insert(graph->getEdge(i)->getEndElement());
				tmp->connect(i, i+1, graph->getEdge(i)->getElement());
				weight+=graph->getEdge(i)->getElement();
				graph->removeConnection(graph->getEdge(i)->getStart()->getPosition());
			}else{
				if(!tmp->existnode(graph->getEdge(i)->getStartElement())&&tmp->existnode(graph->getEdge(i)->getEndElement())){
					tmp->insert(graph->getEdge(i)->getStartElement());
					tmp->insert(graph->getEdge(i)->getEndElement());
				}
				if(tmp->existnode(graph->getEdge(i)->getStartElement())&&tmp->existnode(graph->getEdge(i)->getEndElement()))
				if(!tmp->areConnected(graph->getEdge(i)->getStartElement(),graph->getEdge(i)->getEndElement())){
					tmp->connect(i, i+1, graph->getEdge(i)->getElement());
					weight+=graph->getEdge(i)->getElement();
					graph->removeConnection(graph->getEdge(i)->getStart()->getPosition());
				}
			}
		}
	}
	delete tmp;
	return weight;
}



#endif