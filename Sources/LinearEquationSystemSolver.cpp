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
		solution[i] = 1;
	}

	double norm;

	do 
	{
		#pragma omp parallel for if (rowsCount > 128)
		for (int row = 0; row < rowsCount; row++) 
		{
			NUMBER freeTerm = matrix[row][freeTermIndex];
			
			newSolution[row] = freeTerm;

			for (int column = 0; column < n; column++)
			{
				if (row == column)
				{
					continue;
				}

				newSolution[row] -= matrix[row][column] * solution[column];				
			}

			newSolution[row] /= matrix[row][row];
		}

		norm = ABS(solution[0] - newSolution[0]);

		for (int column = 0; column < n; column++) 
		{
			NUMBER difference = ABS(solution[column] - newSolution[column]);

			if (difference > norm)
			{
				norm = difference;
			}

			solution[column] = newSolution[column];
		}
	} 
	while (norm > accuracy);

	delete []newSolution;
}