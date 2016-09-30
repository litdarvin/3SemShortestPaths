//Автор: Литвинцева Дарья
//Описание: игра в восьминашки, на bfs
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
using std::string;

class CVertex
{
public:
	CVertex( char wayToMe_, int chain_, int zeroPosition_ )
	{
		wayToMe = wayToMe_;
		Chain = chain_;
		zeroPosition = zeroPosition_;
	}
	
	vector<shared_ptr<CVertex>> Children;
	weak_ptr<CVertex> Parent;
	int Chain;
	char GetWay() const { return wayToMe;  }

	bool isItFinish() const
	{
		if( Chain == 123456780 ) return true;

		return false;
	}

	void CreateChildren(set<int>& Set)
	{
		int newChain;
		
		if( zeroPosition + 3 <= 8 && wayToMe != 'U' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition - 3 ))* ReturnByIndex( zeroPosition + 3 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'D', newChain, zeroPosition + 3 ) ) );
				Set.insert( newChain );
			}

		}
		if( zeroPosition - 3 >= 0 && wayToMe != 'D' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition + 3 ))* ReturnByIndex( zeroPosition - 3 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'U', newChain, zeroPosition - 3 ) ) );
				Set.insert( newChain );
			}
		}
		if (zeroPosition != 2 && zeroPosition != 5 && zeroPosition != 8 && wayToMe != 'L' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition - 1 ))* ReturnByIndex( zeroPosition + 1 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'R', newChain, zeroPosition + 1 ) ) );
				Set.insert( newChain );
			}
		}
		if (zeroPosition != 0 && zeroPosition != 3 && zeroPosition != 6 && wayToMe != 'R' ) {
			newChain = Chain + (powTen( 8 - zeroPosition ) - powTen( 8 - zeroPosition + 1 ))* ReturnByIndex( zeroPosition - 1 );
			if (Set.find( newChain ) == Set.end())
			{
				Children.push_back( shared_ptr<CVertex>( new CVertex( 'L', newChain, zeroPosition - 1 ) ) );
				Set.insert( newChain );
			}
		}
	}

	friend bool operator ==( const CVertex& v1, const CVertex& v2)
	{
		return v1.Chain == v2.Chain;
	}

private:
	char wayToMe;	
	int zeroPosition;

	static int powTen( int n )
	{
		static int pow10[10] = {
			1, 10, 100, 1000, 10000,
			100000, 1000000, 10000000, 100000000, 1000000000
		};

		return pow10[n];
	}

	int ReturnByIndex( int ind ) { return (Chain % powTen( 9 - ind ) - Chain % powTen( 8 - ind ))/ powTen( 8 - ind ); }
};

void bfs( shared_ptr<CVertex> graph, fstream& output )
{
	queue<shared_ptr<CVertex>> Queue;
	set<int> Set;
	weak_ptr<CVertex> result;
	Set.insert( graph->Chain );
	Queue.push( graph );
	bool stop = false;

	while( !stop )
	{
		shared_ptr<CVertex> current = Queue.front();
		Queue.pop();
		current->CreateChildren(Set);
		
		for( auto it = current->Children.begin(); it != current->Children.end(); ++it )
		{
			(*it)->Parent = current;
			
			if( !(*it)->isItFinish()) {
				Queue.push( *it );
			} else {
				result = *it;
				stop = true;
				break;
			}
		}
	}

	std::string resultString = "";
	int resultCount = 0;

	while( result.lock()->GetWay() != '\0' ) {

		resultString += result.lock()->GetWay();
		result = result.lock()->Parent;
		++resultCount;
	}

	output << resultCount<<std::endl;
	reverse( resultString.begin(), resultString.end() );
	output << resultString;
}

bool CheckPossibility( int numbers[])
{
	int sum = 0;
	for( int i = 0; i < 9; ++i )
	{
		if( numbers[i] != 0 ) {
			for (int j = i + 1; j < 9; ++j)
			{
				if( numbers[j] < numbers[i] && numbers[j] != 0 ) ++sum;
			}
		}
	}

	if( sum % 2 == 0 ) return true;

	return false;
}

int main()
{
	fstream input( "puzzle.txt", fstream::in );
	fstream output( "puzzle1.txt", fstream::out );

	int chain = 0;
	int sum = 0;
	int zeroPosition = -1;
	int current;
	int numbers[9];

	for( int i = 0; i < 9; ++i )
	{
		input >> current;
		numbers[i] = current;
		if (current == 0) zeroPosition = i;
		chain = 10 * chain + current;
	}

	if( chain == 123456780 ) output << 0;

	if( CheckPossibility( numbers ) )	{
		shared_ptr<CVertex> graph( new CVertex( '\0', chain, zeroPosition ) );
		bfs( graph, output );
	}
	else output << -1;

	output.close();
	input.close();

	return 0;
}