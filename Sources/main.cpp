#include <stdio.h>
#include <windows.h>
#include <float.h>
#include "mpi.h"

#include "Stopwatch.h"
#include "LinearEquationSystemSolver.h"
#include "LinearEquationSystemSolutionChecker.h"
#include "LinearEquationSystemFactory.h"
#include "MPIContext.h"
#include "MPICommunicator.h"

Stopwatch stopwatch;
LinearEquationSystemSolutionChecker checker;

int n = 32;
const int nLimit = 4096 * 2;
const int multiplier = 2;
const int repeatsNumber = 3;

int main(int argc, char* argv[])
{
	MPIContext context(&argc, &argv);
	MPICommunicator communicator(context, MPI_COMM_WORLD);
	LinearEquationSystemFactory factory(context, communicator);
	LinearEquationSystemSolver solver(context, communicator);

	for (; n <= nLimit; n *= multiplier)
	{
		float minTime = FLT_MAX;
		for (int attempt = 0; attempt < repeatsNumber; ++attempt)
		{
			LinearEquationSystem* system = factory.Create(n);
			NUMBER* solution = (NUMBER*)_aligned_malloc(n * sizeof(NUMBER), 16);

			stopwatch.Start();
			solver.Solve(system, solution);
			stopwatch.Stop();

			float elapsedSeconds = stopwatch.GetElapsedSeconds();
			if (elapsedSeconds < minTime)
			{
				minTime = elapsedSeconds;
			}

			communicator.Barrier();

			/*bool result = checker.IsCorrectSolution(system, solution);
			printf("Correct: %s \n", result ? "yes" : "no");*/

			delete system;
			_aligned_free(solution);
		}

		if (context.IsMaster())
		{
			printf("N = %d, Elapsed seconds: %f\n", n, minTime);
		}
	}
}