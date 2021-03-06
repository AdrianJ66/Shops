// Sklepy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graf.h"

using namespace std;

int ReadFile( Node** node, const char* file );

#define REALLOC_INT 3
//#define _DEBUG_


int main( int argc, char** argv )
{
	if ( argc != 2 )
	{
		printf( "Missing input file!\n" );
		return -1;
	}
	
	Node* Homes = NULL; //tablica przechowujaca struktury bedace wierzcholkami grafu


	int lines = ReadFile( &Homes, argv[1] );
	if ( !lines )
	{
		printf( "Unable to read the file!\n" );
		return -2;
	}
	


	int* visited = ( int* )calloc( lines, sizeof( int ) );

	if ( !visited )
	{
		printf( "Unable to alloc visited array!\n" );
		return -2;
	}
#ifdef _DEBUG_
	for ( int i = 0; i < lines; i++ )
	{
		printf( "\n~~~~~~||~~~~~~\nNumer domu: %d,\nMonopol: %d,\nIle sasiadow: %d", Homes[i].HomeNum, Homes[i].Monopoly, Homes[i].NeighboursNumber );
		ListItem* ptr = Homes[i].Neighbours->pNext;
		while( ptr )
		{
			printf( "\n--Sasiad nr: %d,\n--Dystans do somsiada: %.2lf,\n--Czas do somsiada: %.2lf", Homes[i].Neighbours->pInfo->HomeNumber, Homes[i].Neighbours->pInfo->Distance, Homes[i].Neighbours->pInfo->Time );
			ptr = ptr->pNext;
		}
	}
#endif // _DEBUG_

	DFS( Homes, 0, visited );

	FILE* Output = fopen( "./result.txt", "w" );

	//PrintDetails( Homes, lines );
	PrintToFile( Output, Homes, lines );

	FreeMemory( Homes, lines );

	return 123;
}




int ReadFile( Node** node, const char* file )
{
	FILE* data = fopen( file, "r" );
	if ( !data )
	{
		printf( "Error: Failed to open the data sheet!\n" );
		return -3;
	}

	int lines = 0;
	char c;


	while ( !feof( data ) )
	{
		if ( !( lines%REALLOC_INT ) ) //realokuje tablice struktur co 3 linijki pliku wsadowego
		{
			Node* tmp = ( Node* )realloc( *node, sizeof( Node )*( lines + REALLOC_INT ) ); //tablica przechowujaca wezly struktury
			if ( !tmp )
			{
				printf( "ReadData: allocation error" );
				return 0;
			}
			*node = tmp;
			memset( ( *node + lines ), 0, sizeof( Node ) * REALLOC_INT ); //wyplenienie zerami jeszcze nie zapelnionych elementow tablicy
		}

		Node* pointer = &( ( *node )[lines++] );
		fscanf( data, "%d %d", &pointer->HomeNum, &pointer->Monopoly );
		fscanf( data, "%d", &pointer->NeighboursNumber );
		ListItem* tmp = CreateEmptyList();

		while ( !feof( data ) && ( ( c = fgetc( data ) ) != '\n' ) )
			if ( c >= '0' && c <= '9' )
			{
				ungetc( c, data );
		//for ( int i = 0; i < pointer->NeighboursNumber; i++ )
		//	{
				LISTINFO* tmpItem = ( LISTINFO* )calloc( 1, sizeof( LISTINFO ) );
				if ( !tmp )
				{
					printf( "ReadData: allocation error" );
					return 0;
				}
				fscanf( data, "%d", &tmpItem->HomeNumber );
				fscanf( data, "%lf", &tmpItem->Distance );
				tmpItem->Time = 0;

				Insert( tmp, tmpItem );
				
			}
		pointer->Neighbours = tmp;
	}
	fclose( data );
	return lines;
}

//Na podstawie danych z rysunku mamy stworzyc plik tekstowy opisujacy graf nieskierowany, za pomoca list incydencji, nalezy pamietac indexy domow, czy to sklep czy nie, dlugosc sciezki do najblizszego sklepu i jego indeks, liste nastepnikow, i w elemencie nastepnika trzeba bedzie pamietac odleglosc do niego i czas przejscia do niego, ktory ma byc definiowany preprocesoerem, ustawiany na srednio 5 km/h. Obliczamy czas przejscia w minutach. 
//Tablice wezlow realokujemy dynamicznie, tak jak w lotto.

//Plik wsadowy:
//nr wierzchołka / sklep czy dom / ilość sąsiadów / sąsiad - odległość( dla każdego sąsiada )

//
//Plik wejsciowy jest parametrem programu, wyjsciowy moze byc dowolnie zaszyty w programie. Ilosc wezlow miasta nie jest okreslona, wiec trzeba bedzie realokowac co trzy wezly, 
//
//zrob dwa przegladania tego drzewa.
//
//void BFS                            ale masz robic DFS a nie bfs!!!!
//{
//	//to szkic wymagajacy dodatkowo kolejki fifo
//	//zbadaj v -> zbadaj nastepnik v -> zbadaj nastepnik 
//	q = NULL;
//enqueue( q, v );
//wgile( noEmpty( q ) do
//{
//	u = dequeue( q );
//	for ( each w z L[u] )
//	{
//		if ( !mark[w] )
//		{
//			mark[w] = 1; visit( w );
//			enqueue( q, w );
//		}
//	}
//}
//	   }
//
//	   algorytm szukania najkrotszej sciezki - Dijkstry, potrzebna jest do niego kolejka priorytetowa
//
//		Mamy to zrobic 2x, tzn wyszukiwanie najkroszej sciezki wzglem odleglosci  oraz to samo wzgledem czasu. Mamy to zrobic dla kazdego wezla w grafie, ktory nie jest sklepem.

