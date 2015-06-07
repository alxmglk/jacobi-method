#include "LinearEquationSystemSolver.h"

void LinearEquationSystemSolver::Solve(LinearEquationSystem* system, NUMBER* solution)
{
	double accuracy = 0.0000001;
	int n = system->N;
	NUMBER** matrix = system->AugmentedMatrix;
	int rowsCount = system->RowsCount;
	int freeTermIndex = system->FreeTermIndex;

	NUMBER* newSolution = new NUMBER[n];

	for (int i = 0; i < n; ++i)
	{
		solution[i] = 0;
	}

	NUMBER maxDivergence = 0;
	int solutionSize = n * sizeof(NUMBER);

	do
	{
		maxDivergence = -DBL_MAX;

		for (int row = 0; row < rowsCount; row++)
		{
			NUMBER x = matrix[row][freeTermIndex];

			for (int column = 0; column < n; column++)
			{
				if (row != column)
				{
					x -= matrix[row][column] * solution[column];
				}
			}

			x /= matrix[row][row];

			newSolution[row] = x;

			NUMBER divergence = ABS(solution[row] - newSolution[row]);
			if (divergence > maxDivergence)
			{
				maxDivergence = divergence;
			}
		}

		memcpy(solution, newSolution, solutionSize);
	} while (maxDivergence > accuracy);

	delete[]newSolution;
}