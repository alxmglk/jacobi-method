#pragma once
#include "Common.h"
#include "intrin.h"
#include <stdio.h>
#include <memory.h>
#include "MPIRowType.h"

class LinearEquationSystem
{
public:
	MPIRowType* RowType;
	NUMBER** AugmentedMatrix;
	int N;
	int RowsCount;
	int ColumnsCount;
	int FreeTermIndex;
	
	LinearEquationSystem(int n);
	LinearEquationSystem(int n, int rowsCount);
	~LinearEquationSystem();

	void Print();
};