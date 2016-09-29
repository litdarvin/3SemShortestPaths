//Автор: Литвинцева Дарья
//Описание: 3 семестр, задача 1

#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <assert.h>

using std::vector;
using std::cout;
using std::cin;

class CVertex {
public:
	CVertex() {	distance = std::numeric_limits<double>::infinity(); }
	//properties
	vector<CVertex*>& Children() { return children;	}
	vector<double>& ChildrenCost() { return childrenCost; }
	double& Distance() { return distance; }

private:
	vector<CVertex*> children;
	vector<double> childrenCost;
	double distance;
};

bool isNegativeCycleBFAlgorythm( vector<CVertex*>& graph, int numberCurrency )
{	
	assert(!graph.empty());
	(*graph.begin())->Distance() = 0;

	bool relaxed = false;
	for( int k = 0; k < numberCurrency - 1; ++k ) {
		relaxed = false;
		for( auto it = graph.begin(); it != graph.end(); ++it ) {
			vector<double>::iterator itChildrenCost = (*it)->ChildrenCost().begin();
			for( auto itChildren = (*it)->Children().begin(); itChildren != (*it)->Children().end(); ++itChildren ) {
				if( (*itChildren)->Distance() > (*it)->Distance() + *itChildrenCost ) {
					(*itChildren)->Distance() = (*it)->Distance() + *itChildrenCost;
					relaxed = true;
				}
				++itChildrenCost;
			}
		}

		if (!relaxed)
			break;
	}

	for( auto it = graph.begin(); it != graph.end(); ++it )	{
		auto itChildrenCost = (*it)->ChildrenCost().begin();
		for ( auto itChildren = (*it)->Children().begin(); itChildren != (*it)->Children().end(); ++itChildren ) {
			if( (*itChildren)->Distance() > (*it)->Distance() + *itChildrenCost )
				return true; //Negative cycle
			++itChildrenCost;
		}
	}
	//No negative cycle
	return false;
}

int main()
{
	int numberCurrency = 0;
	cin >> numberCurrency;
	vector<CVertex*> Graph;
	//Locate memory
	for( int i = 0; i < numberCurrency; ++i ) {
		Graph.push_back( new CVertex() );
	}
	//Reading
	int k = 0;	
	for( auto it = Graph.begin(); it != Graph.end(); ++it ) {
		for ( int i = 0; i < numberCurrency; ++i ) {
			if( i != k ) {
				double cost = 0;
				cin >> cost;
				if( cost != -1 ) {
					(*it)->Children().push_back( Graph.at(i) );
					(*it)->ChildrenCost().push_back( -log(cost) );
				}
			}
		}
		++k;
	}

	if( isNegativeCycleBFAlgorythm(Graph, numberCurrency) )
		cout << "YES" << std::endl;
	else
		cout << "NO" << std::endl;

	//Deleting
	for( auto it = Graph.begin(); it != Graph.end(); ++it ) {
		delete *it;
	}

	return 0;
}