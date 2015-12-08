#include "neptunePhysics\npVector.h"

#include <math.h>

namespace NeptunePhysics {

	npReal npVector3::squareLength() {
		
	}

	npReal npVector3::length() const {
		
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

	npReal npVector3::angle(const npVector3& v)
	{
		auto top = (x * v.x) + (y * v.y) + (z * v.z);
		auto bottom = this->length() * v.length();
		return (npReal)(acos(top/bottom) * (180 / NP_PI));
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


