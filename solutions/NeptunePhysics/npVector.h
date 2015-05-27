#ifndef NEPTUNE_NPVECTOR3_H
#define NEPTUNE_NPVECTOR3_H

#include <math.h>

#include "npPrecision.h"

namespace neptunePhysics {

	class npVector3 {

	public:
		npReal x, y, z;
		npVector3() : x(0), y(0), z(0) {}
		npVector3(npReal xx, npReal yy, npReal zz) : x(xx), y(yy), z(zz) {}

		/*!
		Returns square magnitude value without the sqrt
		*/
		npReal squareLength() {
			return (x * x) + (y * y) + (z * z);
		}

		/*!
		Returns the magnitute/length of this vector.
		*/
		npReal length() {
			return sqrt((x * x) + (y * y) + (z * z));
		}

		/*!
		Inverts the vector values.
		*/
		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		/*!
		Normalizes the vector = vector / length(vector)
		*/
		void normalize() {
			npReal l = this->length();
			if (l > 0) {
				(*this) *= ((npReal)l) / l;
			}
		}

		/*!
		\param vector a referenced Vector3.
		\param scale a scale with a real value.
		*/
		void addScaledVector(const npVector3& v, npReal scale) {
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

		//TODO: implement
		/*npReal angle(const npVector3& v) {
		return acoshf(this->dotProduct(v) / (this->length() * v.length()));
		}*/

#pragma region operator overloads
		void operator+=(const npVector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator-=(const npVector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(const npReal& v)
		{
			x *= v;
			y *= v;
			z *= v;
		}

		void operator%=(const npVector3& v)
		{
			x = y*v.z - z*v.y;
			y = y*v.x - x*v.z;
			z = x*v.y - y*v.x;
		}

		npVector3& operator+(const npVector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		npVector3& operator-(const npVector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		npVector3& operator*(const npReal& v)
		{
			x *= v;
			y *= v;
			z *= v;
			return *this;
		}

		npReal operator*(npVector3& v)
		{
			return (x * v.x) + (y * v.y) + (z * v.z);
		}

		npVector3& operator%(const npVector3& vector)
		{
			x = y*vector.z - z*vector.y;
			y = y*vector.x - x*vector.z;
			z = x*vector.y - y*vector.x;
			return *this;
		}
#pragma endregion

	};
}

#endif // NEPTUNE_NPVECTOR3_H