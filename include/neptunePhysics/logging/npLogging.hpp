#ifndef NEPTUNE_NPLOGGING_H
#define NEPTUNE_NPLOGGING_H

#include "math/npMatrix4.hpp"
#include "math/npVector2.hpp"
#include "math/npVector3.hpp"

#include <iostream>

namespace NeptunePhysics {
#ifdef _DEBUG

	//Logging for normal C++ types (char, int, float)
	//template<typename T> void Log_DEBUG(const char* _location, const char* _message, const T _value) {

	//	if (std::is_same<int, T>::value) {
	//		printf("DEBUG: [%s] %s: %d \n", _location, _message, _value);
	//	}
	//	else if (std::is_same<const char*, T>::value) {
	//		printf("DEBUG: [%s] %s: %s \n", _location, _message, _value);
	//	}
	//	else if (std::is_same<float, T>::value) {
	//		printf("DEBUG: [%s] %s: %f \n", _location, _message, _value);
	//	}
	//	else {
	//		//Called twice - first for generic function
	//		//printf("Typeid %s\n", typeid(_value).name());
	//	}
	//}

	void Log_DEBUG(const char* _location, const char* _message, const npVector2<npReal>& _value) {
		printf("DEBUG: [%s] %s: (%f, %f) \n", _location, _message, _value.x, _value.y);
	}

	void Log_DEBUG(const char* _location, const char* _message, const npVector3r& _value) {
		printf("DEBUG: [%s] %s: (%f, %f, %f) \n", _location, _message, _value.x, _value.y, _value.z);
	}

	void Log_DEBUG(const char* _location, const char* _message, const npMatrix3& _value) {
		printf("DEBUG: [%s] %s:\n(%f, %f, %f)\n(%f, %f, %f)\n(%f, %f, %f)\n", _location, _message, _value.m[0], _value.m[1], _value.m[2],
			_value.m[3], _value.m[3], _value.m[4], _value.m[5], _value.m[7], _value.m[8]);
	}

	void Log_DEBUG(const char* _location, const char* _message, const npMatrix4& _value) {
		printf("DEBUG: [%s] %s:\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n(%f, %f, %f, %f)\n", _location, _message,
			_value.m[0], _value.m[1], _value.m[2], _value.m[3],
			_value.m[4], _value.m[5], _value.m[6], _value.m[7],
			_value.m[8], _value.m[9], _value.m[10], _value.m[11],
			_value.m[12], _value.m[13], _value.m[14], _value.m[15]);
	}
#endif
}
#endif
