#include "Helper.h"

int Helper::DegreesToIndex(int degrees)
{
	int indexDifference = degrees * Helper::DEGREES_INDEX_RATIO;
	return Helper::HALF_SCAN_SPAN + indexDifference;
}

int Helper::IndexToDegrees(int index)
{
	int relativeIndex = index - Helper::HALF_SCAN_SPAN;
	return relativeIndex / Helper::DEGREES_INDEX_RATIO;
}
