#include <iostream>
#include <vector>

using std::vector;

#include "CVertex.h"
#include "BinaryHeap.h"

CVertex* CBinaryHeap::top()
{
	CVertex* res = elements[0];
	elements.erase( elements.begin() );
	if( elements.begin() != elements.end() ) {
		elements.begin() = elements.end() - 1;
	}
	--heapSize;
	increaseKey( 0 );
	return res;
}

int CBinaryHeap::push( CVertex* v )
{
	++heapSize;
	elements.push_back( v );
	return decreaseKey( heapSize - 1 );
}

int CBinaryHeap::increaseKey( int index)
{
	while( 2 * index + 1 < heapSize ) {
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int j = left;
		if( right < heapSize && elements[right]->DistanceF < elements[left]->DistanceF )
			j = right;
		if( elements[index]->DistanceF < elements[j]->DistanceF )
			break;
		std::swap( elements[index], elements[j] );
		index = j;
	}
	return index;
}

int CBinaryHeap::decreaseKey( int index )
{
	while( elements[index]->DistanceF < elements[( index - 1 ) / 2]->DistanceF ) {
		std::swap( elements[index], elements[( index - 1 ) / 2] );
		index = ( index - 1 ) / 2;
	}
	return index;
}