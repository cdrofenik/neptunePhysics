#ifndef NEPTUNE_NPTRANSFORM_H
#define NEPTUNE_NPTRANSFORM_H

#include "npVector3.hpp"
#include "npMatrix.h"

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
	
	class npTransform
	{
	public:
		npTransform() { m_scale = npVector3<npReal>(1.0f, 1.0f, 1.0f); m_origin = npVector3<npReal>(0.0f, 0.0f, 0.0f); }
		~npTransform() { }

		void setScale(const npReal& _x, const npReal& _y, const npReal& _z)  { m_scale = npVector3<npReal>(_x, _y, _z); m_wasChanged = true; }
		void setOrigin(const npReal& _x, const npReal& _y, const npReal& _z) { m_origin = npVector3<npReal>(_x, _y, _z); m_wasChanged = true; }
		void setRotation(const npReal& _alfaX, const npReal& _alfaY, const npReal& _alfaZ) { m_rotation = npVector3<npReal>(_alfaX, _alfaY, _alfaZ); m_wasChanged = true; }

		/*
		Returns Model matrix which can be manipulated through setScale, setOrigin and setRotation
		*/
		const npMatrix4 getTransformMatrix() {
			if (m_wasChanged) {
				m_finalTransformation = getOriginMatrix() * getRotationMatrix() * getScaleMatrix();
				m_wasChanged = false;
			}
			
			return m_finalTransformation;
		}

	private:
		bool m_wasChanged = false;
		npVector3<npReal> m_scale;
		npVector3<npReal> m_rotation;
		npVector3<npReal> m_origin;
		npMatrix4 m_finalTransformation;

		npMatrix4 getOriginMatrix() {
			npMatrix4 v;
			v.m[0][0] = 1.0f;	v.m[0][1] = 0.0f;   v.m[0][2] = 0.0f;   v.m[0][3] = m_origin.x;
			v.m[1][0] = 0.0f;   v.m[1][1] = 1.0f;   v.m[1][2] = 0.0f;   v.m[1][3] = m_origin.y;
			v.m[2][0] = 0.0f;   v.m[2][1] = 0.0f;   v.m[2][2] = 1.0f;   v.m[2][3] = m_origin.z;
			v.m[3][0] = 0.0f;   v.m[3][1] = 0.0f;   v.m[3][2] = 0.0f;   v.m[3][3] = 1.0f;

			return v;
		}

		npMatrix4 getScaleMatrix() {
			npMatrix4 v;
			v.m[0][0] = m_scale.x;	v.m[0][1] = 0.0f;		v.m[0][2] = 0.0f;		v.m[0][3] = 0.0f;
			v.m[1][0] = 0.0f;		v.m[1][1] = m_scale.y;	v.m[1][2] = 0.0f;		v.m[1][3] = 0.0f;
			v.m[2][0] = 0.0f;		v.m[2][1] = 0.0f;		v.m[2][2] = m_scale.z;	v.m[2][3] = 0.0f;
			v.m[3][0] = 0.0f;		v.m[3][1] = 0.0f;		v.m[3][2] = 0.0f;		v.m[3][3] = 1.0f;
			return v;
		}

		npMatrix4 getRotationMatrix() {
			npMatrix4 v;

			//Rotation around z
			npMatrix4 aroundZ;
			aroundZ.m[0][0] = cosf(m_rotation.z);	aroundZ.m[0][1] = -sinf(m_rotation.z);	aroundZ.m[0][2] = 0.0f; aroundZ.m[0][3] = 0.0f;
			aroundZ.m[1][0] = sinf(m_rotation.z);	aroundZ.m[1][1] = cosf(m_rotation.z);	aroundZ.m[1][2] = 0.0f; aroundZ.m[1][3] = 0.0f;
			aroundZ.m[2][0] = 0.0f;					aroundZ.m[2][1] = 0.0f;					aroundZ.m[2][2] = 1.0f; aroundZ.m[2][3] = 0.0f;
			aroundZ.m[3][0] = 0.0f;		    		aroundZ.m[3][1] = 0.0f;					aroundZ.m[3][2] = 0.0f; aroundZ.m[3][3] = 1.0f;

			//Rotation around y
			npMatrix4 aroundY;
			aroundY.m[0][0] = cosf(m_rotation.y);	aroundY.m[0][1] = 0.0f;			aroundY.m[0][2] = -sinf(m_rotation.y);	aroundY.m[0][3] = 0.0f;
			aroundY.m[1][0] = 0.0f;					aroundY.m[1][1] = 1.0f;			aroundY.m[1][2] = 0.0f;					aroundY.m[1][3] = 0.0f;
			aroundY.m[2][0] = sinf(m_rotation.y);	aroundY.m[2][1] = 0.0f;         aroundY.m[2][2] = cosf(m_rotation.y);	aroundY.m[2][3] = 0.0f;
			aroundY.m[3][0] = 0.0f;					aroundY.m[3][1] = 0.0f;         aroundY.m[3][2] = 0.0f;					aroundY.m[3][3] = 1.0f;

			//Rotation around x
			npMatrix4 aroundX;
			aroundX.m[0][0] = 1.0f; aroundX.m[0][1] = 0.0f;					aroundX.m[0][2] = 0.0f;					aroundX.m[0][3] = 0.0f;
			aroundX.m[1][0] = .0f;	aroundX.m[1][1] = cosf(m_rotation.x);	aroundX.m[1][2] = sinf(m_rotation.x);	aroundX.m[1][3] = 0.0f;
			aroundX.m[2][0] = 0.0f;	aroundX.m[2][1] = -sinf(m_rotation.x);	aroundX.m[2][2] = cosf(m_rotation.x);	aroundX.m[2][3] = 0.0f;
			aroundX.m[3][0] = 0.0f;	aroundX.m[3][1] = 0.0f;					aroundX.m[3][2] = 0.0f;					aroundX.m[3][3] = 1.0f;

			v = aroundZ * aroundY * aroundX;
			return v;
		}
	};
}

#endif