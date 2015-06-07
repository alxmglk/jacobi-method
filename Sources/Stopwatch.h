#pragma once
#include <stdio.h>
#include <windows.h>

class Stopwatch
{
	LARGE_INTEGER li1, li2;
	LARGE_INTEGER frequency;

public:
	Stopwatch();
	void Start();
	void Stop();
	float GetElapsedSeconds();
	void ShowElapsedTime();
};