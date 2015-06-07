#pragma once
#include "mpi.h"
#include "MPIContext.h"

class MPICommunicator
{
	MPI_Comm id;
	MPIContext& context;

public:
	MPICommunicator(MPIContext& mpiContext, MPI_Comm communicatorId);

	void Barrier();
	void Scatter(const void* sendBuffer, int sendCount, void* recvBuffer, MPI_Datatype sendType);
	void Gather(const void* sendBuffer, int sendCount, void* recvBuffer, MPI_Datatype sendType);
	void AllGather(const void* sendBuffer, int sendCount, void* recvBuffer, MPI_Datatype sendType);
	void Broadcast(void* buffer, int count, MPI_Datatype type, int root);
	void Reduce(const void* sendBuffer, void* recvBuffer, int count, MPI_Datatype type, MPI_Op operation, int root);
	void AllReduce(const void* sendBuffer, void* recvBuffer, int count, MPI_Datatype type, MPI_Op operation);
};