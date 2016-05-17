#ifndef NEPTUNE_NPVECTOR3_H
#define NEPTUNE_NPVECTOR3_H

#include <math.h>

#include "npPrecision.hpp"

namespace NeptunePhysics {

	class npVector3 {

	public:
		npReal x, y, z;
		npVector3() : x(0), y(0), z(0) {}
		npVector3(const npReal xx, const  npReal yy, const  npReal zz) : x(xx), y(yy), z(zz) {}

		/*!
		Returns square length value without the sqrt
		*/
		npReal squareLength() {
			return (x * x) + (y * y) + (z * z);
		}

		/*!
		Returns the length of this vector.
		*/
		npReal length() const {
			return sqrt((x * x) + (y * y) + (z * z));
		}

		/*!
		Inverts the vector values.
		*/
		void invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		/*!
		Normalizes the vector = vector / length
		*/
		npVector3& normalize() {
			const float l = sqrt(x * x + y * y + z * z);

			x /= l;
			y /= l;
			z /= l;

			return *this;
		}

		/*!
		\param vector a referenced Vector3.
		\param scale a scale with a real value.
		*/
		void addScaledVector(const npVector3& v, const npReal& scale) {
			x += v.x * scale;
			y += v.y * scale;
			z += v.z * scale;
		}

		/*!
		\param vector a referenced Vector3.
		*/
		void componentProductUpdate(const npVector3& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
		}

		/*!
		Angle between two vectors in degrees
		*/
		npReal angle(const npVector3& v) {
			auto top = (x * v.x) + (y * v.y) + (z * v.z);
			auto bottom = this->length() * v.length();
			return (npReal)(acos(top / bottom) * (180 / NP_PI));
		}

		void operator+=(const npVector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator-=(const npVector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(const npReal& v) {
			x *= v;
			y *= v;
			z *= v;
		}

		void operator%=(const npVector3& v) {
			npVector3 r(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
			(*this) = r;
		}

		npVector3 operator+(const npVector3& v) const {
			return npVector3(x + v.x, y + v.y, z + v.z);
		}

		npVector3 operator-(const npVector3& v) const {
			return npVector3(x - v.x, y - v.y, z - v.z);
		}

		npVector3 operator*(const npReal& v) const {
			return npVector3(x * v, y * v, z * v);
		}

		npReal operator*(npVector3& v) const {
			return (x * v.x) + (y * v.y) + (z * v.z);
		}

		/*!
		Returns cross product between two vectors
		*/
		npVector3 operator%(const npVector3& v) const {
			return npVector3(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x);
		}

	};
}
#endif // NEPTUNE_NPVECTOR3_H