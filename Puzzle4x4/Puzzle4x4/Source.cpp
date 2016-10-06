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

int Heuristic( shared_ptr<CVertex> current )
{
	int ManhettenDistance = 0;

	for (int i = 0; i < N; ++i)
		ManhettenDistance += abs( (current->Chain[i] - 1) / 4 - (i - 1) / 4 ) + abs( (current->Chain[i] - 1) % 4 - (i - 1) % 4 );

	return ManhettenDistance;
}

int AStartAlgorythm( shared_ptr<CVertex> start )
{
	priority_queue<shared_ptr<CVertex>> Queue;
	set<shared_ptr<CVertex>> Graph;
	Graph.insert( start );
	set<shared_ptr<CVertex>> VertexInQueue;
	set<shared_ptr<CVertex>> SetOpenedVertex;
	weak_ptr<CVertex> result;
	Queue.push( start );
	VertexInQueue.insert( start );
	start->DistanceG = 0;
	start->DistanceF = start->DistanceG + Heuristic( start );

	shared_ptr<CVertex> current;

	while( Queue.size() != 0 )
	{
		current = Queue.top();
		Queue.pop();
		VertexInQueue.erase( current );
		if (current->isItFinish()) break;
		SetOpenedVertex.insert( current );
		current->CreateChildren( Graph );
		for (auto it = current->Children.begin(); it != current->Children.end(); ++it)
		{
			auto containedInSet = SetOpenedVertex.find( *it );
			//if (containedInSet != SetOpenedVertex.end() && current->DistanceG + 1 >= (*it)->DistanceG) continue;

			if (containedInSet == SetOpenedVertex.end() || current->DistanceG + 1 < (*it)->DistanceG) {
				(*it)->Parent = current;
				(*it)->DistanceG = current->DistanceG + 1;
				(*it)->DistanceF = (*it)->DistanceG + Heuristic( *it );
				if (VertexInQueue.find( *it ) == VertexInQueue.end()) {
					Queue.push( *it );
					VertexInQueue.insert( *it );
				}
			}
		}
	}
	return current->DistanceG;
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
	output << AStartAlgorythm( start );
}