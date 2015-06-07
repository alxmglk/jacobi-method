#include <stdio.h>
#include <windows.h>
#include <float.h>
#include "mpi.h"

#include "Stopwatch.h"
#include "LinearEquationSystemSolver.h"
#include "LinearEquationSystemSolutionChecker.h"
#include "LinearEquationSystemFactory.h"

Stopwatch stopwatch;
LinearEquationSystemSolutionChecker checker;

int n = 32;
const int nLimit = 4096 * 2;
const int multiplier = 2;
const int repeatsNumber = 1;

int main(int argc, char* argv[])
{
	LinearEquationSystemFactory factory;
	LinearEquationSystemSolver solver;

	for (; n <= nLimit; n *= multiplier)
	{
		float minTime = FLT_MAX;
		for (int attempt = 0; attempt < repeatsNumber; ++attempt)
		{
			LinearEquationSystem* system = factory.Create(n);
			NUMBER* solution = new NUMBER[n];

			stopwatch.Start();			
			solver.Solve(system, solution);
			stopwatch.Stop();

			float elapsedSeconds = stopwatch.GetElapsedSeconds();
			if (elapsedSeconds < minTime)
			{
				minTime = elapsedSeconds;
			}

			bool result = checker.IsCorrectSolution(system, solution);
			printf("Correct: %s \n", result ? "yes" : "no");

			delete system;
			delete []solution;
		}

		printf("N = %d, Elapsed seconds: %f\n", n, minTime);
	}
}