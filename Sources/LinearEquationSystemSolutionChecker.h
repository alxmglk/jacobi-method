#pragma once
#include <math.h>
#include "Common.h"
#include "LinearEquationSystem.h"

class LinearEquationSystemSolutionChecker
{
public:
	bool IsCorrectSolution(LinearEquationSystem* system, NUMBER* solution);
};