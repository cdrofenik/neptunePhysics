#include <math.h>

#ifndef NEPTUNE_CORE_H
#define NEPTUNE_CORE_H

#include "precision.h"

namespace neptune
{
	class Vector3 {

	public:
		real x;
		real y;
		real z;

		//! Vector3 default constructor
		/*!
		Initializes the class Vector3 putting all the values to 0.
		*/
		Vector3() : x(0), y(0), z(0) {}

		//! Vector3 constructor which takes x, y and z.
		/*!
		Vector3 constructor which takes x, y and z values for initialization.
		*/
		Vector3(real _x, real _y, real _z) : x(_x), y(_y), z(_z) {}

		//! Returns the magnitute/length of this vector
		/*!
		Returns the magnitute/length of this vector.
		*/
		real magnitute() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		//! Returns the square magnitude value
		/*!
		Returns square magnitude value without the sqrt
		*/
		real squareMagnitude() const
		{
			return x*x + y*y + z*z;
		}

		//! Calculates the vector product of this vector with the given one.
		/*!
		\param vector a referenced Vector3.
		\return a vector which is the vector product of the two vectors
		*/
		Vector3 vectorProduct(const Vector3& vector) const
		{
			return Vector3(
				y*vector.z - z*vector.y,
				y*vector.x - x*vector.z,
				x*vector.y - y*vector.x
				);
		}

		//! Calculates the scalar product of this vector with the given one.
		/*!
		\param vector a referenced Vector3.
		\return a scalar (value) which is the product of the two vectors
		*/
		real scalarProduct(const Vector3& vector) const
		{
			return x*vector.x + y*vector.y + z*vector.z;
		}

		//! Inverts the vector
		/*!
		Inverts the vector values.
		*/
		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		//! Normalizes the vector.
		/*!
		Normalizes the vector = vector / length(vector)
		*/
		void normalize()
		{
			real l = magnitute();
			if (l > 0)
			{
				(*this) *= ((real)l) / l;
			}
		}

		//! Scales the given vector.
		/*!
		\param vector a referenced Vector3.
		\param scale a scale with a real value.
		*/
		void addScaledVector(const Vector3& vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		//! Multiplies each vector value with it's counterpart in the other vector
		/*!
		\param vector a referenced Vector3.
		\return A vector with it's components multiplied by the components of the parameter.
		*/
		Vector3 componentProduct(const Vector3& vector) const
		{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}

		//! Multiplies this vector value with it's parameter counterparts
		/*!
		\param vector a referenced Vector3.
		*/
		void componentProductUpdate(const Vector3& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		Vector3 operator+=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		Vector3 operator-=(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator*=(const real value)
		{
			x *= value;
			y *= value;
			z *= value;
		}

		Vector3 operator+(const Vector3& v)
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator-(const Vector3& v)
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3 operator*(const real value) const
		{
			return Vector3(x*value, y*value, z*value);
		}

		real operator*(const Vector3& v) const
		{
			return scalarProduct(v);
		}

		Vector3 operator%=(const Vector3& vector)
		{
			*this = vectorProduct(vector);
		}

		Vector3 operator%(const Vector3& vector) const
		{
			return Vector3(
				y*vector.z - z*vector.y,
				y*vector.x - x*vector.z,
				x*vector.y - y*vector.x
				);
		}

		//! Calculates the orthonormal basic vectors
		/*!
		\param vector a referenced Vector3.
		\param vector a referenced Vector3.
		\param vector a referenced Vector3.
		*/
		void makeOrthonormalBasic(Vector3 *a, Vector3 *b, Vector3 *c)
		{
			a->normalize();
			(*c) = (*a) % (*b);
			if (c->squareMagnitude() == 0.0) return;
			c->normalize();
			(*b) = (*c) % (*a);
		}

	private:
		real placeHolder;
	};
}

#endif // NEPTUNE_CORE_H