#ifndef NEPTUNE_NPMATRIX3_H
#define NEPTUNE_NPMATRIX3_H

#include "npPrecision.hpp"
#include "npVector3.hpp"
#include "npQuaternion.h"

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
		npReal m[9]; //TODO dodaj komentarje za vse operacije

		npMatrix3(const npReal &v = 1.0f)
		{
			m[0] = m[4] = m[8] = v; // diagonal elements
			m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
		}

		npMatrix3(const npReal &a00, const npReal &a01, const npReal &a02,
			const npReal &a10, const npReal &a11, const npReal &a12,
			const npReal &a20, const npReal &a21, const npReal &a22)
		{
			m[0] = a00;		m[1] = a01;		m[2] = a02;
			m[3] = a10;		m[4] = a11;		m[5] = a12;
			m[6] = a20;		m[7] = a21;		m[8] = a22;
		}

		npMatrix3 operator*(const npReal &_value) const
		{
			return npMatrix3(
				m[0] * _value, m[1] * _value, m[2] * _value,
				m[3] * _value, m[4] * _value, m[5] * _value,
				m[6] * _value, m[7] * _value, m[8] * _value
				);
		}

		npMatrix3 operator*(const npMatrix3 &_rmat) const
		{
			return npMatrix3(
				m[0] * _rmat.m[0] + m[1] * _rmat.m[3] + m[2] * _rmat.m[6],
				m[0] * _rmat.m[1] + m[1] * _rmat.m[4] + m[2] * _rmat.m[7],
				m[0] * _rmat.m[2] + m[1] * _rmat.m[5] + m[2] * _rmat.m[8],

				m[3] * _rmat.m[0] + m[4] * _rmat.m[3] + m[5] * _rmat.m[6],
				m[3] * _rmat.m[1] + m[4] * _rmat.m[4] + m[5] * _rmat.m[7],
				m[3] * _rmat.m[2] + m[4] * _rmat.m[5] + m[5] * _rmat.m[8],

				m[6] * _rmat.m[0] + m[7] * _rmat.m[3] + m[8] * _rmat.m[6],
				m[6] * _rmat.m[1] + m[7] * _rmat.m[4] + m[8] * _rmat.m[7],
				m[6] * _rmat.m[2] + m[7] * _rmat.m[5] + m[8] * _rmat.m[8]
				);
		}

		npMatrix3 operator+(const npMatrix3 &_rmat) const
		{
			return npMatrix3(
				m[0] + _rmat.m[0], m[1] + _rmat.m[1], m[2] + _rmat.m[2],
				m[3] + _rmat.m[3], m[4] + _rmat.m[4], m[5] + _rmat.m[5],
				m[6] + _rmat.m[6], m[7] + _rmat.m[7], m[8] + _rmat.m[8]
				);
		}

		npVector3r operator*(const npVector3r &_vector) const
		{
			return npVector3r(
				_vector.x * m[0] + _vector.y * m[1] + _vector.z * m[2],
				_vector.x * m[3] + _vector.y * m[4] + _vector.z * m[5],
				_vector.x * m[6] + _vector.y * m[7] + _vector.z * m[8]);
		}

		void operator*=(const npReal &_value) {
			m[0] *= _value;
			m[1] *= _value;
			m[2] *= _value;
			
			m[3] *= _value;
			m[4] *= _value;
			m[5] *= _value;
			
			m[6] *= _value;
			m[7] *= _value;
			m[8] *= _value;
		}

		void operator*=(const npMatrix3 &_rmat) {
			npReal v1, v2, v3;
			v1 = m[0] * _rmat.m[0] + m[1] * _rmat.m[3] + m[2] * _rmat.m[6];
			v2 = m[0] * _rmat.m[1] + m[1] * _rmat.m[4] + m[2] * _rmat.m[7];
			v3 = m[0] * _rmat.m[2] + m[1] * _rmat.m[5] + m[2] * _rmat.m[8];
			m[0] = v1;
			m[1] = v2;
			m[2] = v3;

			v1 = m[3] * _rmat.m[0] + m[4] * _rmat.m[3] + m[5] * _rmat.m[6];
			v2 = m[3] * _rmat.m[1] + m[4] * _rmat.m[4] + m[5] * _rmat.m[7];
			v3 = m[3] * _rmat.m[2] + m[4] * _rmat.m[5] + m[5] * _rmat.m[8];
			m[3] = v1;
			m[4] = v2;
			m[5] = v3;

			v1 = m[6] * _rmat.m[0] + m[7] * _rmat.m[3] + m[8] * _rmat.m[6];
			v2 = m[6] * _rmat.m[1] + m[7] * _rmat.m[4] + m[8] * _rmat.m[7];
			v3 = m[6] * _rmat.m[2] + m[7] * _rmat.m[5] + m[8] * _rmat.m[8];
			m[6] = v1;
			m[7] = v2;
			m[8] = v3;
		}

		void operator+=(const npMatrix3 &_rmat) {
			m[0] += _rmat.m[0];
			m[1] += _rmat.m[1];
			m[2] += _rmat.m[2];

			m[3] += _rmat.m[3];
			m[4] += _rmat.m[4];
			m[5] += _rmat.m[5];

			m[6] += _rmat.m[6];
			m[7] += _rmat.m[7];
			m[8] += _rmat.m[8];
		}

		npVector3r transform(const npVector3r &_vector) const
		{
			return (*this) * _vector;
		}

		npReal getDeterminant() const
		{
			return getDeterminant(*this);
		}

		void setInverse(const npMatrix3 &_rmat)
		{
			npReal det = getDeterminant(_rmat);

			if (det == 0.0f) return;
			npReal invDet = 1.0f / det;

			m[0] = (_rmat.m[4] * _rmat.m[8] - _rmat.m[7] * _rmat.m[5]) * invDet;
			m[1] = -(_rmat.m[1] * _rmat.m[8] - _rmat.m[2] * _rmat.m[7]) * invDet;
			m[2] = (_rmat.m[1] * _rmat.m[5] - _rmat.m[2] * _rmat.m[4]) * invDet;

			m[3] = -(_rmat.m[3] * _rmat.m[8] - _rmat.m[5] * _rmat.m[6]) * invDet;
			m[4] = (_rmat.m[0] * _rmat.m[8] - _rmat.m[2] * _rmat.m[6]) * invDet;
			m[5] = -(_rmat.m[0] * _rmat.m[5] - _rmat.m[2] * _rmat.m[3])* invDet;

			m[6] = (_rmat.m[3] * _rmat.m[7] - _rmat.m[4] * _rmat.m[6]) * invDet;
			m[7] = -(_rmat.m[0] * _rmat.m[7] - _rmat.m[1] * _rmat.m[6]) * invDet;
			m[8] = (_rmat.m[0] * _rmat.m[4] - _rmat.m[1] * _rmat.m[3]) * invDet;
		}

		npMatrix3 inverse() const
		{
			npMatrix3 result;
			result.setInverse(*this);
			return result;
		}

		void invert()
		{
			npMatrix3 result;
			result.setInverse(*this);
			*this = result;
		}
		
		npMatrix3 transpose() const
		{
			npMatrix3 result;
			result.setTranspose(*this);
			return result;
		}

		void setOrientation(const npQuarternion &q)
		{
			m[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
			m[1] = 2 * q.i * q.j + 2 * q.k * q.r;
			m[2] = 2 * q.i * q.k - 2 * q.j * q.r;

			m[3] = 2 * q.i * q.j - 2 * q.k * q.r;
			m[4] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
			m[5] = 2 * q.j * q.k + 2 * q.i * q.r;

			m[6] = 2 * q.i * q.k + 2 * q.j * q.r;
			m[7] = 2 * q.j * q.k - 2 * q.i * q.r;
			m[8] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
		}

	private:
		npReal getDeterminant(const npMatrix3 &_rmat) const
		{
			npReal v1 = _rmat.m[0] * _rmat.m[4] * _rmat.m[8];
			npReal v2 = _rmat.m[1] * _rmat.m[5] * _rmat.m[6];
			npReal v3 = _rmat.m[2] * _rmat.m[3] * _rmat.m[7];

			npReal v4 = _rmat.m[6] * _rmat.m[4] * _rmat.m[2];
			npReal v5 = _rmat.m[7] * _rmat.m[5] * _rmat.m[0];
			npReal v6 = _rmat.m[8] * _rmat.m[3] * _rmat.m[1];

			return v1 + v2 + v3 - v4 - v5 - v6;
		}

		void setTranspose(const npMatrix3 &_rmat) {
			m[0] = _rmat.m[0]; m[1] = _rmat.m[3]; m[2] = _rmat.m[6];
			m[3] = _rmat.m[1]; m[4] = _rmat.m[4]; m[5] = _rmat.m[7];
			m[6] = _rmat.m[2]; m[7] = _rmat.m[5]; m[8] = _rmat.m[8];
		}
	};
}
#endif