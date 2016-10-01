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


class CVertex
{
public:
	CVertex( char wayToMe_, int chain_, int zeroPosition_ );
	
	vector<shared_ptr<CVertex>> Children;
	weak_ptr<CVertex> Parent;
	int Chain;//condition
	char GetWay() const;

	bool isItFinish() const;

	void CreateChildren(set<int>& Set);//creates children for the vertex


private:
	char wayToMe;	
	int zeroPosition;
	//fast 10^(0...9)
	static int powTen( int n )
	{
		static int pow10[10] = {
			1, 10, 100, 1000, 10000,
			100000, 1000000, 10000000, 100000000, 1000000000
		};

		return pow10[n];
	}

	int ReturnByIndex( int ind );
};

void bfs( shared_ptr<CVertex> graph, fstream& output );
