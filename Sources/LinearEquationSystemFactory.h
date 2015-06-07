#pragma once
#include "Common.h"
#include "LinearEquationSystem.h"
#include <time.h>
#include <windows.h>

class LinearEquationSystemFactory
{
private:
	bool IsDiagonallyDominant(LinearEquationSystem* s);
	NUMBER GetRandomCoefficient();

public:
    LinearEquationSystem* Create(int n);
};