
#include "neptunePhysics/math/npMatrix4.hpp"

// GLM
#include <glm/glm.hpp>

using namespace NeptunePhysics;

glm::mat4 ConvertNpMatrixToGlm(const npMatrix4& _matrix4) {

	npMatrix4 _inputMatrix = _matrix4;
	_inputMatrix = _inputMatrix.Transpose();

	return glm::mat4(
		_inputMatrix.m[0][0], _inputMatrix.m[0][1], _inputMatrix.m[0][2], _inputMatrix.m[0][3],
		_inputMatrix.m[1][0], _inputMatrix.m[1][1], _inputMatrix.m[1][2], _inputMatrix.m[1][3],
		_inputMatrix.m[2][0], _inputMatrix.m[2][1], _inputMatrix.m[2][2], _inputMatrix.m[2][3],
		_inputMatrix.m[3][0], _inputMatrix.m[3][1], _inputMatrix.m[3][2], _inputMatrix.m[3][3]);
}
