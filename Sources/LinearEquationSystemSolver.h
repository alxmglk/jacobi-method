#pragma once
#include "Common.h"
#include "LinearEquationSystem.h"
#include <math.h>
#include <intrin.h>
#include <float.h>
#include <windows.h>
#include <stdio.h>

class LinearEquationSystemSolver
{
public:
	void Solve(LinearEquationSystem* system, NUMBER* solution);
};