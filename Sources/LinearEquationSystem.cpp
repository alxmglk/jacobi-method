#include "LinearEquationSystem.h"

LinearEquationSystem::LinearEquationSystem(int n) : LinearEquationSystem(n, n)
{
}

LinearEquationSystem::LinearEquationSystem(int n, int rowsCount)
{
	RowType = new MPIRowType(n);
	N = n;
	RowsCount = rowsCount;
	ColumnsCount = n + 1;
	FreeTermIndex = n;

	NUMBER* data = (NUMBER*)_aligned_malloc(RowsCount * RowType->Size, 16);
	AugmentedMatrix = (NUMBER**)malloc(RowsCount * sizeof(NUMBER*));

	for (int row = 0; row < RowsCount; ++row)
	{
		AugmentedMatrix[row] = &(data[row * RowType->ElementsCount]);

		memset(AugmentedMatrix[row], 0, RowType->Size);
	}
}

LinearEquationSystem::~LinearEquationSystem()
{
	_aligned_free(AugmentedMatrix[0]);
	free(AugmentedMatrix);
	delete RowType;
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