#ifndef NEPTUNE_NPPRECISION_H
#define NEPTUNE_NPPRECISION_H

namespace NeptunePhysics {
	/*
		Defines a real number precision. Neptune Physics support single- and double- precision versions.
		The default one is single-precision.
	*/
#define PI 3.14159265

#if DOUBLE_PRECISION
	typedef double npReal;
#else
	typedef float npReal;
#endif
}


#endif