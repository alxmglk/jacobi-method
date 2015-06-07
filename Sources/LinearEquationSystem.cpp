#include "LinearEquationSystem.h"
#include <stdio.h>
#include <memory.h>

LinearEquationSystem::LinearEquationSystem(int n) : LinearEquationSystem(n, n)
{
}

LinearEquationSystem::LinearEquationSystem(int n, int rowsCount)
{
	N = n;
	RowsCount = rowsCount;
	ColumnsCount = n + 1;
	FreeTermIndex = n;

	AugmentedMatrix = (NUMBER**)malloc(RowsCount * sizeof(NUMBER*));

	int buffer = (ColumnsCount % K == 0) ? 0 : (K - ColumnsCount % K);
	ColumnsCountWithBuffer = ColumnsCount + buffer;

	for (int row = 0; row < RowsCount; ++row)
	{
		AugmentedMatrix[row] = (NUMBER*)_aligned_malloc(ColumnsCountWithBuffer * sizeof(NUMBER), 16);

		memset(AugmentedMatrix[row], 0, ColumnsCountWithBuffer * sizeof(NUMBER));
	}
}

LinearEquationSystem::~LinearEquationSystem()
{
	for (int row = 0; row < RowsCount; ++row)
	{
		_aligned_free(AugmentedMatrix[row]);
	}	

	free(AugmentedMatrix);
}

void LinearEquationSystem::Print()
{
	printf("Matrix: \n");

	for (int i = 0; i < RowsCount; ++i)
	{
		for (int j = 0; j < ColumnsCount; ++j)
		{
			printf("%f ", AugmentedMatrix[i][j]);
		}

		printf("\n");
	}
}