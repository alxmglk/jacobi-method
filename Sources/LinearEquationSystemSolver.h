#pragma once
#include "Common.h"
#include "LinearEquationSystem.h"
#include <math.h>
#include <intrin.h>
#include <float.h>
#include <windows.h>
#include <stdio.h>
#include "MPIContext.h"
#include "MPICommunicator.h"

class LinearEquationSystemSolver
{
	MPIContext& context;
	MPICommunicator& communicator;

public:
	LinearEquationSystemSolver(MPIContext& mpiContext, MPICommunicator& mpiCommunicator);
	void Solve(LinearEquationSystem* system, NUMBER* solution);
};