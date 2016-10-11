#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <utility>
#include <unordered_set>

using std::unordered_set;
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
	H = -1;
}

void CVertex::pushInGraph( array<short, N>& newChain, short zeroPosition_, vector<shared_ptr<CVertex>>& graph, char lastWayToMe_)
{
	auto candidate = std::find_if( graph.begin(), graph.end(),
		[newChain]( shared_ptr<CVertex> V1 ) { return V1->Chain == newChain; } );

	if( candidate == graph.end() ) {
		auto newMember = shared_ptr<CVertex>( new CVertex( newChain, zeroPosition_ ) );
		switch( lastWayToMe_ ) {
		case 'R':
		{
			newMember->wayToMeR = true;
			break;
		}
		case 'L':
		{
			newMember->wayToMeL = true;
			break;
		}
		case 'U':
		{
			newMember->wayToMeU = true;
			break;
		}
		case 'D':
		{
			newMember->wayToMeD = true;
			break;
		}
		default:
			break;
		}
		newMember->lastWayToMe = lastWayToMe_;
		Children.push_back( newMember );
		graph.push_back( newMember );
	} else {
		( *candidate )->lastWayToMe = lastWayToMe_;
		switch( lastWayToMe_ ) {
		case 'R':
		{
			( *candidate )->wayToMeR = true;
			break;
		}
		case 'L':
		{
			( *candidate )->wayToMeL = true;
			break;
		}
		case 'U':
		{
			( *candidate )->wayToMeU = true;
			break;
		}
		case 'D':
		{
			( *candidate )->wayToMeD = true;
			break;
		}
		default:
			break;
		}
		Children.push_back( *candidate );
	}
}

bool CVertex::isItFinish() const
{
	if( zeroPosition == N - 1 ) {
		for( short i = 0; i < N - 1; ++i ) {
			if( Chain[i] != i + 1 )
				return false;
		}
		return true;
	}
	return false;
}

void CVertex::CreateChildren( vector<shared_ptr<CVertex>>& graph )
{
	array<short, N> newChain;

	if( zeroPosition <= N-n-1 && ShortestWayToMe != 'U' ) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition + n] );
		pushInGraph( newChain, zeroPosition + n, graph, 'D' );
	}
	if( zeroPosition >= n && ShortestWayToMe != 'D' ) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition - n] );
		pushInGraph( newChain, zeroPosition - n, graph, 'U' );
	}
	if( zeroPosition%n != 3 && ShortestWayToMe != 'L' ) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition + 1] );
		pushInGraph( newChain, zeroPosition + 1, graph, 'R' );
	}
	if( zeroPosition%n != 0 && ShortestWayToMe != 'R' ) {
		newChain = Chain;
		std::swap( newChain[zeroPosition], newChain[zeroPosition - 1] );
		pushInGraph( newChain, zeroPosition - 1, graph, 'L' );
	}
}

