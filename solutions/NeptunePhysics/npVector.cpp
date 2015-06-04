#include "npVector.h"

namespace neptunePhysics {

	npReal npVector3::squareLength() {
		return (x * x) + (y * y) + (z * z);
	}

	npReal npVector3::length() {
		return sqrt((x * x) + (y * y) + (z * z));
	}

	void npVector3::invert()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	void npVector3::normalize() {
		npReal l = this->length();
		if (l > 0) {
			x /= l;
			y /= l;
			z /= l;
			(*this) *= ((npReal)l) / l;
		}
	}

	void npVector3::addScaledVector(const npVector3& v, const npReal& scale) {
		x += v.x * scale;
		y += v.y * scale;
		z += v.z * scale;
	}

	void npVector3::componentProductUpdate(const npVector3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

#pragma region operator overloads
	void npVector3::operator+=(const npVector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	void npVector3::operator-=(const npVector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	void npVector3::operator*=(const npReal& v)
	{
		x *= v;
		y *= v;
		z *= v;
	}

	void npVector3::operator%=(const npVector3& v)
	{
		npVector3 r(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
		(*this) = r;
	}

	npVector3& npVector3::operator+(const npVector3& v) const
	{
		return npVector3(x + v.x, y + v.y, z + v.z);
	}

	npVector3& npVector3::operator-(const npVector3& v) const
	{
		return npVector3(x - v.x, y - v.y, z - v.z);
	}

	npVector3& npVector3::operator*(const npReal& v) const
	{
		return npVector3(x * v, y * v, z * v);
	}

	npReal npVector3::operator*(npVector3& v) const
	{
		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	npVector3& npVector3::operator%(const npVector3& v) const
	{
		return npVector3(
			y*v.z - z*v.y, 
			z*v.x - x*v.z,
			x*v.y - y*v.x);
	}
#pragma endregion
}


