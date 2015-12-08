#include "neptunePhysics\npTransform.h"

namespace NeptunePhysics {

//Public functions
	npMatrix4 npTransform::getTranslationsMatrix(const npReal& _x, const npReal& _y, const npReal& _z) {
		npMatrix4 v;
		v.m[0][0] = 1.0f;	v.m[0][1] = 0.0f;   v.m[0][2] = 0.0f;   v.m[0][3] = _x;
		v.m[1][0] = 0.0f;   v.m[1][1] = 1.0f;   v.m[1][2] = 0.0f;   v.m[1][3] = _y;
		v.m[2][0] = 0.0f;   v.m[2][1] = 0.0f;   v.m[2][2] = 1.0f;   v.m[2][3] = _z;
		v.m[3][0] = 0.0f;   v.m[3][1] = 0.0f;   v.m[3][2] = 0.0f;   v.m[3][3] = 1.0f;

		return v;
	}

	npMatrix4 npTransform::getScaleMatrix(const npReal& _x, const npReal& _y, const npReal& _z) {
		npMatrix4 v;
		v.m[0][0] = _x;		v.m[0][1] = 0.0f;   v.m[0][2] = 0.0f;   v.m[0][3] = 0.0f;
		v.m[1][0] = 0.0f;   v.m[1][1] = _y;		v.m[1][2] = 0.0f;   v.m[1][3] = 0.0f;
		v.m[2][0] = 0.0f;   v.m[2][1] = 0.0f;   v.m[2][2] = _z;		v.m[2][3] = 0.0f;
		v.m[3][0] = 0.0f;   v.m[3][1] = 0.0f;   v.m[3][2] = 0.0f;   v.m[3][3] = 1.0f;
		return v;
	}

	npMatrix4 npTransform::getRotationMatrix(const npReal& _alfaX, const npReal& _alfaY, const npReal& _alfaZ) {
		npMatrix4 v;

		//Rotation around z
		npMatrix4 aroundZ;
		aroundZ.m[0][0] = cosf(_alfaZ); aroundZ.m[0][1] = -sinf(_alfaZ); aroundZ.m[0][2] = 0.0f; aroundZ.m[0][3] = 0.0f;
		aroundZ.m[1][0] = sinf(_alfaZ); aroundZ.m[1][1] = cosf(_alfaZ);  aroundZ.m[1][2] = 0.0f; aroundZ.m[1][3] = 0.0f;
		aroundZ.m[2][0] = 0.0f;			aroundZ.m[2][1] = 0.0f;          aroundZ.m[2][2] = 1.0f; aroundZ.m[2][3] = 0.0f;
		aroundZ.m[3][0] = 0.0f;		    aroundZ.m[3][1] = 0.0f;          aroundZ.m[3][2] = 0.0f; aroundZ.m[3][3] = 1.0f;

		//Rotation around y
		npMatrix4 aroundY;
		aroundY.m[0][0] = cosf(_alfaY); aroundY.m[0][1] = 0.0f;			aroundY.m[0][2] = -sinf(_alfaY); aroundY.m[0][3] = 0.0f;
		aroundY.m[1][0] = 0.0f;			aroundY.m[1][1] = 1.0f;			aroundY.m[1][2] = 0.0f;			aroundY.m[1][3] = 0.0f;
		aroundY.m[2][0] = sinf(_alfaY);	aroundY.m[2][1] = 0.0f;         aroundY.m[2][2] = cosf(_alfaY); aroundY.m[2][3] = 0.0f;
		aroundY.m[3][0] = 0.0f;		    aroundY.m[3][1] = 0.0f;         aroundY.m[3][2] = 0.0f;			aroundY.m[3][3] = 1.0f;

		//Rotation around x
		npMatrix4 aroundX;
		aroundX.m[0][0] = 1.0f; aroundX.m[0][1] = 0.0f;			 aroundX.m[0][2] = 0.0f;			aroundX.m[0][3] = 0.0f;
		aroundX.m[1][0] = .0f;	aroundX.m[1][1] = cosf(_alfaX);  aroundX.m[1][2] = sinf(_alfaX);	aroundX.m[1][3] = 0.0f;
		aroundX.m[2][0] = 0.0f;	aroundX.m[2][1] = -sinf(_alfaX); aroundX.m[2][2] = cosf(_alfaX);	aroundX.m[2][3] = 0.0f;
		aroundX.m[3][0] = 0.0f;	aroundX.m[3][1] = 0.0f;          aroundX.m[3][2] = 0.0f;			aroundX.m[3][3] = 1.0f;

		v = aroundZ * aroundY * aroundX;
		return v;
	}

