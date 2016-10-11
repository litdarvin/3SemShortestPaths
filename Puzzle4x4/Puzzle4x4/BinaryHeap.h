#include <iostream>
#include <vector>

using std::vector;

class CBinaryHeap {
public:
	

	int increaseKey( int index );
	int decreaseKey( int index );
	int push( CVertex* v);
	CVertex* top();
	int size() { return heapSize; }

private:
	int heapSize;
	vector<CVertex*> elements;
};
