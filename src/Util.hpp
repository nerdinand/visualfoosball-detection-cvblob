#ifndef SRC_UTIL_HPP_
#define SRC_UTIL_HPP_


long clamp(long value, long min, long max) {
	value = value < min ? min : value;
	value = value > max ? max : value;

	return value;
}


#endif /* SRC_UTIL_HPP_ */
