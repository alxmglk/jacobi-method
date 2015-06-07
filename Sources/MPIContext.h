#pragma once
#include "mpi.h"

class MPIContext
{
public:
	int ProcessRank;
	int NumberOfProcesses;
	int MasterProcessRank;

	MPIContext(int* argc, char*** argv);
	~MPIContext();

	bool IsMaster();
};