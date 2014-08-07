#ifndef NEPTUNE_PRECISION_H
#define NEPTUNE_PRECISION_H

#include <float.h>

namespace neptune
{
	//! Defines precision
	/*!
	Defines precision for the whole application (single/double floating point).
	*/
	typedef float real;

	//! Defines the precision of the power operator
	/*!
	Defines the precision of the power operator.
	*/
	//#define real_pow pow;

	//! Defines the precision of the square root operator.
	/*!
	Defines the precision of the square root operator.
	*/
	//#define real_sqrt sqrt;
}

#endif // NEPTUNE_PRECISION_H