#ifndef NEPTUNE_NPVECTOR3_H
#define NEPTUNE_NPVECTOR3_H

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

	class npVector3 {

	public:
		npReal x, y, z;
		npVector3() : x(0), y(0), z(0) {}
		npVector3(npReal xx, npReal yy, npReal zz) : x(xx), y(yy), z(zz) {}

		/*!
		Returns square length value without the sqrt
		*/
		npReal squareLength();

		/*!
		Returns the length of this vector.
		*/
		npReal length() const;

		/*!
		Inverts the vector values.
		*/
		void invert();

		/*!
		Normalizes the vector = vector / length
		*/
		void normalize();

		/*!
		\param vector a referenced Vector3.
		\param scale a scale with a real value.
		*/
		void addScaledVector(const npVector3& v, const npReal& scale);

		/*!
		\param vector a referenced Vector3.
		*/
		void componentProductUpdate(const npVector3& v);

		/*!
		Angle between two vectors in degrees
		*/
		npReal angle(const npVector3& v);

		void operator+=(const npVector3& v);

		void operator-=(const npVector3& v);

		void operator*=(const npReal& v);

		void operator%=(const npVector3& v);

		npVector3& operator+(const npVector3& v) const;

		npVector3& operator-(const npVector3& v) const;

		npVector3& operator*(const npReal& v) const;

		npReal operator*(npVector3& v) const;

		npVector3& operator%(const npVector3& vector) const;

	};
}

#endif // NEPTUNE_NPVECTOR3_H