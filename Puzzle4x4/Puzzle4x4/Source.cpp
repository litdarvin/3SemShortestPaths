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
using std::priority_queue;
using std::set;
using std::shared_ptr;
using std::weak_ptr;
using std::fstream;
#include "CVertex.h"

int Heuristic( CVertex* current )
{
	int ManhettenDistance = 0;

	for( int i = 0; i < N; ++i ) {
		if( current->Chain[i] != 0 ) {
			ManhettenDistance += abs( ( current->Chain[i] - 1 ) / 4 - i / 4 ) + abs( ( current->Chain[i] - 1 ) % 4 - i % 4 );
		}
	}

	return ManhettenDistance;
}

class Compare {
public:
	bool operator() ( const CVertex* V1, const CVertex* V2 )
	{
		return false;
	}
};

int AStartAlgorythm( CVertex* start )
{
	//auto comp = []( const shared_ptr<CVertex> V1, const shared_ptr<CVertex> V2 ) { return V1->DistanceF > V1->DistanceG; };
	priority_queue < CVertex*, vector<CVertex*>, Compare > Queue;
	set<CVertex*> Graph;
	Graph.insert( start );
	set<CVertex*> VertexInQueue;
	set<CVertex*> SetOpenedVertex;
	weak_ptr<CVertex> result;
	Queue.push( start );
	VertexInQueue.insert( start );
	start->DistanceG = 0;
	start->DistanceF = start->DistanceG + Heuristic( start );

	CVertex* current = 0;

	while( Queue.size() != 0 )
	{
		current = Queue.top();
		VertexInQueue.erase( current );
		Queue.pop();
		if( current->isItFinish() ) {
			break;
		}
		SetOpenedVertex.insert( current );
		current->CreateChildren( Graph );

		for (auto it = current->Children.begin(); it != current->Children.end(); ++it)
		{
			auto containedInSet = SetOpenedVertex.find( (*it).get() );
			//if (containedInSet != SetOpenedVertex.end() && current->DistanceG + 1 >= (*it)->DistanceG) continue;
			if (containedInSet == SetOpenedVertex.end() || current->DistanceG + 1 < (*it)->DistanceG) {
				(*it)->Parent = current;
				(*it)->DistanceG = current->DistanceG + 1;
				(*it)->DistanceF = (*it)->DistanceG + Heuristic( (*it).get() );
				if (VertexInQueue.find( ( *it ).get() ) == VertexInQueue.end()) {
					Queue.push( ( *it ).get() );
					VertexInQueue.insert( ( *it ).get() );
				}
			}
		}
	}
	if( current != 0 ) {
		return current->DistanceG;
	}
	return -1;
}

int main()
{
	fstream input( "puzzle.txt", fstream::in );
	fstream output( "puzzle1.txt", fstream::out );


	short zeroPosition = -1;
	array<short, N> Chain;
	//reading for checking and for graph
	for (int i = 0; i < N; ++i)
	{
		input >> Chain[i];
		if (Chain[i] == 0) zeroPosition = i;
	}

	auto start = shared_ptr<CVertex>(new CVertex( Chain, zeroPosition ));
	output << AStartAlgorythm( start.get() );
}