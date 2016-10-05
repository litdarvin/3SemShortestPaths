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
	return 0;
}

bool AStartAlgorythm( shared_ptr<CVertex> graph, fstream& output )
{
	priority_queue<shared_ptr<CVertex>> Queue;
	set<shared_ptr<CVertex>> SetOpenedVertex;
	weak_ptr<CVertex> result;
	Queue.push( graph );
	graph->DistanceG = 0;
	graph->DistanceF = graph->DistanceG + Heuristic( graph );
	bool stop = false;

	while (!stop)
	{
		shared_ptr<CVertex> current = Queue.top();
		Queue.pop();
		if (current->isItFinish()) return true;
		SetOpenedVertex.insert( current );

		for (auto it = current->Children.begin(); it != current->Children.end(); ++it)
		{
			SetOpenedVertex.find( *it );
		}
	}

}
/*(start, goal) :
	U = \varnothing
	Q = \varnothing
	Q.push( start )
	g[start] = 0
	f[start] = g[start] + h( start )
	while Q.size() != 0
		current = вершина из Q с минимальным значением f
		if current == goal
			return true                                           // нашли путь до нужной вершины
			Q.remove( current )
			U.push( current )
			for v : смежные с current вершины
				tentativeScore = g[current] + d( current, v )           // d(current, v) — стоимость пути между current и v 
				if v \in U and tentativeScore >= g[v]
					continue
					if v \notin U or tentativeScore < g[v]
						parent[v] = current
						g[v] = tentativeScore
						f[v] = g[v] + h( v )
						if v \notin Q
							Q.push( v )
							return false*/

int main()
{

}