#include <vector>
using std::vector;

struct CVertex {

	CVertex();
	vector<CVertex*> Children;
	vector<double> ChildrenCost;
	double Distance;
};

bool isNegativeCycleBFAlgorythm( vector<CVertex*>& graph, int numberCurrency );