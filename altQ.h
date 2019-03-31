#pragma once
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

typedef struct
{
	int nKey;
	double nPrior;
} PQItem;

typedef struct
{
	PQItem* pQueueArray; //kolejka realizowana w postaci stogu
	int PQSize; // rozmiar kolejki priorytetowej
	int PQCurrSize; //iloœæ elementów w kolejce
} PQueue;

PQueue* xPQInit( int nSize );
int		xPQIsEmpty( PQueue* pQueue );
void	xPQEnqueue( PQueue* pQueue, int nKey, double nPrior );
int		xPQDequeueu( PQueue* pQueue );
void	xPQClearQueue( PQueue* pQueue );
void	xPQRelease( PQueue** pQueue ); //zwalnia pamiêæ we/wy NULL
void	xPQPrint( PQueue* pQueue ); // inorder

void xUpdateDown( PQueue* pQueue, int l, int p );
void xUpdateUp( PQueue* pQueue, int l, int p );

//dodatkowe //potem usun¹æ
void	xDecreaseKey( PQueue* pQueue, int nKey, int nPrior );
void	xIncreaseKey( PQueue* pQueue, int nKey, int nPrior );