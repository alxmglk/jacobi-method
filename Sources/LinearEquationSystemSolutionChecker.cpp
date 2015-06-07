#include "LinearEquationSystemSolutionChecker.h"

bool LinearEquationSystemSolutionChecker::IsCorrectSolution(LinearEquationSystem* system, NUMBER* solution)
{
	NUMBER precision = 0.001f;
	bool correct = true;

	NUMBER** matrix = system->AugmentedMatrix;
	int freeTermColumn = system->ColumnsCount - 1;

	for (int row = 0; row < system->RowsCount; ++row)
	{
		NUMBER freeTerm = matrix[row][freeTermColumn];

		for (int column = 0; column < freeTermColumn; ++column)
		{
			freeTerm -= matrix[row][column] * solution[column];
		}

		if (ABS(freeTerm) > precision)
		{
 			correct = false;
			break;
		}
	}

	return correct;
}