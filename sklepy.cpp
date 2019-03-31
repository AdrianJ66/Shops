#include <iostream>
#include "graf.h"



//#define _DEBUG_



void DFS( Node* node, int v, int* visited )
{
	visited[v] = 1;
	ListItem* ptr = node[v].Neighbours;
	while ( ptr )
	{
		ptr->pInfo->Time = ptr->pInfo->Distance / AverageSpeed * 60;
		if ( !visited[ptr->pInfo->HomeNumber] )
			DFS( node, ptr->pInfo->HomeNumber, visited );
		ptr = ptr->pNext;
	}
}

void PrintDetails( Node* node, int nSize )
{

	for ( int i = 0; i < nSize; i++ )
	{
		node[i].StepsToShop = Dijkstra( node, nSize, i, 1 );
		//node[i].MinutesToShop = node[i].StepsToShop / AverageSpeed * 60;
		node[i].MinutesToShop = Dijkstra( node, nSize, i, 2 );
		if ( !( node[i].Monopoly ) )
		{
			printf( "\nDla wierzcholka nr %d, odleglosc do najblizszego sklepu pod numerem %d wynosi: %.2lf, pokonasz ja w %.2lf minut\n", i, node[i].BeerHere, node[i].StepsToShop, node[i].MinutesToShop );
		}
		else
		{
			printf( "\nJezeli tu mieszkasz to wygrales na loterii :D\n" );
			continue;
		}

		int temp = node[i].BeerHere;

		int k = 0;
		for ( int j = 1; j < nSize && node[i].RouteToShop[j - 1] != i; j++ )
		{
			node[i].RouteToShop[j] = temp;                         //ustawia droge z danego do mu do sklepu 
			temp = node[i].RouteToShop[temp];
			k = j;
		}

		//if ( !( node[i].Monopoly ) )
		//{
			//int tmp = node[i].BeerHere;
			//int k = 0; //int k = 1; 

			//while ( node[i].RouteToShop[k - 1] != i )
			//{
			//	if ( k >= nSize ) break;
			//	node[i].RouteToShop[k] = tmp;
			//	tmp = node[i].RouteToShop[tmp];
			//	k++;
			//}



		for ( int j = 0; j < k / 2; j++ )			//odwraca tablice zwierajaca droge
		{
			int temp = node[i].RouteToShop[k - j - 1];
			node[i].RouteToShop[k - j - 1] = node[i].RouteToShop[j];
			node[i].RouteToShop[j] = temp;
		}
		/*}*/

		int m = 0;
		while ( node[i].RouteToShop[m] != node[i].BeerHere )
			printf( "%d -> ", node[i].RouteToShop[m++] );
		printf(  "%d ", node[i].RouteToShop[m] );
	}

	

	//int YourPick;
	//printf( "\n\nZ ktorego domu chcesz dojsc do najblizszego sklepu?\nTwoj wybor: " );
	//scanf( "%d", &YourPick );
	//if ( node[YourPick].Monopoly )
	//{
	//	printf( "Jestes na miejscu!\n" );
	//	return;
	//}

	//int k = 0;
	//	while ( node[YourPick].RouteToShop[k] != node[YourPick].BeerHere )
	//		printf( "%d -> ", node[YourPick].RouteToShop[k++] );
	//	printf(  "%d ", node[YourPick].RouteToShop[k] );
	//

	
}


void PrintToFile( FILE* fout, Node* node, int nSize )
{
	for ( int i = 0; i < nSize; i++ )
	{
		node[i].StepsToShop = Dijkstra( node, nSize, i, 1 );
		//node[i].MinutesToShop = node[i].StepsToShop / AverageSpeed * 60;
		node[i].MinutesToShop = Dijkstra( node, nSize, i, 2 );

		if ( !( node[i].Monopoly ) )
		{
			fprintf( fout, "\nDla wierzcholka nr %d, odleglosc do najblizszego sklepu pod numerem %d wynosi: %.2lf, pokonasz ja w %.2lf minut\n", i, node[i].BeerHere, node[i].StepsToShop, node[i].MinutesToShop );
		}
		else
			fprintf( fout, "\nJezeli tu mieszkasz to wygrales na loterii :D\n" );

		if ( !( node[i].Monopoly ) )
		{
			int temp = node[i].BeerHere;
			int k = 0;

			for ( int j = 1; j < nSize && node[i].RouteToShop[j - 1] != i; j++ )
			{
				node[i].RouteToShop[j] = temp;                         //ustawia droge z danego do mu do sklepu 
				temp = node[i].RouteToShop[temp];
				k = j;
			}

			for ( int j = 0; j < k / 2; j++ ) //obracam tablice
			{
				int temp = node[i].RouteToShop[k - j - 1];
				node[i].RouteToShop[k - j - 1] = node[i].RouteToShop[j];
				node[i].RouteToShop[j] = temp;
			}

			int m = 0;					
			fprintf( fout, "%d -> ", node[i].HomeNum );
			while ( node[i].RouteToShop[m] != node[i].BeerHere )
				fprintf( fout, "%d -> ", node[i].RouteToShop[m++] );
			fprintf( fout, "%d ", node[i].RouteToShop[m] );			//wypisuje sciezke do monopolowego
		}

	}



	//int YourPick;
	//printf(  "\n\nZ ktorego domu chcesz dojsc do najblizszego sklepu?\nTwoj wybor: " );
	//scanf( "%d", &YourPick );
	//fprintf( fout, "\n\nWybrano sciezke dla domu nr: %d\n", YourPick );
	//if ( node[YourPick].Monopoly )
	//{
	//	fprintf( fout, "Jestes na miejscu!\n" );
	//	return;
	//}

	//int k = 0;
	//while ( node[YourPick].RouteToShop[k] != node[YourPick].BeerHere )
	//	fprintf( fout, "%d -> ", node[YourPick].RouteToShop[k++] );
	//fprintf( fout, "%d ", node[YourPick].RouteToShop[k] );

	fclose( fout );
}

