//Автор: Литвинцева Дарья
//Описание: игра в восьминашки, на bfs
#include <iostream>
#include <memory>
#include <math.h>
#include <fstream>

using std::shared_ptr;
using std::fstream;

#include "CVertex.h"


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
	//reading for checking and for graph
	for( int i = 0; i < 9; ++i )
	{
		input >> current;
		numbers[i] = current;
		if (current == 0) zeroPosition = i;
		chain = 10 * chain + current;
	}
	//if it's correct
	if( chain == 123456780 ) output << 0;
	//if possible
	if( CheckPossibility( numbers ) )	{
		shared_ptr<CVertex> graph( new CVertex( '\0', chain, zeroPosition ) );
		bfs( graph, output );
	}
	else output << -1;//if impossible

	output.close();
	input.close();

	return 0;
}