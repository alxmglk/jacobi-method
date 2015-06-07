#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
	QueryPerformanceFrequency(&frequency);
}

void Stopwatch::Start()
{
	QueryPerformanceCounter(&li1);
}

void Stopwatch::Stop()
{
	QueryPerformanceCounter(&li2);
}

float Stopwatch::GetElapsedSeconds()
{
	return (li2.QuadPart - li1.QuadPart) / (float)frequency.QuadPart;
}

void Stopwatch::ShowElapsedTime()
{
	float elapsedSeconds = this->GetElapsedSeconds();

	printf("Elapsed seconds: %f\n", elapsedSeconds);
}