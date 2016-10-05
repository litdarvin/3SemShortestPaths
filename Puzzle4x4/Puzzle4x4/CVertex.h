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
	CVertex( char wayToMe_, array<short, N>& chain_, short zeroPosition_ );

	set<shared_ptr<CVertex>> Children;
	weak_ptr<CVertex> Parent;
	array<short, N> Chain;//condition

	bool isItFinish() const;

	int DistanceF;
	int DistanceG;

	void CreateChildren();//creates children for the vertex

	friend bool operator < ( CVertex& A, CVertex&B ) { return A.DistanceF > B.DistanceF; }

private:
	char wayToMe;
	short zeroPosition;
};
