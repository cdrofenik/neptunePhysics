#ifndef NEPTUNE_NPVECTOR_H
#define NEPTUNE_NPVECTOR_H

template<typename T>
class npVector3
{
public:
	T x, y, z;
	npVector3() : x(0), y(0), z(0) {}
	npVector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

	/*!
	Returns the magnitute/length of this vector.
	*/
	template<typename T> T magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	/*!
	Returns square magnitude value without the sqrt
	*/
	template<typename T> T squareMagnitude() const {
		return x*x + y*y + z*z;
	}

	/*!
	\param vector a referenced Vector3.
	\return a vector which is the vector product of the two vectors
	*/
	npVector3<T> vectorProduct(const npVector3<T>& vector) const {
		return npVector3<T>(
			y*vector.z - z*vector.y,
			y*vector.x - x*vector.z,
			x*vector.y - y*vector.x
			);
	}

	/*!
	\param vector a referenced Vector3.
	\return a scalar (value) which is the product of the two vectors
	*/
	template<typename T> T scalarProduct(npVector3<T>& vector)
	{
		return x*vector.x + y*vector.y + z*vector.z;
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
		T l = this->magnitude();
		if (l > 0)
		{
			(*this) *= ((T)l) / l;
		}
	}

	/*!
	\param vector a referenced Vector3.
	\param scale a scale with a real value.
	*/
	void addScaledVector(const npVector3<T>& vector, T scale) {

		x += vector.x * scale;
		y += vector.y * scale;
		z += vector.z * scale;
	}

	/*!
	\param vector a referenced Vector3.
	*/
	void componentProductUpdate(const npVector3<T>& vector)
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
	}

	npVector3<T> operator+=(const npVector3<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	npVector3<T> operator-=(const npVector3<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	void operator*=(const T& value)
	{
		x *= value;
		y *= value;
		z *= value;
	}

	npVector3<T> operator+(const npVector3<T>& v)
	{
		return npVector3<T>(x + v.x, y + v.y, z + v.z);
	}

	npVector3<T> operator-(const npVector3<T>& v)
	{
		return npVector3<T>(x - v.x, y - v.y, z - v.z);
	}

	npVector3<T> operator*(const T& value) const
	{
		return npVector3<T>(x*value, y*value, z*value);
	}

	template<typename T> T operator*(npVector3<T>& vector)
	{
		return scalarProduct(vector);
	}

	npVector3<T> operator%=(const npVector3<T>& vector)
	{
		*this = vectorProduct(vector);
	}

	npVector3<T> operator%(const npVector3<T>& vector) const
	{
		return npVector3<T>(
			y*vector.z - z*vector.y,
			y*vector.x - x*vector.z,
			x*vector.y - y*vector.x
			);
	}

	/*!
	\param vector a referenced Vector3.
	\param vector b referenced Vector3.
	\param vector c referenced Vector3.
	*/
	void makeOrhonormalBasic(npVector3<T> *a, npVector3<T> *b, npVector3<T> *c)
	{
		a->normalize();
		(*c) = (*a) % (*b);
		if (c->squareMagnitude() == 0.0) return;
		c->normalize();
		(*b) = (*c) % (*a);
	}
};

typedef npVector3<float> npVector3f;
typedef npVector3<int> npVector3i;

#endif // NEPTUNE_NPVECTOR_H