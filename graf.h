#pragma once

#include "lista.h"
#include "lista-element.h"
#include "priorQ.h"
//#include "altQ.h"

#define EstateSize 27
#define AverageSpeed 5		//km/h
							//odleglosci pomiedzy wezlami sa podane w kilometrach
typedef struct tagNode
{
	ListItem* Neighbours;
	int HomeNum;
	int Monopoly;
	int NeighboursNumber; 
	double StepsToShop;
	double MinutesToShop;
	int* RouteToShop; //
	int BeerHere; //indeks najblizszego sklepu 
}Node;

double Dijkstra( Node* node, int nSize, int YourHome, int choice );
void PrintDetails( Node* node, int nSize );
void PrintToFile( FILE* fout, Node* node, int nSize );
void FreeMemory( Node* node, int nSize );
void DFS( Node* node, int v, int* visited );