double Dijkstra( Node* node, int nSize, int YourHome, int choice )
{
	PQueue* q = PQInit( nSize );		//inicjalizuje kolejke priorytetowa
	if ( !q )
	{
		printf( "ERROR_Dijkstra: Queue initialisation FAILED!.\n" );
		return -1;
	}


	double* CostsTab = ( double* )calloc( 1, nSize * sizeof( double ) ); //inicjalizuje tablice kosztow
	if ( !CostsTab )
	{
		printf( "ERROR_Dijkstra: Memory allocation FAILED! CostsTab.\n" );
		return -1;
	}


	int* PrevsTab = ( int* )calloc( nSize, sizeof( int ) ); //inicjalizuje tablice kosztow
	if ( !CostsTab )
	{
		printf( "ERROR_Dijkstra: Memory allocation FAILED! PrevsTab.\n" );
		return -1;
	}


	node[YourHome].RouteToShop = PrevsTab;

	for ( int i = 0; i < nSize; i++ ) //wypelnia tablice kosztow wartosciami maksymalnymi
	{
		CostsTab[i] = INT_MAX;
		PrevsTab[i] = -1;
	}

	node[YourHome].RouteToShop = PrevsTab;

	PQEnqueue( q, YourHome, 0 );
	CostsTab[YourHome] = 0;
	double len = 0;


	while ( !( PQIsEmpty( q ) ) )
	{
		int k = PQDequeueu( q );
		if ( node[k].Monopoly )
		{
			node[YourHome].BeerHere = k;
			PQRelease( &q );
			len = CostsTab[k];
			break;
		}

		else
		{
			ListItem* NeighList = node[k].Neighbours;

			if ( choice == 1 ) //najkrotsza droga
			{
				while ( NeighList )
				{
					int somsiad = NeighList->pInfo->HomeNumber;

					if ( CostsTab[k] + NeighList->pInfo->Distance < CostsTab[somsiad] )
					{
						CostsTab[somsiad] = CostsTab[k] + NeighList->pInfo->Distance;
						node[YourHome].RouteToShop[somsiad] = k;
						PQEnqueue( q, somsiad, CostsTab[somsiad] );
					}
					NeighList = NeighList->pNext;
				}
			}
			else if ( choice == 2 ) //najszybsza droga
			{
				while ( NeighList )
				{
					int somsiad = NeighList->pInfo->HomeNumber;

					if ( CostsTab[k] + NeighList->pInfo->Time < CostsTab[somsiad] )
					{
						CostsTab[somsiad] = CostsTab[k] + NeighList->pInfo->Time;
						node[YourHome].RouteToShop[somsiad] = k;
						PQEnqueue( q, somsiad, CostsTab[somsiad] );
					}
					NeighList = NeighList->pNext;
				}
			}

		}
	}
#ifdef _DEBUG_
	int no;
	printf( "DEBUG: Podaj wezel do sprawdzenia:\n" );
	scanf( "%d", &no );

	printf( "Najblizszy sklep: %d", node[no].BeerHere );
	printf( "Koszt dojscia do niego z wybranego wierzcholka: %.2lf", CostsTab[no] );

#endif // 


	/*node[YourHome].RouteToShop = PrevsTab;*/
	free( CostsTab );
	//free( PrevsTab );
	return len;
}


void FreeMemory( Node* node, int nSize )
{
	for ( int i = 0; i < nSize; i++ )
	{
		while ( ListItem* temp = node[i].Neighbours )
		{
			node[i].Neighbours = temp->pNext;
			free( temp );
		}
		free( node[i].RouteToShop );
	}
	free( node );
	node = NULL;
}
	
