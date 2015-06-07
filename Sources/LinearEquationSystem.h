#pragma once
#include "Common.h"
#include "intrin.h"

class LinearEquationSystem
{
public:
	NUMBER** AugmentedMatrix;
	int N;
	int RowsCount;
	int ColumnsCount;
	int FreeTermIndex;
	int ColumnsCountWithBuffer;

	LinearEquationSystem(int n);
	LinearEquationSystem(int n, int rowsCount);
	~LinearEquationSystem();

	void Print();
};