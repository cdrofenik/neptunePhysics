#ifndef NEPTUNE_NPMATRIX3_H
#define NEPTUNE_NPMATRIX3_H

#include "npPrecision.hpp"
#include "npVector3.hpp"

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

	//TODO: Set row major setting for both classes

	class npMatrix3 {

	public:
		npReal m[3][3];

		npMatrix3(const npReal& v = 1.0f) {
			m[0][0] = v;	 m[0][1] = 0.0f;   m[0][2] = 0.0f;
			m[1][0] = 0.0f;  m[1][1] = v;   m[1][2] = 0.0f;
			m[2][0] = 0.0f;  m[2][1] = 0.0f;   m[2][2] = v;
		}

		npMatrix3(const npReal& a00, const npReal& a01, const npReal& a02,
			const npReal& a10, const npReal& a11, const npReal& a12,
			const npReal& a20, const npReal& a21, const npReal& a22) {
			m[0][0] = a00;	 m[0][1] = a01;   m[0][2] = a02;
			m[1][0] = a10;  m[1][1] = a11;   m[1][2] = a12;
			m[2][0] = a20;  m[2][1] = a21;   m[2][2] = a22;
		}

		npMatrix3& operator*(const npReal& v) const {
			npMatrix3 Ret;
			for (size_t i = 0; i < 3; i++)
			{
				Ret.m[i][0] = m[i][0] * v;
				Ret.m[i][1] = m[i][1] * v;
				Ret.m[i][2] = m[i][2] * v;
			}

			return Ret;
		}

		npMatrix3& operator*(const npMatrix3& v) const {
			npMatrix3 Ret;
			for (unsigned int i = 0; i < 3; i++) {
				for (unsigned int j = 0; j < 3; j++) {
					Ret.m[i][j] = m[i][0] * v.m[0][j] +
						m[i][1] * v.m[1][j] +
						m[i][2] * v.m[2][j];
				}
			}

			return Ret;
		}

		npVector3<npReal> operator*(const npVector3<npReal>& _vector) {
			return npVector3<npReal>(
				_vector.x * m[0][0] + _vector.y * m[1][0] + _vector.z * m[2][0],
				_vector.x * m[0][1] + _vector.y * m[1][1] + _vector.z * m[2][1],
				_vector.x * m[0][2] + _vector.y * m[2][1] + _vector.z * m[2][2]);
		}

		npMatrix3& operator+(const npMatrix3& v) const {
			npMatrix3 Ret;
			for (unsigned int i = 0; i < 3; i++) {
				for (unsigned int j = 0; j < 3; j++) {
					Ret.m[i][j] = m[i][j] + v.m[i][j];
				}
			}

			return Ret;
		}

		/** Init
		Fills the 3x3 matrix with input value

		@param v Input value
		*/
		void Init(const npReal& v) {
			for (size_t i = 0; i < 3; i++)
			{
				m[i][0] = v;
				m[i][1] = v;
				m[i][2] = v;
			}
		}
	
		npMatrix3 rotate(const npReal& _angle, const npVector3<npReal>& axis) {
			npReal radian = ToRadian(_angle);

			npMatrix3 aaT(
				axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
				axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
				axis.x * axis.z, axis.y * axis.z, axis.z * axis.z
				);

			npMatrix3 Astar(0, -axis.z, axis.y,
				axis.z, 0, -axis.x,
				-axis.y, axis.x, 0);

			return npMatrix3()*cos(radian) + aaT*(1 - cos(radian)) + Astar*sin(radian);
		}
	};
}
#endif