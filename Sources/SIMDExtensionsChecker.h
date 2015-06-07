#pragma once
#include <intrin.h>
#include <stdio.h>

class SIMDExtensionsChecker
{
public:
	bool IsSSESupported();
	bool IsAVXSupported();

	void PrintSupportedExtensions();
};