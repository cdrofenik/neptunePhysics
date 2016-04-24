
#include "neptunePhysics/math/npMatrix4.hpp"

// GLM
#include <glm/glm.hpp>

using namespace NeptunePhysics;

//glm::mat4 ConvertNpMatrixToGlm(const npMatrix4& _matrix4) {
//
//	npMatrix4 _inputMatrix = _matrix4;
//	_inputMatrix = _inputMatrix.Transpose();
//
//	return glm::mat4(
//		_inputMatrix.m[0][0], _inputMatrix.m[0][1], _inputMatrix.m[0][2], _inputMatrix.m[0][3],
//		_inputMatrix.m[1][0], _inputMatrix.m[1][1], _inputMatrix.m[1][2], _inputMatrix.m[1][3],
//		_inputMatrix.m[2][0], _inputMatrix.m[2][1], _inputMatrix.m[2][2], _inputMatrix.m[2][3],
//		_inputMatrix.m[3][0], _inputMatrix.m[3][1], _inputMatrix.m[3][2], _inputMatrix.m[3][3]);
//}

glm::mat4 GenerateMatrix4ForPosition(const npReal& v1, const npReal& v2, const npReal& v3) {

	return glm::mat4(
		0.1, 0, 0, v1,
		0, 0.1, 0, v2,
		0, 0, 0.1, v3,
		0, 0, 0, 1);
}