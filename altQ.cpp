#include "altQ.h"

PQueue* xPQInit( int nSize )
{
	PQueue* res = ( PQueue* )calloc( 1, sizeof( PQueue ) );
	if ( !res )
	{
		perror( "PQInit: allocation error" );
		return NULL;
	}
	res->PQCurrSize = 0;
	res->PQSize = nSize;
	res->pQueueArray = ( PQItem* )calloc( nSize, sizeof( PQItem ) );
	if ( !( res->pQueueArray ) )
	{
		perror( "PQInit: allocation error" );
	}
	return res;
}



//==================================
int		xPQIsEmpty( PQueue* pQueue )
{
	return !( pQueue->PQCurrSize );
}



//==================================
void	xPQEnqueue( PQueue* pQueue, int nKey, double nPrior )
{
	if ( pQueue->PQCurrSize == pQueue->PQSize )
	{
		perror( "PQEnqueue: no free space" );
		return;
	}
	//wstaw na koñcu
	pQueue->pQueueArray[pQueue->PQCurrSize].nKey = nKey;
	pQueue->pQueueArray[pQueue->PQCurrSize].nPrior = nPrior;

	//uaktualnij w górê
	xUpdateUp( pQueue, 0, pQueue->PQCurrSize++ );
}



//==================================
int		xPQDequeueu( PQueue* pQueue )
{
	if ( xPQIsEmpty( pQueue ) )
	{
		perror( "PQDequeueu: queue is empty" );
		return 0;
	}
	//zwraca z indeksu 0
	int res = pQueue->pQueueArray->nKey;
	//wpisaæ ostatni do 0-erowego
	*( pQueue->pQueueArray ) = pQueue->pQueueArray[pQueue->PQCurrSize - 1];
	//update w dó³
	xUpdateDown( pQueue, 0, pQueue->PQCurrSize-- );
	return res;
}



//==================================
void	xPQClearQueue( PQueue* pQueue )
{
	pQueue->PQCurrSize = 0;
	memset( pQueue->pQueueArray, 0, pQueue->PQSize * sizeof( PQItem ) );
}



//==================================
void	xPQRelease( PQueue** pQueue )
{
	free( ( *pQueue )->pQueueArray );
	free( *pQueue );
	*pQueue = NULL;
}



//==================================
void	xPQPrint( PQueue* pQueue )
{
	for ( int i = 0; i < pQueue->PQCurrSize; i++ )
		printf( "%d\t", pQueue->pQueueArray[i].nKey );
	//printInOrder( pQueue->pQueueArray, pQueue->PQCurrSize, 0 );
}



//==================================
void xUpdateDown( PQueue* pQueue, int l, int p )
{
	if ( l == p ) return;
	int i = l;
	int j = 2 * i + 1;
	PQItem x = pQueue->pQueueArray[i];

	while ( j <= p )
	{
		if ( j < p )
			if ( pQueue->pQueueArray[j].nPrior < pQueue->pQueueArray[j + 1].nPrior )
				j++;

		if ( pQueue->pQueueArray[i].nPrior < x.nPrior ) break;

		pQueue->pQueueArray[i] = pQueue->pQueueArray[j];
		i = j;
		j = 2 * i + 1;
	}
	pQueue->pQueueArray[i] = x;
}




//==================================
void xUpdateUp( PQueue* pQueue, int l, int p )
{
	int i = p;
	int j = ( i - 1 ) / 2;
	PQItem tmp = pQueue->pQueueArray[i];
	while ( i > 0 && pQueue->pQueueArray[j].nPrior < tmp.nPrior )
	{
		pQueue->pQueueArray[i] = pQueue->pQueueArray[j];
		i = j;
		j = ( i - 1 ) / 2;
	}
	pQueue->pQueueArray[i] = tmp;
}