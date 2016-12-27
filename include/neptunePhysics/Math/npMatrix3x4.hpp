#ifndef NEPTUNE_NPMATRIX3X4_H
#define NEPTUNE_NPMATRIX3X4_H

#include "npVector3.hpp"
#include "npQuaternion.hpp"

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

	class npMatrix3x4
	{
	public:
		npReal m[12]; //TODO dodaj komentarje za vse operacije

		npMatrix3x4(const npReal& v = 1.0f)
		{
			m[0] = m[5] = m[10] = v; // diagonal elements
			m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = 0.0f;
		}

		npMatrix3x4(const npReal& a0, const npReal& a1, const npReal& a2, const npReal& a3,
			const npReal& a4, const npReal& a5, const npReal& a6, const npReal& a7,
			const npReal& a8, const npReal& a9, const npReal& a10, const npReal& a11)
		{
			m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3;
			m[4] = a4; m[5] = a5; m[6] = a6; m[7] = a7;
			m[8] = a8; m[9] = a9; m[10] = a10; m[11] = a11;
		}

		npVector3r operator*(const npVector3r& _vector) const
		{
			return npVector3r(
				_vector.x * m[0] + _vector.y * m[1] + _vector.z * m[2] + m[3],
				_vector.x * m[4] + _vector.y * m[5] + _vector.z * m[6] + m[7],
				_vector.x * m[8] + _vector.y * m[9] + _vector.z * m[10] + m[11]
				);
		}

		npMatrix3x4 operator*(const npMatrix3x4& _rmat) const
		{
			return npMatrix3x4(
				m[0] * _rmat.m[0] + m[1] * _rmat.m[4] + m[2] * _rmat.m[8],
				m[0] * _rmat.m[1] + m[1] * _rmat.m[5] + m[2] * _rmat.m[9],
				m[0] * _rmat.m[2] + m[1] * _rmat.m[6] + m[2] * _rmat.m[10],
				m[0] * _rmat.m[3] + m[1] * _rmat.m[7] + m[2] * _rmat.m[11] + m[3],

				m[4] * _rmat.m[0] + m[5] * _rmat.m[4] + m[6] * _rmat.m[8],
				m[4] * _rmat.m[1] + m[5] * _rmat.m[5] + m[6] * _rmat.m[9],
				m[4] * _rmat.m[2] + m[5] * _rmat.m[6] + m[6] * _rmat.m[10],
				m[4] * _rmat.m[3] + m[5] * _rmat.m[7] + m[6] * _rmat.m[11] + m[7],

				m[8] * _rmat.m[0] + m[9] * _rmat.m[4] + m[10] * _rmat.m[8],
				m[8] * _rmat.m[1] + m[9] * _rmat.m[5] + m[10] * _rmat.m[9],
				m[8] * _rmat.m[2] + m[9] * _rmat.m[6] + m[10] * _rmat.m[10],
				m[8] * _rmat.m[3] + m[9] * _rmat.m[7] + m[10] * _rmat.m[11] + m[11]
				);
		}

		void operator*=(const npMatrix3x4& _rmat)
		{
			npReal v1, v2, v3, v4;
			v1 = m[0] * _rmat.m[0] + m[1] * _rmat.m[4] + m[2] * _rmat.m[8];
			v2 = m[0] * _rmat.m[1] + m[1] * _rmat.m[5] + m[2] * _rmat.m[9];
			v3 = m[0] * _rmat.m[2] + m[1] * _rmat.m[6] + m[2] * _rmat.m[10];
			v4 = m[0] * _rmat.m[3] + m[1] * _rmat.m[7] + m[2] * _rmat.m[11] + m[3];
			m[0] = v1;
			m[1] = v2;
			m[2] = v3;
			m[3] = v4;

			v1 = m[4] * _rmat.m[0] + m[5] * _rmat.m[4] + m[6] * _rmat.m[8];
			v2 = m[4] * _rmat.m[1] + m[5] * _rmat.m[5] + m[6] * _rmat.m[9];
			v3 = m[4] * _rmat.m[2] + m[5] * _rmat.m[6] + m[6] * _rmat.m[10];
			v4 = m[4] * _rmat.m[3] + m[5] * _rmat.m[7] + m[6] * _rmat.m[11] + m[7];
			m[4] = v1;
			m[5] = v2;
			m[6] = v3;
			m[7] = v4;

			v1 = m[8] * _rmat.m[0] + m[9] * _rmat.m[4] + m[10] * _rmat.m[8];
			v2 = m[8] * _rmat.m[1] + m[9] * _rmat.m[5] + m[10] * _rmat.m[9];
			v3 = m[8] * _rmat.m[2] + m[9] * _rmat.m[6] + m[10] * _rmat.m[10];
			v4 = m[8] * _rmat.m[3] + m[9] * _rmat.m[7] + m[10] * _rmat.m[11] + m[11];
			m[8] = v1;
			m[9] = v2;
			m[10] = v3;
			m[11] = v4;
		}

		npVector3r transform(const npVector3r& _vector) const
		{
			return (*this) * _vector;
		}

		npReal getDeterminant() const
		{
			return getDeterminant(*this);
		}

		npMatrix3x4 inverse() const
		{
			npMatrix3x4 result;
			result.setInverse(*this);
			return result;
		}

		void invert()
		{
			npMatrix3x4 result;
			result.setInverse(*this);
			*this = result;
		}

		void setOrientation(const npQuarternion &_q, const npVector3r &_pos)
		{
			m[0] = 1 - (2 * _q.j * _q.j + 2 * _q.k * _q.k);
			m[1] = 2 * _q.i * _q.j + 2 * _q.k * _q.r;
			m[2] = 2 * _q.i * _q.k - 2 * _q.j * _q.r;
			m[3] = _pos.x;

			m[4] = 2 * _q.i * _q.j - 2 * _q.k * _q.r;
			m[5] = 1 - (2 * _q.i * _q.i + 2 * _q.k * _q.k);
			m[6] = 2 * _q.j * _q.k + 2 * _q.i * _q.r;
			m[7] = _pos.y;

			m[8] = 2 * _q.i * _q.k + 2 * _q.j * _q.r;
			m[9] = 2 * _q.j * _q.k - 2 * _q.i * _q.r;
			m[10] = 1 - (2 * _q.i * _q.i + 2 * _q.j * _q.j);
			m[11] = _pos.z;
		}

		npVector3r transformInverse(const npVector3r &_vector) const
		{
			npVector3r tmp = _vector;
			tmp.x -= m[3];
			tmp.x -= m[7];
			tmp.x -= m[11];
			return npVector3r(
				tmp.x * m[0] + tmp.y * m[4] + tmp.z * m[8],
				tmp.x * m[1] + tmp.y * m[5] + tmp.z * m[9],
				tmp.x * m[2] + tmp.y * m[6] + tmp.z * m[10]
				);
		}
	
	private:
		npReal getDeterminant(const npMatrix3x4 &_rmat) const
		{
			npReal v1 = _rmat.m[0] * _rmat.m[5] * _rmat.m[10];
			npReal v2 = _rmat.m[8] * _rmat.m[1] * _rmat.m[6];
			npReal v3 = _rmat.m[4] * _rmat.m[9] * _rmat.m[2];

			npReal v4 = _rmat.m[8] * _rmat.m[5] * _rmat.m[2];
			npReal v5 = _rmat.m[0] * _rmat.m[9] * _rmat.m[6];
			npReal v6 = _rmat.m[4] * _rmat.m[1] * _rmat.m[10];

			return v1 + v2 + v3 - v4 - v5 - v6;
		}

		void setInverse(const npMatrix3x4 &_rmat)
		{
			npReal det = getDeterminant(_rmat);

			if (det == 0.0f) return;
			npReal invDet = 1.0f / det;

			m[0] = (-_rmat.m[9] * _rmat.m[6] + _rmat.m[5] * _rmat.m[10]) * invDet;
			m[1] = (_rmat.m[9] * _rmat.m[2] - _rmat.m[1] * _rmat.m[10]) * invDet;
			m[2] = (-_rmat.m[5] * _rmat.m[2] + _rmat.m[1] * _rmat.m[6]) * invDet;

			m[3] = (_rmat.m[9] * _rmat.m[6] * _rmat.m[3]
				- _rmat.m[5] * _rmat.m[10] * _rmat.m[3]
				- _rmat.m[9] * _rmat.m[2] * _rmat.m[7]
				+ _rmat.m[1] * _rmat.m[10] * _rmat.m[7]
				+ _rmat.m[5] * _rmat.m[2] * _rmat.m[11]
				- _rmat.m[1] * _rmat.m[6] * _rmat.m[11]) * invDet;

			m[4] = (_rmat.m[8] * _rmat.m[6] - _rmat.m[4] * _rmat.m[10]) * invDet;
			m[5] = (-_rmat.m[8] * _rmat.m[2] + _rmat.m[0] * _rmat.m[10]) * invDet;
			m[6] = (+_rmat.m[4] * _rmat.m[2] - _rmat.m[0] * _rmat.m[6]) * invDet;

			m[7] = (_rmat.m[8] * _rmat.m[6] * _rmat.m[3]
				- _rmat.m[4] * _rmat.m[10] * _rmat.m[3]
				- _rmat.m[8] * _rmat.m[2] * _rmat.m[7]
				+ _rmat.m[0] * _rmat.m[10] * _rmat.m[7]
				+ _rmat.m[4] * _rmat.m[2] * _rmat.m[11]
				- _rmat.m[0] * _rmat.m[6] * _rmat.m[11]) * invDet;

			m[8] = (-_rmat.m[8] * _rmat.m[5] + _rmat.m[4] * _rmat.m[9]) * invDet;
			m[9] = (_rmat.m[8] * _rmat.m[1] + _rmat.m[0] * _rmat.m[9]) * invDet;
			m[10] = (-_rmat.m[4] * _rmat.m[1] - _rmat.m[0] * _rmat.m[5]) * invDet;

			m[11] = (_rmat.m[8] * _rmat.m[5] * _rmat.m[3]
				- _rmat.m[4] * _rmat.m[9] * _rmat.m[3]
				- _rmat.m[8] * _rmat.m[1] * _rmat.m[7]
				+ _rmat.m[0] * _rmat.m[9] * _rmat.m[7]
				+ _rmat.m[4] * _rmat.m[1] * _rmat.m[11]
				- _rmat.m[0] * _rmat.m[5] * _rmat.m[11]) * invDet;
		}

	};

}

#endif