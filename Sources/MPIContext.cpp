#include "MPIContext.h"

MPIContext::MPIContext(int* argc, char*** argv)
{
	MPI_Init(argc, argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcessRank);
	MPI_Comm_size(MPI_COMM_WORLD, &NumberOfProcesses);
	MasterProcessRank = 0;
}

MPIContext::~MPIContext()
{
	MPI_Finalize();
}

bool MPIContext::IsMaster()
{
	return ProcessRank == MasterProcessRank;
}