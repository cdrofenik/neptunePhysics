#ifndef NEPTUNE_NPQUARTERNION_H
#define NEPTUNE_NPQUARTERNION_H

#include "npVector3.hpp"
#include <math.h>

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

	class npQuarternion
	{
	public:
		union {
			struct {
				npReal r;
				npReal i;
				npReal j;
				npReal k;
			};

			npReal data[4];
		};

		npQuarternion(const npReal& _r = 0, const npReal& _i = 0,
			const npReal& _j = 0, const npReal& _k = 0) :
			r(_r), i(_i), j(_j), k(_k) {}

		void normalize()
		{
			npReal d = r*r + i*i + j*j + k*k;

			if (d == 0) {
				r = 1;
				return;
			}

			d = 1.0f / sqrt(d);
			r *= d;
			i *= d;
			j *= d;
			k *= d;
		}

		void operator*=(const npQuarternion& _multiplier)
		{
			npQuarternion result, q  = *this;
			result.r = q.r * _multiplier.r - q.i * _multiplier.i - q.j * _multiplier.j - q.k * _multiplier.k;
			result.i = q.r * _multiplier.i + q.i * _multiplier.r + q.j * _multiplier.k - q.k * _multiplier.j;
			result.j = q.r * _multiplier.j + q.j * _multiplier.r + q.k * _multiplier.i - q.i * _multiplier.k;
			result.k = q.r * _multiplier.k + q.k * _multiplier.r + q.i * _multiplier.j - q.j * _multiplier.i;
		
			*this = result;
		}

		void rotateByVector(const npVector3& _vector)
		{
			npQuarternion q(0, _vector.x, _vector.y, _vector.z);
			(*this) *= q;
		}

		void addScaledVector(const npVector3& _vector, const npReal& _scale)
		{
			npQuarternion q(0, _vector.x * _scale, _vector.y * _scale, _vector.z * _scale);
			q *= *this;
			r += q.r * (0.5f);
			i += q.i * (0.5f);
			j += q.j * (0.5f);
			k += q.k * (0.5f);
		}

	};
}

#endif