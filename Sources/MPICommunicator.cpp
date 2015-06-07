#include "MPICommunicator.h"

MPICommunicator::MPICommunicator(MPIContext& mpiContext, MPI_Comm communicatorId)	
	: context(mpiContext)
{	
	id = communicatorId;
}

void MPICommunicator::Barrier()
{
	MPI_Barrier(id);
}

void MPICommunicator::Scatter(const void* sendBuffer, int sendCount, void* recvBuffer, MPI_Datatype sendType)
{
	MPI_Scatter(sendBuffer, sendCount, sendType, recvBuffer, sendCount, sendType, context.MasterProcessRank, id);
}

void MPICommunicator::Gather(const void* sendBuffer, int sendCount, void* recvBuffer, MPI_Datatype sendType)
{
	MPI_Gather(sendBuffer, sendCount, sendType, recvBuffer, sendCount, sendType, context.MasterProcessRank, id);
}

void MPICommunicator::Broadcast(void* buffer, int count, MPI_Datatype type, int root)
{
	MPI_Bcast(buffer, count, type, root, id);
}