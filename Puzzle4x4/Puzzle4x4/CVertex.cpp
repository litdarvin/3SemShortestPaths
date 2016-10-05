#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>

using std::vector;
using std::queue;
using std::set;
using std::shared_ptr;
using std::weak_ptr;
using std::fstream;

#include "CVertex.h"

CVertex::CVertex( char wayToMe_, array<short, N>& chain_, short zeroPosition_ )
{
	wayToMe = wayToMe_;
	Chain = chain_;
	zeroPosition = zeroPosition_;
}

bool CVertex::isItFinish() const
{
	if( zeroPosition == 15 ) {
		for( short i = 0; i < N-1; ++i )
		{
			if (Chain[i] != i + 1)
				return false;
		}
		return true;
	}

	return false;
}

void CVertex::CreateChildren()
{
	array<short, N> newChain;

	if (zeroPosition <= 11 && wayToMe != 'U') {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition + 4] );
		std::find_if( Children.begin(), Children.end(),
			[]( const shared_ptr<CVertex> V1, const shared_ptr<CVertex> V2 ) { return V1->Chain == V2->Chain; } );
		Children.insert( shared_ptr<CVertex>( new CVertex( 'D', newChain, zeroPosition + 3 ) ) );
	}
	if (zeroPosition >= 4 && wayToMe != 'D') {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition - 4] );
		Children.push_back( shared_ptr<CVertex>( new CVertex( 'U', newChain, zeroPosition - 3 ) ) );
	}
	if (zeroPosition != 3 && zeroPosition != 7 && zeroPosition != 11 && zeroPosition != 15 && wayToMe != 'L') {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition + 1] );
		Children.push_back( shared_ptr<CVertex>( new CVertex( 'R', newChain, zeroPosition + 1 ) ) );
	}
	if (zeroPosition != 0 && zeroPosition != 4 && zeroPosition != 8 && zeroPosition != 12 && wayToMe != 'R') {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition - 1] );
		Children.push_back( shared_ptr<CVertex>( new CVertex( 'L', newChain, zeroPosition - 1 ) ) );
	}
}

