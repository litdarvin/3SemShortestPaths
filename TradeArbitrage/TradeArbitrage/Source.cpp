#include <iostream>
#include <vector>
#include <limits>
#include <math.h> 

using std::vector;
using std::cout;
using std::cin;

class CVertex
{
public:
	//properties
	vector<CVertex*>& Children()
	{
		return children;
	}

	vector<double>& ChildrenCost()
	{
		return childrenCost;
	}

	double& Distance()
	{
		return distance;
	}

	CVertex()
	{
		distance = std::numeric_limits<double>::infinity();
	}

private:

	vector<CVertex*> children;
	vector<double> childrenCost;
	double distance;

};

bool BFAlgorythm(vector<CVertex*>& Graph, int N)
{
	bool relaxed;

	(*Graph.begin())->Distance() = 0;

	vector<double>::iterator itChildrenCost;

	for (int k = 0; k < N - 1; ++k)
	{
		relaxed = false;

		for (auto it = Graph.begin(); it != Graph.end(); ++it)
		{
			itChildrenCost = (*it)->ChildrenCost().begin();

			for (auto itChildren = (*it)->Children().begin(); itChildren != (*it)->Children().end(); ++itChildren)
			{
				if ((*itChildren)->Distance() >(*it)->Distance() + *itChildrenCost)
				{
					(*itChildren)->Distance() = (*it)->Distance() + *itChildrenCost;
					relaxed = true;
				}
				++itChildrenCost;
			}
		}

		if (!relaxed)
			break;
	}

	for (auto it = Graph.begin(); it != Graph.end(); ++it)
	{
		itChildrenCost = (*it)->ChildrenCost().begin();

		for (auto itChildren = (*it)->Children().begin(); itChildren != (*it)->Children().end(); ++itChildren)
		{
			if ((*itChildren)->Distance() > (*it)->Distance() + *itChildrenCost)
				return true; //negative cycle
			++itChildrenCost;
		}
	}
	//no negative cycle
	return false;
}

int main()
{
	int N;
	cin >> N;

	vector<CVertex*> Graph;

	for (int i = 0; i < N; ++i)
		Graph.push_back(new CVertex());

	int k = 0;
	double cost;

	for (auto it = Graph.begin(); it != Graph.end(); ++it)
	{
		for (int i = 0; i < N; ++i)
		{
			if (i != k)
			{
				cin >> cost;
				if (cost != -1)
				{
					(*it)->Children().push_back(Graph.at(i));
					(*it)->ChildrenCost().push_back(-log(cost));
				}
			}
		}
		++k;
	}

	if (BFAlgorythm(Graph, N))
		cout << "YES" << std::endl;
	else
		cout << "NO" << std::endl;

	for (auto it = Graph.begin(); it != Graph.end(); ++it)
		delete *it;

	return 0;
}