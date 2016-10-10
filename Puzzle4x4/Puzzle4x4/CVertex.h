#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm>
#include <array>

using std::vector;
using std::array;
using std::queue;
using std::set;
using std::shared_ptr;
using std::weak_ptr;
using std::fstream;

//const short N = 16;
const int N = 16;
const int n = 4;
class CVertex
{
public:
	CVertex( array<short, N>& chain_, short zeroPosition_ );
	vector<shared_ptr<CVertex>> Children;
	CVertex* Parent;
	array<short, N> Chain;//condition

	bool isItFinish() const;

	int DistanceF;
	int DistanceG;
	char ShortestWayToMe;
	char lastWayToMe;
	short zeroPosition;
	int H;
	void CreateChildren( set<shared_ptr<CVertex>>& graph );//creates children for the vertex

private:

	bool wayToMeU;
	bool wayToMeD;
	bool wayToMeR;
	bool wayToMeL;

	void pushInGraph( array<short, N>& newChain, short zeroPosition, set<shared_ptr<CVertex>>& graph, char lastWayToMe_ );
};
