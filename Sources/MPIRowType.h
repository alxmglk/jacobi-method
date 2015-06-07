#pragma once
#include "Common.h"
#include "mpi.h"

class MPIRowType
{
public:
	int ElementsCount;
	int Size;
	MPI_Datatype Type;

	MPIRowType(int n);
	~MPIRowType();
};