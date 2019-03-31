#include "lista.h"
#include "lista-element.h"
#include <iostream>

using namespace std;

int Compare( const void* p, const void* v );
int isEmptyList( ListItem* pList );
ListItem* FindPrevious( ListItem* pList, const void* x, ListItem** pPrev, int( _cdecl *comp )( const void*, const void* ) );


ListItem* CreateEmptyList()
{
	ListItem* pList = ( ListItem* )malloc( sizeof( ListItem ) );
	LISTINFO* item = ( LISTINFO* )malloc( sizeof( LISTINFO ) );

	if ( pList )
	{
		item->Distance = 0;
		item->HomeNumber = -1;
		item->Time = 0;
		pList->pInfo = item;
		pList->pNext = NULL;
	}
	return pList;
}

LISTINFO* CreateListElement( double distance, int homenumber, double time )
{
	LISTINFO* item = ( LISTINFO* )malloc( sizeof( LISTINFO ) );
	if ( item )
	{
		item->Distance = distance;
		item->HomeNumber = homenumber;
		item->Time = time;
	}
	else
	{
		printf( "\nInitialisation failed!\n" );
	}
	return item;
}


void Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	ListItem* pList = ( ListItem* )malloc( sizeof( ListItem ) );

	if ( pList )
	{
		pList->pInfo = pInfo;
		pList->pNext = pAfter->pNext;
		pAfter->pNext = pList;
	}
	else
	{
		perror( "\n Insertion failed!" );
	}
}

void InsertOnFront( ListItem* pList, LISTINFO* pInfo )
{
	Insert( pList, pInfo );
}


ListItem* Front( ListItem* pList )
{
	if ( !isEmptyList( pList ) )
		return pList->pNext;
	else
	{
		return NULL;
	}
}

void RemoveAfter( ListItem* pAfter )
{
	if ( pAfter->pNext )
	{
		ListItem* v = pAfter->pNext;
		pAfter->pNext = v->pNext;
		free( v );
	}
	else
		printf( "\n Error: Can not remove item! \n" );
}

void RemoveOnFront( ListItem* pList )
{
	RemoveAfter( pList );
}

void FreeList( ListItem* pList )
{
	while ( !isEmptyList( pList ) )
	{
		RemoveOnFront( pList );
	}
}

void DelList( ListItem** pHead )
{
	FreeList( *pHead );
	free( *pHead );
	*pHead = NULL;
}


int isEmptyList( ListItem* pList )
{
	if ( !pList )
	{
		printf( "\nError: List does not exist!" );
		return -1;
	}

	return !( pList->pNext );
}

ListItem* FindPrevious( ListItem* pList, const void* x, ListItem** pPrev, int( _cdecl *comp )( const void*, const void* ) )
{
	ListItem* pointer = pList->pNext;
	*pPrev = pList;
	while ( !isEmptyList( pointer ) )
	{
		if ( comp( x, pointer ) == 0 ) return pointer;

		*pPrev = pointer;
		pointer = pointer->pNext;

	}

	return *pPrev = NULL;
}




//void LSort( ListItem* pList, int( __cdecl * comp )( const void*, const void* ) )
//{
//	ListItem* poczatek = pList;
//
//	while ( poczatek->pNext )
//	{
//		ListItem* pointer = poczatek->pNext; // wskaznik na kolejne wyrazy listy
//		ListItem* preVsmall = poczatek; // element przed najmniejszym
//
//		while ( pointer->pNext ) // sprawdzam dopoki element wskazuje na kolejny element
//		{
//			if ( comp( pointer->pNext, preVsmall->pNext ) == -1 )
//				preVsmall = pointer;
//
//			pointer = pointer->pNext;
//		}
//
//		if ( preVsmall != poczatek )
//		{
//			pointer = preVsmall->pNext; // minimum bedzie elementem za preVsmall
//			preVsmall->pNext = preVsmall->pNext->pNext; // element przed najmniejszym wskazuje teraz na to, na co wskazywalo minimum
//			pointer->pNext = poczatek->pNext; // minimum wskazuje teraz na pierwszy element nieposortowanej listy
//			poczatek->pNext = pointer; // glowa wskazuje teraz na minimum
//		}
//		poczatek = poczatek->pNext;
//	}
//}

//void PrintList( ListItem* pList )
//{
//	if ( pList->pInfo )
//	{
//		ListItem* v = pList;
//		while ( v )
//		{
//			int value = v->pInfo->nKey;
//			printf( "%d ", value );
//			v = v->pNext;
//		}
//	}
//	else
//		printf( "\n List is empty! \n" );
//}



//int Compare( const void* p, const void* v )
//{
//	if ( ( ( ListItem* )p )->pInfo->nKey < ( ( ListItem* )v )->pInfo->nKey )	return -1;
//	else if ( ( ( ListItem* )p )->pInfo->nKey == ( ( ListItem* )v )->pInfo->nKey )	return 0;
//	else return 1;
//}