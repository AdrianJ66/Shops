#pragma once

typedef struct
{
	int HomeNumber;
	double Distance;
	double Time;
} ListInfo;

#define LISTINFO ListInfo

typedef int( _cdecl* comp )( const void*, const void* );

int Compare( const void* p, const void* v );
