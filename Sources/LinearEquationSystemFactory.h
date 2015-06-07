#pragma once
#include "Common.h"
#include "LinearEquationSystem.h"
#include <time.h>
#include <windows.h>
#include "MPIContext.h"
#include "MPICommunicator.h"

class LinearEquationSystemFactory
{
	MPIContext& context;
	MPICommunicator& communicator;

	bool IsDiagonallyDominant(LinearEquationSystem* s);
	NUMBER GetRandomCoefficient();
	void Fill(LinearEquationSystem* system);

public:
	LinearEquationSystemFactory(MPIContext& mpiContext, MPICommunicator& mpiCommunicator);	

    LinearEquationSystem* Create(int n);
};