	npMatrix4 npTransform::getProjectionMatrix(const npReal& _as, const npReal& _zNear, const npReal& _zFar, const npReal& _fov) {
		npMatrix4 m;
		const npReal ar = _as;
		const npReal zRange = _zNear - _zFar;
		const npReal tanFOV = tanf(_fov / 2.0);

		m.m[0][0] = 1.0f / (tanFOV * ar);
		m.m[0][1] = 0.0f;
		m.m[0][2] = 0.0f;
		m.m[0][3] = 0.0f;

		m.m[1][0] = 0.0f;
		m.m[1][1] = 1.0f / tanFOV;
		m.m[1][2] = 0.0f;
		m.m[1][3] = 0.0f;

		m.m[2][0] = 0.0f;
		m.m[2][1] = 0.0f;
		m.m[2][2] = -(_zFar + _zNear) / zRange;
		m.m[2][3] = -(2.0f * _zFar * _zNear) / zRange;

		m.m[3][0] = 0.0f;
		m.m[3][1] = 0.0f;
		m.m[3][2] = -1.0f;
		m.m[3][3] = 0.0f;

		return m;
	}

	void npTransform::setScale(const npReal& _x, const npReal& _y, const npReal& _z) {
		m_scale = npVector3<npReal>(_x, _y, _z);
	}

	void npTransform::setTranslation(const npReal& _x, const npReal& _y, const npReal& _z) {
		m_translation = npVector3<npReal>(_x, _y, _z);
	}

	void npTransform::setRotation(const npReal& _alfaX, const npReal& _alfaY, const npReal& _alfaZ) {
		m_rotation = npVector3<npReal>(_alfaX, _alfaY, _alfaZ);
	}

	const npMatrix4 npTransform::getModelMatrix() {

		//TODO: Check flag if there was a change since the last calculation

		m_finalTransformation = getTranslationsMatrix(m_translation.x, m_translation.y, m_translation.z)
			* getRotationMatrix(m_rotation.x, m_rotation.y, m_rotation.z)
			* getScaleMatrix(m_scale.x, m_scale.y, m_scale.z);
		return m_finalTransformation;
	}

	//TODO test funkcijo
	npMatrix4 npTransform::lookAt(const npVector3<npReal>& eye, const npVector3<npReal>& center, const npVector3<npReal>& up) {
		npMatrix4 lookAt;

		npVector3<npReal> w = eye - center; w.normalize();
		npVector3<npReal> u = up % w; u.normalize();
		npVector3<npReal> v = w % u; v.normalize();

		auto bb = eye;

		lookAt.m[0][0] = u.x;
		lookAt.m[0][1] = u.y;
		lookAt.m[0][2] = u.z;
		lookAt.m[0][3] = u * bb * (-1);

		lookAt.m[1][0] = v.x;
		lookAt.m[1][1] = v.y;
		lookAt.m[1][2] = v.z;
		lookAt.m[1][3] = v * bb * (-1);

		lookAt.m[2][0] = w.x;
		lookAt.m[2][1] = w.y;
		lookAt.m[2][2] = w.z;
		lookAt.m[2][3] = w * bb * (-1);
		
		return lookAt;
	}

	npMatrix3 npTransform::rotate(const npReal& _angle, const npVector3<npReal>& axis) {
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

	npVector3<npReal> npTransform::multiplyVectorAndMatrix(const npVector3<npReal>& _vector, const npMatrix3& _matrix) {
		return npVector3<npReal>(
			_vector.x * _matrix.m[0][0] + _vector.y * _matrix.m[1][0] + _vector.z * _matrix.m[2][0],
			_vector.x * _matrix.m[0][1] + _vector.y * _matrix.m[1][1] + _vector.z * _matrix.m[2][1],
			_vector.x * _matrix.m[0][2] + _vector.y * _matrix.m[2][1] + _vector.z * _matrix.m[2][2]);
	}

	npTransform::npTransform() {
		m_scale = npVector3<npReal>(1.0f, 1.0f, 1.0f);
		m_translation = npVector3<npReal>(0, 0, 0);
		m_rotation = npVector3<npReal>(0, 0, 0);
	}

	npTransform::~npTransform()
	{
	}
}