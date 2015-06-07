#pragma once
#include "Common.h"
#include "LinearEquationSystem.h"
#include <time.h>
#include <windows.h>

class LinearEquationSystemFactory
{
public:
    LinearEquationSystem* Create(int n);
};