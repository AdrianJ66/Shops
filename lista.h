#pragma once

#include "lista-element.h"

typedef struct tagListItem
{
	LISTINFO* pInfo;
	tagListItem* pNext;

}ListItem;

ListItem* FindPrevious( ListItem* pList, const void* x, ListItem** pPrev, int( _cdecl *comp )( const void*, const void* ) );		// znajduje																						podany element na liscie // wskaznik na funkcje Compare
LISTINFO* CreateListElement( double distance, int homenumber, double time ); //moja funkcja prywatna
ListItem* CreateEmptyList();	// tworzy pusta liste (ma zrobic pusty element na poczatku), jesli funkcja zwr�ci NULL
ListItem* Front( ListItem* pList );		//odpowiednik funkcji top - zwraca szczytowy element listy (ca�y element listy)
void Insert( ListItem* pAfter, LISTINFO* pInfo );		// wstawianie po danym elemencie
void InsertOnFront( ListItem* pList, LISTINFO* pInfo );		//wstawianie na poczatek
void RemoveAfter( ListItem* pAfter );		//usuniecie elementow o danych wskaznikach, po elemencie na kt�ry wskazuje wska�nik
void RemoveOnFront( ListItem* pList );		//odpowiednik pop - usuwa szczytowy element z listy
void FreeList( ListItem* pList );		//czysci liste - zostawia tylko glowe
void LSort( ListItem* pList, int( __cdecl * comp )( const void*, const void* ) );
void DelList( ListItem** pHead );		//usuwa ca�� liste
void PrintList( ListItem* pList );
