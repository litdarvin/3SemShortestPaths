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

CVertex::CVertex( array<short, N>& chain_, short zeroPosition_ )
{
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

void CVertex::CreateChildren( set<shared_ptr<CVertex>>& graph )
{
	array<short, N> newChain;

	if (zeroPosition <= 11 && !wayToMeU) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition + 4] );
		auto candidate = std::find_if( graph.begin(), graph.end(),
			[newChain]( const shared_ptr<CVertex> V1 ) { return V1->Chain == newChain; } );
		if (candidate == graph.end()) {
			auto newMember = shared_ptr<CVertex>( new CVertex( newChain, zeroPosition + 3 ) );
			newMember->wayToMeD = true;
			Children.push_back( newMember );
			graph.insert( newMember );
		}
		else {
			Children.push_back( *candidate );
			(*candidate)->wayToMeD = true;
		}
	}
	if (zeroPosition >= 4 && !wayToMeD) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition - 4] );
		auto candidate = std::find_if( graph.begin(), graph.end(),
			[newChain]( const shared_ptr<CVertex> V1 ) { return V1->Chain == newChain; } );
		if (candidate == graph.end()) {
			auto newMember = shared_ptr<CVertex>( shared_ptr<CVertex>( new CVertex( newChain, zeroPosition - 3 ) ) );
			newMember->wayToMeU = true;
			Children.push_back( newMember );
			graph.insert( newMember );
		}
		else {
			Children.push_back( *candidate );
			(*candidate)->wayToMeU = true;
		}
	}
	if (zeroPosition != 3 && zeroPosition != 7 && zeroPosition != 11 && zeroPosition != 15 && !wayToMeL) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition + 1] );
		auto candidate = std::find_if( graph.begin(), graph.end(),
			[newChain]( const shared_ptr<CVertex> V1 ) { return V1->Chain == newChain; } );
		if (candidate == graph.end()) {
			auto newMember = shared_ptr<CVertex>( shared_ptr<CVertex>( new CVertex( newChain, zeroPosition + 1 ) ) );
			newMember->wayToMeR = true;
			Children.push_back( newMember );
			graph.insert( newMember );
		}
		else {
			Children.push_back( *candidate );
			(*candidate)->wayToMeR = true;
		}
	}
	if (zeroPosition != 0 && zeroPosition != 4 && zeroPosition != 8 && zeroPosition != 12 && !wayToMeR) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition - 1] );
		auto candidate = std::find_if( graph.begin(), graph.end(),
			[newChain]( const shared_ptr<CVertex> V1 ) { return V1->Chain == newChain; } );
		if (candidate == graph.end()) {
			auto newMember = shared_ptr<CVertex>( shared_ptr<CVertex>( new CVertex( newChain, zeroPosition - 1 ) ) );
			newMember->wayToMeL = true;
			Children.push_back( newMember );
			graph.insert( newMember );
		}
		else {
			Children.push_back( *candidate );
			(*candidate)->wayToMeL = true;
		}
	}
}

