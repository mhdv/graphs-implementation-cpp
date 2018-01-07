#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
//
#include "graphalgorithms.h"

// naglowki implementacji
#include "graph.h"

// funkcja generujaca losowe liczby bez powtorzen do grafów
void randomGraphGenerator(Graph<int>* graph, int size, float density=100);
void timeMeasure(time_t beginning, time_t ending);



int main(){
	srand(time(NULL));
	static int size = 500;

	// Graph<int>* test = new Graph<int>();
	// test->insert(1);
	// test->insert(2);
	// test->insert(3);
	// test->insert(66);
	// test->insert(22);
	// test->connect(1,2);
	// test->connect(2,5);
	// if(test->areConnected(3,5)) std::cout << "ta";


	Graph<int>* nowy = new Graph<int>('g', size);
	randomGraphGenerator(nowy, size, 25);
	time_t start = clock();
	Prim(nowy);
	time_t end = clock();
	timeMeasure(start, end);
	delete nowy;

	Graph<int>* nowy2 = new Graph<int>('g', size);
	randomGraphGenerator(nowy2, size, 50);
	start = clock();
	Prim(nowy2);
	end = clock();
	timeMeasure(start, end);
	delete nowy2;

	Graph<int>* nowy3 = new Graph<int>('g', size);
	randomGraphGenerator(nowy3, size, 75);
	start = clock();
	Prim(nowy3);
	end = clock();
	timeMeasure(start, end);
	delete nowy3;

	Graph<int>* nowy4 = new Graph<int>('g', size);
	randomGraphGenerator(nowy4, size, 100);
	start = clock();
	Prim(nowy4);
	end = clock();
	timeMeasure(start, end);
	delete nowy4;




	Graph<int>* nowy5 = new Graph<int>('g', size);
	randomGraphGenerator(nowy5, size, 25);
	start = clock();
	Kruskal(nowy5);
	end = clock();
	timeMeasure(start, end);
	delete nowy5;

	Graph<int>* nowy6 = new Graph<int>('g', size);
	randomGraphGenerator(nowy6, size, 50);
	start = clock();
	Kruskal(nowy6);
	end = clock();
	timeMeasure(start, end);
	delete nowy6;

	Graph<int>* nowy7 = new Graph<int>('g', size);
	randomGraphGenerator(nowy7, size, 75);
	start = clock();
	Kruskal(nowy7);
	end = clock();
	timeMeasure(start, end);
	delete nowy7;

	Graph<int>* nowy8 = new Graph<int>('g', size);
	randomGraphGenerator(nowy8, size, 100);
	start = clock();
	Kruskal(nowy8);
	end = clock();
	timeMeasure(start, end);
	delete nowy8;


	return 0;
}

void randomGraphGenerator(Graph<int>* graph, int size, float density){
	int* tmparr = new int[size];
	for(int i=0; i<size; i++){
		bool duplicate = false;
		tmparr[i]=rand()%(size*10)+1;
		for(int j=0; j<i; j++){
			if(tmparr[i]==tmparr[j]) duplicate = true;
		}
		if(duplicate) --i;
	}
	for(int i=0; i<size; i++){
		graph->insert(tmparr[i]);
	}
	float real_dens = 0.01*density*size;
	int dens = static_cast<int>(real_dens);
	for(int i=1; i<=dens; i++){
		for(int j=1; j<=dens; j++){
			graph->connect(i, j, rand()%(size*10)+1);
		}
	}
}


void timeMeasure(time_t beginning, time_t ending){
    std::cout << "\nCZAS WYKONANIA: " << (ending-beginning)/(CLOCKS_PER_SEC/1000) << "\n";
}