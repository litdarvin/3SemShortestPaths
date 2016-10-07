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
using std::queue;
using std::set;
using std::shared_ptr;
using std::weak_ptr;
using std::fstream;

class CVertex {
public:
	CVertex( char wayToMe_, int chain_, int zeroPosition_ );

	vector<shared_ptr<CVertex>> Children;
	weak_ptr<CVertex> Parent;
	int Chain;//condition

	char GetWay() const;

	bool IsItFinish() const;

	void CreateChildren( set<int>& Set );//creates children for the vertex

private:
	char wayToMe;
	int zeroPosition;

	int returnByIndex( int ind );
};

void bfs( shared_ptr<CVertex> graph, fstream& output );
