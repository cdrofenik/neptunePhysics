#ifndef NEPTUNE_NPPOINT_H
#define NEPTUNE_NPPOINT_H

#include <vector>

//! 
//!... 2D Point
//!
template<typename T>
class npPoint2
{
public:
	std::vector<T> pnts;
	npPoint2() : pnts(std::vector<T>()) {}
};

//! 
//!... 3D Point
//!
template<typename T>
class npPoint3
{
public:
	std::vector<T> pnts;
	npPoint3() : pnts(std::vector<T>()) {}
	npPoint3(T xx, T yy, T zz) {
		pnts.push_back(xx);
		pnts.push_back(yy);
		pnts.push_back(zz);
	}

	void normalize() {
		float magnitude = 0.0f;
		for (int i = 0; i < pnts.size(); i++)
			magnitude += pow(pnts[i], 2.0f);
		magnitude = sqrt(magnitude);
		for (int i = 0; i < pnts.size(); i++)
			pnts[i] /= magnitude;
	}
};

typedef npPoint3<float> npPoint3f;
typedef npPoint3<int> npPoint3i;
typedef npPoint2<float> npPoint2f;

#endif