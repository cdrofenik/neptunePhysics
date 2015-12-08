#ifndef NEPTUNE_NPTRANSFORMATIONMATRIX_H
#define NEPTUNE_NPTRANSFORMATIONMATRIX_H

#include "npVector.h"
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
		npTransform();
		~npTransform();

		static npMatrix4 getTranslationsMatrix(const npReal& _x, const npReal& _y, const npReal& _z);
		static npMatrix4 getScaleMatrix(const npReal& _x, const npReal& _y, const npReal& _z);
		static npMatrix4 getRotationMatrix(const npReal& _alfaX, const npReal& _alfaY, const npReal& _alfaZ);
		static npMatrix4 getProjectionMatrix(const npReal& _as, const npReal& _zNear, const npReal& _zFar, const npReal& _fov);

		void setScale(const npReal& _x, const npReal& _y, const npReal& _z);
		void setTranslation(const npReal& _x, const npReal& _y, const npReal& _z);
		void setRotation(const npReal& _alfaX, const npReal& _alfaY, const npReal& _alfaZ);

		/*
		Returns Model matrix which can be manipulated through setScale, setTranslation and setRotation
		*/
		const npMatrix4 getModelMatrix();

		/*
		Generates lookAt matrix

		gluLookAt reference http://stackoverflow.com/questions/19740463/lookat-function-im-going-crazy
		*/
		static npMatrix4 lookAt(const npVector3<npReal>& position, const npVector3<npReal>& direction, const npVector3<npReal>& up);

		static npMatrix3 rotate(const npReal& _angle, const npVector3<npReal>& axis);

		static npVector3<npReal> multiplyVectorAndMatrix(const npVector3<npReal>& _vector, const npMatrix3& _matrix);

	private:

		npVector3<npReal> m_scale;
		npVector3<npReal> m_rotation;
		npVector3<npReal> m_translation;
		npMatrix4 m_finalTransformation;
	};
}

#endif