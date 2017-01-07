#ifndef NEPTUNE_NPVECTOR3_H
#define NEPTUNE_NPVECTOR3_H

#include <math.h>

#include "npPrecision.hpp"

namespace NeptunePhysics {

	template<typename T>
	class npVector3 {

	public:
		T x, y, z;
		npVector3() : x(0), y(0), z(0) {}
		npVector3(const T &xx, const T &yy, const T &zz) : x(xx), y(yy), z(zz) {}

		T getValue(int axis) const
		{
			if (axis == 0)
				return x;
			else if (axis == 1)
				return y;
			else
				return z;
		}

		void setValue(int axis, T value)
		{
			if (axis == 0)
				x = value;
			else if (axis == 1)
				y = value;
			else
				z = value;
		}

		/*!
		Returns square length value without the sqrt
		*/
		T squareLength() const
		{
			return (x * x) + (y * y) + (z * z);
		}

		/*!
		Returns the length of this vector.
		*/
		T length() const
		{
			return (npReal)sqrt((x * x) + (y * y) + (z * z));
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
		Normalizes the vector = vector / length
		*/
		npVector3<T>& normalize()
		{
			const npReal l = (npReal)sqrt(x * x + y * y + z * z);

			x /= l;
			y /= l;
			z /= l;

			return *this;
		}

		/*!
		\param vector a referenced Vector3.
		\param scale a scale with a real value.
		*/
		void addScaledVector(const npVector3<T> &v, const T &scale)
		{
			x += v.x * scale;
			y += v.y * scale;
			z += v.z * scale;
		}

		/*!
		\param vector a referenced Vector3.
		*/
		void componentProductUpdate(const npVector3<T> &v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
		}

		/*!
		Angle between two vectors in degrees
		*/
		T angle(const npVector3<T> &v)
		{
			auto top = (x * v.x) + (y * v.y) + (z * v.z);
			auto bottom = this->length() * v.length();
			return (T)(acos(top / bottom) * (180 / NP_PI));
		}

		void operator+=(const npVector3<T> &v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator-=(const npVector3<T> &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(const T &v) {
			x *= v;
			y *= v;
			z *= v;
		}

		bool operator!=(const npVector3<T> &v) {
			return x != v.x || y != v.y || z != v.z;
		}

		void operator%=(const npVector3<T> &v) {
			npVector3<T> r(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
			(*this) = r;
		}

		npVector3<T> operator+(const npVector3<T> &v) const {
			return npVector3(x + v.x, y + v.y, z + v.z);
		}

		npVector3<T> operator-(const npVector3<T> &v) const {
			return npVector3(x - v.x, y - v.y, z - v.z);
		}

		npVector3<T> operator*(const T &v) const {
			return npVector3(x * v, y * v, z * v);
		}

		npReal operator*(const npVector3<T> &v) const {
			return (x * v.x) + (y * v.y) + (z * v.z);
		}

		/*!
		Returns cross product between two vectors
		*/
		npVector3<T> operator%(const npVector3<T> &v) const {
			return npVector3<T>(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x);
		}

		bool operator>=(const npVector3<T> &v) const {
			return x >= v.x && y >= v.y && z >= v.z;
		}

		bool operator<=(const npVector3<T> &v) const {
			return x <= v.x && y <= v.y && z <= v.z;
		}
	};

	typedef npVector3<npReal> npVector3r;
	typedef npVector3<int> npVector3i;
	typedef npVector3<unsigned int> npVector3ui;
}
#endif // NEPTUNE_NPVECTOR3_H