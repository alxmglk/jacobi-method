#include "SIMDExtensionsChecker.h"

bool SIMDExtensionsChecker::IsSSESupported()
{
	int r[4];
	__cpuid(r, 1);

	return r[2] & (1 << 19);
}

bool SIMDExtensionsChecker::IsAVXSupported()
{
	int r[4];
	bool res = true;

	__cpuid(r, 1);

	if (((r[2] >> 27) & 7) == 7)
	{
		__asm
		{
			mov ECX, 0
				xgetbv
				and eax, 7
				cmp eax, 7
				jc mm
				mov res, 0
		}
	mm:return res != 0;
	}

	return false;
}

void SIMDExtensionsChecker::PrintSupportedExtensions()
{
	printf("Supported SIMD Extensions:\n");
	printf("SSE: %s\n", IsSSESupported() ? "true" : "false");
	printf("AVX: %s\n", IsAVXSupported() ? "true" : "false");
}