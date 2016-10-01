//Автор: Литвинцева Дарья
//Описание: задание 1, задача 3 на алгоритм Флойда-Уоршелла

#include <iostream>
#include <fstream>

using std::fstream;

void Floyd( int N, int** matrix ) //Floyd algrythm
{
	for( int i = 0; i < N; ++i)
	{
		for( int j = 0; j < N; ++j )
		{
			for( int k = 0; k < N; ++k ) matrix[j][k] = std::min(matrix[j][k], matrix[j][i] + matrix[i][k]);
		}
	}
}

int main()
{
	fstream input( "floyd.in", fstream::in );
	fstream output( "floyd.out", fstream::out );

	//reading
	int N;
	input>>N;

	int** matrix = new int*[N];

	for (int i = 0; i < N; ++i) 
	{
		matrix[i] = new int[N];
		for (int j = 0; j < N; ++j)	input >> matrix[i][j];
	}

	Floyd( N, matrix );
	//printing the result
	for (int i = 0; i < N; ++i) 
	{
		for (int j = 0; j < N; ++j)	output << matrix[i][j]<<" ";
		output << std::endl;
	}

	return 0;
}