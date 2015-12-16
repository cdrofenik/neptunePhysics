#ifndef NEPTUNE_NPVECTOR2_H
#define NEPTUNE_NPVECTOR2_H

#include <math.h>

#include "npPrecision.hpp"

namespace NeptunePhysics {

	template <typename T>
	class npVector2 {
	public:
		T x, y;
		npVector2() : x(0), y(0) {}
		npVector2(T xx, T yy) : x(xx), y(yy) {}
	};

	typedef npVector2<float> npVector2f;
	typedef npVector2<int> npVector2i;
	
}

#endif // NEPTUNE_NPVECTOR2_H