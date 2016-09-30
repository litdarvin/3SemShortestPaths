//Автор: Литвинцева Дарья
//Описание: игра в восьминашки, на bfs
#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <queue>
#include <string>

using std::vector;
using std::queue;
using std::shared_ptr;
using std::weak_ptr;
using std::cin;
using std::cout;

class CVertex
{
public:
	CVertex( char wayToMe_, int chain_, int zeroPosition_ )
	{
		wayToMe = wayToMe_;
		chain = chain_;
		zeroPosition = zeroPosition_;
	}
	
	vector<shared_ptr<CVertex>> Children;
	weak_ptr<CVertex> Parent;
	char GetWay() const { return wayToMe;  }

	bool isItFinish() const
	{
		if( chain == 123456780 )
			return true;
		return false;
	}

	void CreateChildren()
	{
		int newChain;

		if( zeroPosition + 3 <= 8 && wayToMe != 'U' ) {
			newChain = chain + ((int)pow( 10, 8 - zeroPosition ) - (int)pow( 10, 8 - zeroPosition - 3 ))* ReturnByIndex( zeroPosition + 3 );
			Children.push_back( shared_ptr<CVertex>( new CVertex( 'D', newChain, zeroPosition + 3 ) ) );

		}
		if( zeroPosition - 3 >= 0 && wayToMe != 'D' ) {
			newChain = chain + ((int)pow( 10, 8 - zeroPosition ) - (int)pow( 10, 8 - zeroPosition + 3 ))* ReturnByIndex( zeroPosition - 3 );
			Children.push_back( shared_ptr<CVertex>( new CVertex( 'U', newChain, zeroPosition - 3 ) ) );
		}
		if (zeroPosition != 2 && zeroPosition != 5 && zeroPosition != 8 && wayToMe != 'L' ) {
			newChain = chain + ((int)pow( 10, 8 - zeroPosition ) - (int)pow( 10, 8 - zeroPosition - 1 ))* ReturnByIndex( zeroPosition + 1 );
			Children.push_back( shared_ptr<CVertex>( new CVertex( 'R', newChain, zeroPosition + 1 ) ) );
		}
		if (zeroPosition != 0 && zeroPosition != 3 && zeroPosition != 6 && wayToMe != 'R' ) {
			newChain = chain + ((int)pow( 10, 8 - zeroPosition ) - (int)pow( 10, 8 - zeroPosition + 1 ))* ReturnByIndex( zeroPosition - 1 );
			Children.push_back( shared_ptr<CVertex>( new CVertex( 'L', newChain, zeroPosition - 1 ) ) );
		}
	}

private:
	int chain;
	char wayToMe;	
	int zeroPosition;

	int ReturnByIndex( int ind )
	{
		return (chain%(int)pow( 10, 9 - ind ) - chain % (int)pow( 10, 8 - ind ))/(int)pow( 10, 8 - ind );
	}
};

void bfs( shared_ptr<CVertex> graph )
{
	queue<shared_ptr<CVertex>> Queue;
	weak_ptr<CVertex> result;
	Queue.push( graph );
	bool stop = false;

	while( !stop )
	{
		shared_ptr<CVertex> current = Queue.front();
		Queue.pop();
		current->CreateChildren();

		for( auto it = current->Children.begin(); it != current->Children.end(); ++it )
		{
			(*it)->Parent = current;

			if( !(*it)->isItFinish() ) {
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

	cout << resultCount;
	std::reverse( resultString.begin(), resultString.end() );
	cout << resultString;
}

int main()
{
	int chain = 0;
	int zeroPosition = -1;

	int current;

	for (int i = 0; i < 9; ++i)
	{
		cin >> current;
		if( current == 0 ) zeroPosition = i;
		if( zeroPosition != 0 )	chain = (int)pow( 10, i )*chain + current;
		else chain = (int)pow( 10, i - 1 )*chain + current;
	}

	shared_ptr<CVertex> graph( new CVertex( '\0', chain, zeroPosition ) );
	bfs( graph );
	system( "pause" );
	return 0;
}