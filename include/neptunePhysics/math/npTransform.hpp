#ifndef NEPTUNE_NPTRANSFORM_H
#define NEPTUNE_NPTRANSFORM_H

#include "npVector3.hpp"
#include "npMatrix4.hpp"

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
		npTransform() { m_scale = npVector3r(1.0f, 1.0f, 1.0f); m_origin = npVector3r(0.0f, 0.0f, 0.0f); m_translation = npVector3r(0.0f, 0.0f, 0.0f); }
		~npTransform() { }

		void setScale(const npReal& _x, const npReal& _y, const npReal& _z)  { m_scale = npVector3r(_x, _y, _z); m_wasChanged = true; }
		void setOrigin(const npReal& _x, const npReal& _y, const npReal& _z) { m_origin = npVector3r(_x, _y, _z); m_wasChanged = true; }
		void setRotation(const npReal& _alfaX, const npReal& _alfaY, const npReal& _alfaZ) { m_rotation = npVector3r(_alfaX, _alfaY, _alfaZ); m_wasChanged = true; }
		void setTranslation(const npReal& _x, const npReal& _y, const npReal& _z) { m_translation = npVector3r(_x, _y, _z); m_wasChanged = true; }

		/*
		Returns Model matrix which can be manipulated through setScale, setOrigin and setRotation
		*/
		const npMatrix4 getTransformMatrix() {
			if (m_wasChanged) {
				m_finalTransformation = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
				m_wasChanged = false;
			}
			
			return m_finalTransformation;
		}

	private:
		bool m_wasChanged = false;
		npVector3r m_scale;
		npVector3r m_rotation;
		npVector3r m_origin;
		npVector3r m_translation;
		npMatrix4 m_finalTransformation;

		npMatrix4 getTranslationMatrix() {
			npMatrix4 v;
			v.m[0] = 1.0f;	v.m[1] = 0.0f;	v.m[2] = 0.0f;	v.m[3] = m_origin.x + m_translation.x;
			v.m[4] = 0.0f;	v.m[5] = 1.0f;	v.m[6] = 0.0f;	v.m[7] = m_origin.y + m_translation.y;
			v.m[8] = 0.0f;	v.m[9] = 0.0f;	v.m[10] = 1.0f;	v.m[11] = m_origin.z + m_translation.z;
			v.m[12] = 0.0f;	v.m[13] = 0.0f;	v.m[14] = 0.0f;	v.m[15] = 1.0f;

			return v;
		}

		npMatrix4 getScaleMatrix() {
			npMatrix4 v;
			v.m[0] = m_scale.x;	v.m[1] = 0.0f;		v.m[2] = 0.0f;		v.m[3] = 0.0f;
			v.m[4] = 0.0f;		v.m[5] = m_scale.y;	v.m[6] = 0.0f;		v.m[7] = 0.0f;
			v.m[8] = 0.0f;		v.m[9] = 0.0f;		v.m[10] = m_scale.z;	v.m[11] = 0.0f;
			v.m[12] = 0.0f;		v.m[13] = 0.0f;		v.m[14] = 0.0f;		v.m[15] = 1.0f;
			return v;
		}

		npMatrix4 getRotationMatrix() {
			npMatrix4 v;

			//Rotation around z
			npMatrix4 aroundZ;
			aroundZ.m[0] = cosf(m_rotation.z);	aroundZ.m[1] = -sinf(m_rotation.z);	aroundZ.m[2] = 0.0f;	aroundZ.m[3] = 0.0f;
			aroundZ.m[4] = sinf(m_rotation.z);	aroundZ.m[5] = cosf(m_rotation.z);	aroundZ.m[6] = 0.0f;	aroundZ.m[7] = 0.0f;
			aroundZ.m[8] = 0.0f;				aroundZ.m[9] = 0.0f;				aroundZ.m[10] = 1.0f;	aroundZ.m[11] = 0.0f;
			aroundZ.m[12] = 0.0f;				aroundZ.m[13] = 0.0f;				aroundZ.m[14] = 0.0f;	aroundZ.m[15] = 1.0f;

			//Rotation around y
			npMatrix4 aroundY;
			aroundY.m[0] = cosf(m_rotation.y);	aroundY.m[1] = 0.0f;	aroundY.m[2] = -sinf(m_rotation.y);	aroundY.m[3] = 0.0f;
			aroundY.m[4] = 0.0f;				aroundY.m[5] = 1.0f;	aroundY.m[6] = 0.0f;				aroundY.m[7] = 0.0f;
			aroundY.m[8] = sinf(m_rotation.y);	aroundY.m[9] = 0.0f;	aroundY.m[10] = cosf(m_rotation.y);	aroundY.m[11] = 0.0f;
			aroundY.m[12] = 0.0f;				aroundY.m[13] = 0.0f;	aroundY.m[14] = 0.0f;				aroundY.m[15] = 1.0f;

			//Rotation around x
			npMatrix4 aroundX;
			aroundX.m[0] = 1.0f;	aroundX.m[1] = 0.0f;				aroundX.m[2] = 0.0f;				aroundX.m[3] = 0.0f;
			aroundX.m[4] = 0.0f;	aroundX.m[5] = cosf(m_rotation.x);	aroundX.m[6] = sinf(m_rotation.x);	aroundX.m[7] = 0.0f;
			aroundX.m[8] = 0.0f;	aroundX.m[9] = -sinf(m_rotation.x);	aroundX.m[10] = cosf(m_rotation.x);	aroundX.m[11] = 0.0f;
			aroundX.m[12] = 0.0f;	aroundX.m[13] = 0.0f;				aroundX.m[14] = 0.0f;				aroundX.m[15] = 1.0f;

			v = aroundZ * aroundY * aroundX;
			return v;
		}
	};
}

#endif