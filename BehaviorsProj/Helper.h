#ifndef HELPER_H_
#define HELPER_H_

#define SCAN_SPAN  666
#define DEGREES 270


class Helper
{

public:
	static const float MINIMUM_WALL_RANGE = 0.8;
	static const float TOTAL_SCAN_SPAN = SCAN_SPAN;
	static const float HALF_SCAN_SPAN = SCAN_SPAN / 2;
	static const float TOTAL_DEGREES = DEGREES;
	static const float DEGREES_INDEX_RATIO = SCAN_SPAN / DEGREES;

	static int IndexToDegrees(int index);
	static int DegreesToIndex(int degrees);

};

#endif
