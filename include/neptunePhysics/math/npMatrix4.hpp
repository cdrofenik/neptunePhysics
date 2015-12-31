#ifndef NEPTUNE_NPMATRIX4_H
#define NEPTUNE_NPMATRIX4_H

#include "npMatrix3.hpp"

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

class npMatrix4 {

public:
	npReal m[4][4]; //TODO: Create single array that is opengl compatible

	npMatrix4(const npReal& v = 1.0f) {
		m[0][0] = v;	 m[0][1] = 0.0f;   m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;  m[1][1] = v;	   m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;  m[2][1] = 0.0f;   m[2][2] = v;		m[2][3] = 0.0f;
		m[3][0] = 0.0f;  m[3][1] = 0.0f;   m[3][2] = 0.0f;  m[3][3] = 1.0f;
	}

	npMatrix4(const npMatrix3& v) {
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				m[i][0] = v.m[i][j];
				m[i][1] = v.m[i][j];
				m[i][2] = v.m[i][j];
				m[i][3] = 0;
			}
		}
		m[3][3] = 1;
	}

	npMatrix4 operator*(const npMatrix4& _right) const
	{
		npMatrix4 ret;
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				ret.m[i][j] = m[i][0] * _right.m[0][j] +
					m[i][1] * _right.m[1][j] +
					m[i][2] * _right.m[2][j] +
					m[i][3] * _right.m[3][j];
			}
		}

		return ret;
	}

	npMatrix4 operator+(const npMatrix4& _right) const
	{
		npMatrix4 ret;
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				ret.m[i][j] = m[i][j] + _right.m[i][j];
			}
		}

		return ret;
	}

	//TODO test
	npMatrix4 Transpose() {
		npMatrix4 result;
		result.m[0][0] = m[0][0];	result.m[0][1] = m[1][0];	result.m[0][2] = m[2][0];	result.m[0][3] = m[3][0];
		result.m[1][0] = m[0][1];	result.m[1][1] = m[1][1];	result.m[1][2] = m[2][1];	result.m[1][3] = m[3][1];
		result.m[2][0] = m[0][2];	result.m[2][1] = m[1][2];	result.m[2][2] = m[2][2];	result.m[2][3] = m[3][2];
		result.m[3][0] = m[0][3];	result.m[3][1] = m[1][3];	result.m[3][2] = m[2][3];	result.m[3][3] = m[3][3];

		return result;
	}

	/** Init
	Fills the 4x4 matrix with input value

	@param v Input value
	*/
	void Init(const npReal& v) {
		for (size_t i = 0; i < 4; i++)
		{
			m[i][0] = v;
			m[i][1] = v;
			m[i][2] = v;
			m[i][3] = v;
		}
	}
	
};
}

#endif