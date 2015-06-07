#include "LinearEquationSystemFactory.h"

bool LinearEquationSystemFactory::IsDiagonallyDominant(LinearEquationSystem* s)
{
	bool result = true;
	for (int i = 0; i < s->N; ++i)
	{
		NUMBER value = ABS(s->AugmentedMatrix[i][i]);

		for (int j = 0; j < s->N; ++j)
		{
			if (i == j)
			{
				continue;
			}

			value -= s->AugmentedMatrix[i][j];
		}

		if (value < 0)
		{
			result = false;
			break;
		}
	}

	return result;
}

NUMBER LinearEquationSystemFactory::GetRandomCoefficient()
{
	const int maxValue = 3;
	const NUMBER divider = 1.33f;

	return (rand() % maxValue) / divider + divider;
}

LinearEquationSystem* LinearEquationSystemFactory::Create(int n)
{
	LinearEquationSystem* system = new LinearEquationSystem(n);
		
	NUMBER** matrix = system->AugmentedMatrix;

	srand(time(nullptr));

	for (int row = 0; row < system->RowsCount; ++row)
	{
		NUMBER freeTerm = 0;
		NUMBER sum = 0;

		int column = 0;
		for (; column < system->ColumnsCount - 1; ++column)
		{
			NUMBER value = GetRandomCoefficient();

			if (column != row)
			{
				sum += value;
				matrix[row][column] = value;
				freeTerm += value * column;
			}
		}

		NUMBER value = sum + GetRandomCoefficient();
		matrix[row][row] = value;
		freeTerm += value * row;

		matrix[row][column] = freeTerm;
	}
		
	return system;
}