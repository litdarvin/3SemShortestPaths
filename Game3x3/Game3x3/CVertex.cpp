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


CVertex::CVertex( char wayToMe_, int chain_, int zeroPosition_ )
{
	wayToMe = wayToMe_;
	Chain = chain_;
	zeroPosition = zeroPosition_;
}

char CVertex::GetWay() const { return wayToMe;  }

bool CVertex::isItFinish() const
	{
		if( Chain == 123456780 ) return true;

		return false;
	}

void CVertex::CreateChildren(set<int>& Set)
	{
		int newChain;
		
		if( zeroPosition + 3 <= 8 && wayToMe != 'U' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition - 3 ))* ReturnByIndex( zeroPosition + 3 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'D', newChain, zeroPosition + 3 ) ) );
				Set.insert( newChain );
			}

		}
		if( zeroPosition - 3 >= 0 && wayToMe != 'D' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition + 3 ))* ReturnByIndex( zeroPosition - 3 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'U', newChain, zeroPosition - 3 ) ) );
				Set.insert( newChain );
			}
		}
		if (zeroPosition != 2 && zeroPosition != 5 && zeroPosition != 8 && wayToMe != 'L' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition - 1 ))* ReturnByIndex( zeroPosition + 1 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'R', newChain, zeroPosition + 1 ) ) );
				Set.insert( newChain );
			}
		}
		if (zeroPosition != 0 && zeroPosition != 3 && zeroPosition != 6 && wayToMe != 'R' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition + 1 ))* ReturnByIndex( zeroPosition - 1 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'L', newChain, zeroPosition - 1 ) ) );
				Set.insert( newChain );
			}
		}
	}

int CVertex::ReturnByIndex( int ind ) { return (Chain % powTen( 9 - ind ) - Chain % powTen( 8 - ind ))/ powTen( 8 - ind ); }

void bfs( shared_ptr<CVertex> graph, fstream& output )
{
	queue<shared_ptr<CVertex>> Queue;
	set<int> Set;
	weak_ptr<CVertex> result;
	Set.insert( graph->Chain );
	Queue.push( graph );
	bool stop = false;

	while( !stop )
	{
		shared_ptr<CVertex> current = Queue.front();
		Queue.pop();
		current->CreateChildren(Set);
		
		for( auto it = current->Children.begin(); it != current->Children.end(); ++it )
		{
			(*it)->Parent = current;
			
			if( !(*it)->isItFinish()) {
				Queue.push( *it );
			} else {
				result = *it;
				stop = true;
				break;
			}
		}
	}

	std::string resultString = "";
	int resultCount = 0;

	while( result.lock()->GetWay() != '\0' ) {

		resultString += result.lock()->GetWay();
		result = result.lock()->Parent;
		++resultCount;
	}

	output << resultCount<<std::endl;
	reverse( resultString.begin(), resultString.end() );
	output << resultString;
}
