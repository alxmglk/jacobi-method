#include "LinearEquationSystemSolver.h"

LinearEquationSystemSolver::LinearEquationSystemSolver(MPIContext& mpiContext, MPICommunicator& mpiCommunicator)
	: context(mpiContext), communicator(mpiCommunicator)
{
}

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

	int packedElementsCount = system->RowType->ElementsCount / K;
	NUMBER maxDivergence;
	int solutionSize = n * sizeof(NUMBER);

	do
	{
		maxDivergence = -FLT_MAX;

		for (int row = 0; row < rowsCount; row++)
		{
			PARRAY pSum = SET1(0);
			PARRAY* pRow = (PARRAY*)matrix[row];
			PARRAY* pSolution = (PARRAY*)solution;

			for (int k = 0; k < packedElementsCount; k++)
			{
				pSum = ADD(pSum, MUL(pRow[k], pSolution[k]));
			}

			NUMBER* sumArray = (NUMBER*)&pSum;
			
			NUMBER sum = 0;
			for (int i = 0; i < K; ++i)
			{
				sum += sumArray[i];
			}

			sum -= matrix[row][row] * solution[row];

			newSolution[row] = (matrix[row][freeTermIndex] - sum) / matrix[row][row];

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