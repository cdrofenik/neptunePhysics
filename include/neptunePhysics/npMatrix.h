#ifndef NEPTUNE_NPMATRIX_H
#define NEPTUNE_NPMATRIX_H

#include <math.h>

#include "npPrecision.h"

#ifdef NO_NeptunePhysics_DLL
#define NEPTUNE_PHYSICS_API
#else
#ifdef NEPTUNE_PHYSICS_EXPORT
#define NEPTUNE_PHYSICS_API __declspec(dllexport)
#else
#define NEPTUNE_PHYSICS_API __declspec(dllimport)
#endif
#endif

namespace NeptunePhysics {

	class npMatrix3 {

	public:
		npReal m[3][3];

		npMatrix3();
		npMatrix3(npReal v);
		npMatrix3(const npReal& a00, const npReal& a01, const npReal& a02,
			const npReal& a10, const npReal& a11, const npReal& a12,
			const npReal& a20, const npReal& a21, const npReal& a22);

		npMatrix3& operator*(const npReal& v) const;
		npMatrix3& operator*(const npMatrix3& v) const;
		npMatrix3& operator+(const npMatrix3& v) const;
		
		void init(npReal v);
	};


	class npMatrix4 {

	public:
		npReal m[4][4];

		npMatrix4();
		npMatrix4(npReal v);
		npMatrix4(npMatrix3 v);

		npMatrix4 operator*(const npMatrix4& v) const;

		void init(npReal v);
	};
}

#endif