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

const short N = 16;

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

	bool wayToMeU;
	bool wayToMeD;
	bool wayToMeR;
	bool wayToMeL;

	void CreateChildren( set<CVertex*>& graph );//creates children for the vertex

	friend bool operator < ( CVertex& A, CVertex&B ) { return A.DistanceF > B.DistanceF; }

private:
	short zeroPosition;
};
