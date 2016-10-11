#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <ctime>
#include <map>
#include <unordered_set>

using std::vector;
using std::priority_queue;
using std::set;
using std::shared_ptr;
using std::weak_ptr;
using std::map;
using std::fstream;
using std::unordered_set;
using std::pair;

#include "CVertex.h"
#include "BinaryHeap.h"

int Heuristic( const CVertex* current )
{
	int ManhettenDistance = 0;

	for( int i = 0; i < N; ++i ) {
		if( current->Chain[i] != 0 ) {
			ManhettenDistance += abs( ( current->Chain[i] - 1 ) / n - i / n ) + abs( ( current->Chain[i] - 1 ) % n - i % n );

			//linear conflict
		/*	if( ( current->Chain[i] - 1 ) / n == i / n ) {
				for( int j = n * ( i / n ); j < i; ++j ) {
					if( ( current->Chain[j] - 1 ) / n == j / n && current->Chain[j] > current->Chain[i] && current->Chain[j] != 0 )
						ManhettenDistance += 1;
				}
				for( int j = i + 1; j < n * ( ( i + 1 ) / n ); ++j ) {
					if( ( current->Chain[j] - 1 ) / n == j / n && current->Chain[j] < current->Chain[i] && current->Chain[j] != 0 )
						ManhettenDistance += 1;
				}
			}
			if( ( current->Chain[i] - 1 ) % n == i % n ) {
				for( int j = i%n; j < i; j += n ) {
					if( ( current->Chain[j] - 1 ) % n == j % n && current->Chain[j] > current->Chain[i] && current->Chain[j] != 0 )
						ManhettenDistance += 1;
				}
				for( int j = i; j < n*( i%n ); j += n ) {
					if( ( current->Chain[j] - 1 ) % n == j % n && current->Chain[j] < current->Chain[i] && current->Chain[j] != 0 )
						ManhettenDistance += 1;
				}
			}*/
		}
	}
	ManhettenDistance += abs( current->zeroPosition / n - 3 ) + abs( current->zeroPosition % n - 3 );
	/*
	//corner conflict
	//left corners
	if( current->Chain[0] != 0 && current->Chain[0] != 1 && current->Chain[1] == 2 && current->Chain[n] == n + 1 ) {
		if( ( current->Chain[0] - 1 ) / n != 0 && ( current->Chain[0] - 1 ) % n != 0 )
			ManhettenDistance += 2;
		else {
			if( current->Chain[0] < 2 && current->Chain[0] < n + 1 )
				ManhettenDistance += 2;
		}
	}

	if( current->Chain[n - 1] != 0 && current->Chain[n - 1] != n && current->Chain[n - 2] == n - 1 && current->Chain[2 * n - 1] == 2 * n ) {
		if( ( current->Chain[n - 1] - 1 ) / n != 0 && ( current->Chain[n - 1] - 1 ) % n != 0 )
			ManhettenDistance += 2;
		else {
			if( current->Chain[n - 1] > n - 1 && current->Chain[n - 1] < 2 * n )
				ManhettenDistance += 2;
		}
	}
	//right corner
	if( current->Chain[N - n] != 0 && current->Chain[N - n] != N - n + 1 && current->Chain[N - n + 1] == N - n + 2
		&& current->Chain[N - 2 * n] == N - 2 * n + 1 ) {
		if( ( current->Chain[N - 2 * n] - 1 ) / n != n - 1 && ( current->Chain[N - 2 * n] - 1 ) % n != n - 1 )
			ManhettenDistance += 2;
		else {
			if( current->Chain[N - 2 * n] < N - n + 2 && current->Chain[N - 2 * n] > N - 2 * n + 1 )
				ManhettenDistance += 2;
		}
	}*/

	return ManhettenDistance;
}

void AStartAlgorythm( shared_ptr<CVertex> start, fstream& output )
{
	CBinaryHeap Queue;
	vector<shared_ptr<CVertex>> Graph;
	map<CVertex*, int> VertexInQueue;
	unordered_set<CVertex*> SetOpenedVertex;


	VertexInQueue.insert( pair<CVertex*, int>( start.get(), 0 ) );
	start->DistanceG = 0;
	start->H = Heuristic( start.get() );
	start->DistanceF = start->DistanceG + start->H;
	Graph.push_back( start );
	Queue.push( start.get() );
	int last = start->DistanceF;
	CVertex* current = 0;

	while( Queue.size() != 0 ) {

		current = Queue.top();
	//	if( last > current->DistanceF )
		//	system( "pause" );
		last = current->DistanceF;
		VertexInQueue.erase( current );
		if( current->isItFinish() ) {
			break;
		}
		SetOpenedVertex.insert( current );
		current->CreateChildren( Graph );

		for( auto it = current->Children.begin(); it != current->Children.end(); ++it ) {
			if( SetOpenedVertex.find( ( *it ).get() ) == SetOpenedVertex.end() || current->DistanceG + 1 < ( *it )->DistanceG ) {
				( *it )->ShortestWayToMe = ( *it )->lastWayToMe;
				( *it )->Parent = current;
				( *it )->DistanceG = current->DistanceG + 1;

				if( ( *it )->H == -1 ) {
					( *it )->H = Heuristic( ( *it ).get() );
				}
				( *it )->DistanceF = ( *it )->DistanceG + Heuristic( ( *it ).get() );

				if( VertexInQueue.find( ( *it ).get() ) == VertexInQueue.end() ) {
					int index = Queue.push( ( *it ).get() );
					VertexInQueue.insert( pair<CVertex*, int>( ( *it ).get(), index ) );
				}
			}
		}
	}

	int res = current->DistanceG;
	std::string fullway;
	while( current->Parent != 0 ) {
		fullway += current->ShortestWayToMe;
		current = current->Parent;
	}
	output << res << std::endl;
	reverse( fullway.begin(), fullway.end() );
	output << fullway;
}

bool CheckPossibility( array<short, N>& chain, short zeroPosition)
{
	int sum = 0;
	for( int i = 0; i < N; ++i ) {
		if( chain[i] != 0 ) {
			for( int j = i + 1; j < N; ++j ) {
				if( chain[j] < chain[i] && chain[j] != 0 ) ++sum;
			}
		}
	}

	return ( sum + ( zeroPosition - 1 ) / n ) % 2 != 0;
}

int main()
{
	unsigned int start_time = clock();
	fstream input( "puzzle.txt", fstream::in );
	fstream output( "puzzle2.txt", fstream::out );

	short zeroPosition = -1;
	array<short, N> Chain;
	//reading for checking and for graph
	for( int i = 0; i < N; ++i ) {
		input >> Chain[i];
		if( Chain[i] == 0 ) zeroPosition = i;
	}
	if( CheckPossibility( Chain, zeroPosition ) ) {
		auto start = shared_ptr<CVertex>( new CVertex( Chain, zeroPosition ) );
		AStartAlgorythm( start, output );
	} else {
		output << -1;
	}
	output << std::endl << "min: " << ( clock() - start_time ) / 60000 << " sec: " << ( clock() - start_time ) / 1000.0;
	output.close();
	input.close();
	system( "pause" );
}