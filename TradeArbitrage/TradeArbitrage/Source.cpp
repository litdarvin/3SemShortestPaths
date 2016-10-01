//Автор: Литвинцева Дарья
//Описание: 3 семестр, задача 1

#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>
#include "CVertex.h"

using std::vector;
using std::cout;
using std::cin;



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
					(*it)->Children.push_back( Graph.at(i) );
					(*it)->ChildrenCost.push_back( -log(cost) );
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