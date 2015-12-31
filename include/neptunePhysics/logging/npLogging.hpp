//#ifndef NEPTUNE_NPLOGGING_H
//#define NEPTUNE_NPLOGGING_H

#include "math/npMatrix.h"
#include "math/npVector2.hpp"
#include "math/npVector3.hpp"

#include <iostream>

namespace NeptunePhysics {
#ifdef _DEBUG

	//Logging for normal C++ types (char, int, float)
	template<typename T> void Log_DEBUG(const char* _location, const char* _message, const T _value) {

		if (std::is_same<int, T>::value) {
			printf("DEBUG: [%s] %s: %d \n", _location, _message, _value);
		}
		else if (std::is_same<const char*, T>::value) {
			printf("DEBUG: [%s] %s: %s \n", _location, _message, _value);
		}
		else if (std::is_same<float, T>::value) {
			printf("DEBUG: [%s] %s: %f \n", _location, _message, _value);
		}
		else {
			//Called twice - first for generic function
			//printf("Typeid %s\n", typeid(_value).name());
		}
	}

	void Log_DEBUG(const char* _location, const char* _message, const npVector2<npReal>& _value) {
		printf("DEBUG: [%s] %s: (%f, %f) \n", _location, _message, _value.x, _value.y);
	}

	void Log_DEBUG(const char* _location, const char* _message, const npVector3& _value) {
		printf("DEBUG: [%s] %s: (%f, %f, %f) \n", _location, _message, _value.x, _value.y, _value.z);
	}

	void Log_DEBUG(const char* _location, const char* _message, const npMatrix3& _value) {
		printf("DEBUG: [%s] %s:\n(%f, %f, %f)\n(%f, %f, %f)\n(%f, %f, %f)\n", _location, _message, _value.m[0][0], _value.m[0][1], _value.m[0][2],
			_value.m[1][0], _value.m[1][1], _value.m[1][2], _value.m[2][0], _value.m[2][1], _value.m[2][2]);
	}

	void Log_DEBUG(const char* _location, const char* _message, const npMatrix4& _value) {
		printf("DEBUG: [%s] %s:\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n", _location, _message,
			_value.m[0][0], _value.m[0][1], _value.m[0][2], _value.m[0][3],
			_value.m[1][0], _value.m[1][1], _value.m[1][2], _value.m[1][3],
			_value.m[2][0], _value.m[2][1], _value.m[2][2], _value.m[2][3],
			_value.m[3][0], _value.m[3][1], _value.m[3][2], _value.m[3][3]);
	}
#endif
}
//#endif
