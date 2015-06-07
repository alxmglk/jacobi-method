#include "MPIRowType.h"

MPIRowType::MPIRowType(int n)
{
	int elementsCount = n + 1;
	int buffer = (elementsCount % K == 0) ? 0 : (K - elementsCount % K);

	ElementsCount = elementsCount + buffer;
	Size = ElementsCount * sizeof(NUMBER);

	MPI_Type_contiguous(ElementsCount, MPI_NUMBER, &Type);
	MPI_Type_commit(&Type);
}

MPIRowType::~MPIRowType()
{
	MPI_Type_free(&Type);
}