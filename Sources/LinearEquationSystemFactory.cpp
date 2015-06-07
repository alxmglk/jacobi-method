#include "LinearEquationSystemFactory.h"

LinearEquationSystemFactory::LinearEquationSystemFactory(MPIContext& mpiContext, MPICommunicator& mpiCommunicator)
	: context(mpiContext), communicator(mpiCommunicator)
{

}

bool LinearEquationSystemFactory::IsDiagonallyDominant(LinearEquationSystem* s)
{
	bool result = true;
	for (int i = 0; i < s->N; ++i)
	{
		NUMBER value = ABS(s->AugmentedMatrix[i][i]);

		for (int j = 0; j < s->N; ++j)
		{
			if (i == j)
			{
				continue;
			}

			value -= s->AugmentedMatrix[i][j];
		}

		if (value < 0)
		{
			result = false;
			break;
		}
	}

	return result;
}

NUMBER LinearEquationSystemFactory::GetRandomCoefficient()
{
	const int maxValue = 3;
	const NUMBER divider = 1.33f;

	return (rand() % maxValue) / divider + divider;
}

LinearEquationSystem* LinearEquationSystemFactory::Create(int n)
{
	int rowsPerProcess = n / context.NumberOfProcesses;
	LinearEquationSystem* system = new LinearEquationSystem(n);;
	LinearEquationSystem* partialSystem = new LinearEquationSystem(n, rowsPerProcess);

	if (context.IsMaster())
	{
		Fill(system);
	}

	communicator.Scatter(system->AugmentedMatrix[0], rowsPerProcess, partialSystem->AugmentedMatrix[0], partialSystem->RowType->Type);

	delete system;

	return partialSystem;
}

void LinearEquationSystemFactory::Fill(LinearEquationSystem* system)
{
	NUMBER** matrix = system->AugmentedMatrix;

	srand(time(nullptr));

	for (int row = 0; row < system->RowsCount; ++row)
	{
		NUMBER freeTerm = 0;

		int column = 0;
		for (; column < system->ColumnsCount - 1; ++column)
		{
			if (column != row)
			{
				NUMBER value = GetRandomCoefficient();

				matrix[row][column] = value;
				freeTerm += value * column;
			}
		}

		NUMBER value = freeTerm + GetRandomCoefficient();
		freeTerm += value * row;

		matrix[row][row] = value;
		matrix[row][column] = freeTerm;
	}
}