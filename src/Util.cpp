
#include "Util.hpp"

long Util::clamp(long value, long min, long max) {
	value = value < min ? min : value;
	value = value > max ? max : value;

	return value;
}

