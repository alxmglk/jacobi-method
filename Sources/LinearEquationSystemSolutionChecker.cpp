#include "LinearEquationSystemSolutionChecker.h"

bool LinearEquationSystemSolutionChecker::IsCorrectSolution(LinearEquationSystem* system, NUMBER* solution)
{
	NUMBER precision = 0.001f;
	bool correct = true;

	for (int i = 0; i < system->N; ++i)
	{
		if (ABS(solution[i] - i) > precision)
		{
			correct = false;
			break;
		}
	}
	
	return correct;
}