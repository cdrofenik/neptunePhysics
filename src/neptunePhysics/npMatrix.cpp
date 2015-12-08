
#include "neptunePhysics\npMatrix.h"

namespace NeptunePhysics {

//-------------------- npMatrix3
	npMatrix3::npMatrix3() {
		m[0][0] = 1.0f;	 m[0][1] = 0.0f;   m[0][2] = 0.0f;
		m[1][0] = 0.0f;  m[1][1] = 1.0f;   m[1][2] = 0.0f;
		m[2][0] = 0.0f;  m[2][1] = 0.0f;   m[2][2] = 1.0f;
	}

	npMatrix3::npMatrix3(npReal v) {
		m[0][0] = v;	 m[0][1] = 0.0f;   m[0][2] = 0.0f;
		m[1][0] = 0.0f;  m[1][1] = v;   m[1][2] = 0.0f;
		m[2][0] = 0.0f;  m[2][1] = 0.0f;   m[2][2] = v;
	}

	npMatrix3::npMatrix3(const npReal& a00, const npReal& a01, const npReal& a02,
		const npReal& a10, const npReal& a11, const npReal& a12,
		const npReal& a20, const npReal& a21, const npReal& a22) {
		m[0][0] = a00;	 m[0][1] = a01;   m[0][2] = a02;
		m[1][0] = a10;  m[1][1] = a11;   m[1][2] = a12;
		m[2][0] = a20;  m[2][1] = a21;   m[2][2] = a22;
	}

	npMatrix3& npMatrix3::operator*(const npReal& v) const {
		npMatrix3 Ret;
		for (size_t i = 0; i < 3; i++)
		{
			Ret.m[i][0] = m[i][0] * v;
			Ret.m[i][1] = m[i][1] * v;
			Ret.m[i][2] = m[i][2] * v;
		}

		return Ret;
	}

	npMatrix3& npMatrix3::operator*(const npMatrix3& v) const {
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

	npMatrix3& npMatrix3::operator+(const npMatrix3& v) const {
		npMatrix3 Ret;
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				Ret.m[i][j] = m[i][j] + v.m[i][j];
			}
		}

		return Ret;
	}

	void npMatrix3::init(npReal v) {
		for (size_t i = 0; i < 3; i++)
		{
			m[i][0] = v;
			m[i][1] = v;
			m[i][2] = v;
		}
	}

//-------------------------	npMatrix4
	void npMatrix4::init(npReal v) {
		for (size_t i = 0; i < 4; i++)
		{
			m[i][0] = v;
			m[i][1] = v;
			m[i][2] = v;
			m[i][3] = v;
		}
	}

	npMatrix4::npMatrix4() {
		m[0][0] = 1.0f;	 m[0][1] = 0.0f;   m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;  m[1][1] = 1.0f;   m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;  m[2][1] = 0.0f;   m[2][2] = 1.0f;	m[2][3] = 0.0f;
		m[3][0] = 0.0f;  m[3][1] = 0.0f;   m[3][2] = 0.0f;  m[3][3] = 1.0f;
	}

	npMatrix4::npMatrix4(npReal v) {
		m[0][0] = v;	 m[0][1] = 0.0f;   m[0][2] = 0.0f;	m[0][3] = 0.0f;
		m[1][0] = 0.0f;  m[1][1] = v;	   m[1][2] = 0.0f;	m[1][3] = 0.0f;
		m[2][0] = 0.0f;  m[2][1] = 0.0f;   m[2][2] = v;		m[2][3] = 0.0f;
		m[3][0] = 0.0f;  m[3][1] = 0.0f;   m[3][2] = 0.0f;  m[3][3] = 1.0f;
	}

	npMatrix4::npMatrix4(npMatrix3 v) {
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

	npMatrix4 npMatrix4::operator*(const npMatrix4& _right) const
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
}