#include <vector>
#include <assert.h>
using std::vector;


struct CVertex {

	CVertex() {	Distance = std::numeric_limits<double>::infinity(); }
	vector<CVertex*> Children;
	vector<double> ChildrenCost;
	double Distance;
};

bool isNegativeCycleBFAlgorythm( vector<CVertex*>& graph, int numberCurrency )
{	
	assert(!graph.empty());
	(*graph.begin())->Distance = 0;

	bool relaxed = false;
	for( int k = 0; k < numberCurrency - 1; ++k ) {
		relaxed = false;
		for( auto it = graph.begin(); it != graph.end(); ++it ) {
			vector<double>::iterator itChildrenCost = (*it)->ChildrenCost.begin();
			for( auto itChildren = (*it)->Children.begin(); itChildren != (*it)->Children.end(); ++itChildren ) {
				if( (*itChildren)->Distance > (*it)->Distance + *itChildrenCost ) {
					(*itChildren)->Distance = (*it)->Distance + *itChildrenCost;
					relaxed = true;
				}
				++itChildrenCost;
			}
		}

		if (!relaxed)
			break;
	}

	for( auto it = graph.begin(); it != graph.end(); ++it )	{
		auto itChildrenCost = (*it)->ChildrenCost.begin();
		for ( auto itChildren = (*it)->Children.begin(); itChildren != (*it)->Children.end(); ++itChildren ) {
			if( (*itChildren)->Distance > (*it)->Distance + *itChildrenCost )
				return true; //Negative cycle
			++itChildrenCost;
		}
	}
	//No negative cycle
	return false;
}