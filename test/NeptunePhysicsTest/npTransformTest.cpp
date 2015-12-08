#include "gtest\gtest.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "../NeptunePhysics/npPrecision.h"
#include "../NeptunePhysics/npTransform.h"

#include <iostream>

using namespace NeptunePhysics;

TEST(npTransformTest, SCALE) {

	npReal Scale = 5.0f;

	npTransform p;
	p.setScale(5.0f, 1.0f, 5.0f);

	npMatrix4 a = p.getModelMatrix();

	EXPECT_FLOAT_EQ(a.m[0][0], 5);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], 0);
	EXPECT_FLOAT_EQ(a.m[0][3], 0);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 1);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);
	EXPECT_FLOAT_EQ(a.m[1][3], 0);

	EXPECT_FLOAT_EQ(a.m[2][0], 0);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], 5);
	EXPECT_FLOAT_EQ(a.m[2][3], 0);

	EXPECT_FLOAT_EQ(a.m[3][0], 0);
	EXPECT_FLOAT_EQ(a.m[3][1], 0);
	EXPECT_FLOAT_EQ(a.m[3][2], 0);
	EXPECT_FLOAT_EQ(a.m[3][3], 1);
}

TEST(npTransformationPipelineTest, TRANSLATION) {

	npReal Scale = 5.0f;

	npTransform p;
	p.setScale(1.0f, 2.0f, 1.0f);
	p.setTranslation(5.0f, 3.0f, 0.0f);
	
	npMatrix4 a = p.getModelMatrix();

	EXPECT_FLOAT_EQ(a.m[0][0], 1);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], 0);
	EXPECT_FLOAT_EQ(a.m[0][3], 5);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 2);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);
	EXPECT_FLOAT_EQ(a.m[1][3], 3);

	EXPECT_FLOAT_EQ(a.m[2][0], 0);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], 1);
	EXPECT_FLOAT_EQ(a.m[2][3], 0);

	EXPECT_FLOAT_EQ(a.m[3][0], 0);
	EXPECT_FLOAT_EQ(a.m[3][1], 0);
	EXPECT_FLOAT_EQ(a.m[3][2], 0);
	EXPECT_FLOAT_EQ(a.m[3][3], 1);

}

TEST(npTransformationPipelineTest, ROTATION) {
	npTransform p;
	p.setRotation(0.0f, 90.0f, 0.0f);

	npMatrix4 a = p.getModelMatrix();

	EXPECT_FLOAT_EQ(a.m[0][0], -0.448073626f);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], -0.893996656f);
	EXPECT_FLOAT_EQ(a.m[0][3], 0);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 1);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);
	EXPECT_FLOAT_EQ(a.m[1][3], 0);

	EXPECT_FLOAT_EQ(a.m[2][0], 0.893996656f);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], -0.448073626f);
	EXPECT_FLOAT_EQ(a.m[2][3], 0);

	EXPECT_FLOAT_EQ(a.m[3][0], 0);
	EXPECT_FLOAT_EQ(a.m[3][1], 0);
	EXPECT_FLOAT_EQ(a.m[3][2], 0);
	EXPECT_FLOAT_EQ(a.m[3][3], 1);


	p.setRotation(0.0f, 0.0f, 90.0f);
	npMatrix4 b = p.getModelMatrix();

	EXPECT_FLOAT_EQ(b.m[0][0], -0.448073626f);
	EXPECT_FLOAT_EQ(b.m[0][1], -0.893996656f);
	EXPECT_FLOAT_EQ(b.m[0][2], 0);
	EXPECT_FLOAT_EQ(b.m[0][3], 0);

	EXPECT_FLOAT_EQ(b.m[1][0], 0.893996656f);
	EXPECT_FLOAT_EQ(b.m[1][1], -0.448073626f);
	EXPECT_FLOAT_EQ(b.m[1][2], 0);
	EXPECT_FLOAT_EQ(b.m[1][3], 0);

	EXPECT_FLOAT_EQ(b.m[2][0], 0);
	EXPECT_FLOAT_EQ(b.m[2][1], 0);
	EXPECT_FLOAT_EQ(b.m[2][2], 1);
	EXPECT_FLOAT_EQ(b.m[2][3], 0);

	EXPECT_FLOAT_EQ(b.m[3][0], 0);
	EXPECT_FLOAT_EQ(b.m[3][1], 0);
	EXPECT_FLOAT_EQ(b.m[3][2], 0);
	EXPECT_FLOAT_EQ(b.m[3][3], 1);

	//TODO: Add test for x axis
}

TEST(npTransformationPipelineTest, PROJECTION_MATRIX) {

	//TODO: Preveri to z glm::perspective
	npMatrix4 a = npTransform::getProjectionMatrix(1024.0f / 768.0f, 0.1f, 100.0f, 45.0f);

	EXPECT_FLOAT_EQ(a.m[0][0], 1.34444320);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], 0);
	EXPECT_FLOAT_EQ(a.m[0][3], 0);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 1.79259098);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);
	EXPECT_FLOAT_EQ(a.m[1][3], 0);

	EXPECT_FLOAT_EQ(a.m[2][0], 0);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], 1.00200200);
	EXPECT_FLOAT_EQ(a.m[2][3], 0.200200200);

	EXPECT_FLOAT_EQ(a.m[3][0], 0);
	EXPECT_FLOAT_EQ(a.m[3][1], 0);
	EXPECT_FLOAT_EQ(a.m[3][2], -1);
	EXPECT_FLOAT_EQ(a.m[3][3], 0);
}

TEST(npTransformTest, multiplyVectorAndMatrixTest) {

	npMatrix3 a(1);
	a.init(1);

	EXPECT_FLOAT_EQ(a.m[0][0], 1);
	EXPECT_FLOAT_EQ(a.m[0][1], 1);
	EXPECT_FLOAT_EQ(a.m[0][2], 1);

	EXPECT_FLOAT_EQ(a.m[1][0], 1);
	EXPECT_FLOAT_EQ(a.m[1][1], 1);
	EXPECT_FLOAT_EQ(a.m[1][2], 1);

	EXPECT_FLOAT_EQ(a.m[2][0], 1);
	EXPECT_FLOAT_EQ(a.m[2][1], 1);
	EXPECT_FLOAT_EQ(a.m[2][2], 1);

	npVector3<npReal> b(3.0f, 2.0f, 5.0f);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 5);

	npVector3<npReal> c = npTransform::multiplyVectorAndMatrix(b, a);

	EXPECT_FLOAT_EQ(c.x, 10);
	EXPECT_FLOAT_EQ(c.y, 10);
	EXPECT_FLOAT_EQ(c.z, 10);
}

TEST(npTransformTest, lookAtTest) {

	glm::vec3 position = glm::vec3(-2, -2, 6);
	glm::vec3 direction = glm::vec3(0, 0.4, 1);
	glm::vec3 _up = glm::vec3(0, 1, 0);
	glm::mat4 result = glm::lookAt(position, direction, _up);
	result = glm::transpose(result);

	auto eye = npVector3<npReal>(-2.0f, -2.0f, 6.0f);
	auto target = npVector3<npReal>(0, 0.4, 1);
	auto up = npVector3<npReal>(0, 1, 0);
	auto a = npTransform::lookAt(eye, target, up);

	EXPECT_FLOAT_EQ(a.m[0][0], result[0][0]);
	EXPECT_FLOAT_EQ(a.m[0][1], result[0][1]);
	EXPECT_FLOAT_EQ(a.m[0][2], result[0][2]);
	EXPECT_FLOAT_EQ(a.m[0][3], result[0][3]);

	EXPECT_FLOAT_EQ(a.m[1][0], result[1][0]);
	EXPECT_FLOAT_EQ(a.m[1][1], result[1][1]);
	EXPECT_FLOAT_EQ(a.m[1][2], result[1][2]);
	EXPECT_FLOAT_EQ(a.m[1][3], result[1][3]);

	EXPECT_FLOAT_EQ(a.m[2][0], result[2][0]);
	EXPECT_FLOAT_EQ(a.m[2][1], result[2][1]);
	EXPECT_FLOAT_EQ(a.m[2][2], result[2][2]);
	EXPECT_FLOAT_EQ(a.m[2][3], result[2][3]);

	EXPECT_FLOAT_EQ(a.m[3][0], result[3][0]);
	EXPECT_FLOAT_EQ(a.m[3][1], result[3][1]);
	EXPECT_FLOAT_EQ(a.m[3][2], result[3][2]);
	EXPECT_FLOAT_EQ(a.m[3][3], result[3][3]);
}

TEST(npTransformTest, perspectiveProjectionTest) {
	/*glm::mat4 perspectiveMatrix = glm::perspective(45.0f, 1024.0f/768.0f, 0.1f, 100.0f);
	glm::mat4 result = glm::transpose(perspectiveMatrix);

	auto a = npTransform::getProjectionMatrix(1024 / (float)768.0f, 0.1f, 100.0f, 45.0f);

	EXPECT_FLOAT_EQ(a.m[0][0], result[0][0]);
	EXPECT_FLOAT_EQ(a.m[0][1], result[0][1]);
	EXPECT_FLOAT_EQ(a.m[0][2], result[0][2]);
	EXPECT_FLOAT_EQ(a.m[0][3], result[0][3]);

	EXPECT_FLOAT_EQ(a.m[1][0], result[1][0]);
	EXPECT_FLOAT_EQ(a.m[1][1], result[1][1]);
	EXPECT_FLOAT_EQ(a.m[1][2], result[1][2]);
	EXPECT_FLOAT_EQ(a.m[1][3], result[1][3]);

	EXPECT_FLOAT_EQ(a.m[2][0], result[2][0]);
	EXPECT_FLOAT_EQ(a.m[2][1], result[2][1]);
	EXPECT_FLOAT_EQ(a.m[2][2], result[2][2]);
	EXPECT_FLOAT_EQ(a.m[2][3], result[2][3]);

	EXPECT_FLOAT_EQ(a.m[3][0], result[3][0]);
	EXPECT_FLOAT_EQ(a.m[3][1], result[3][1]);
	EXPECT_FLOAT_EQ(a.m[3][2], result[3][2]);
	EXPECT_FLOAT_EQ(a.m[3][3], result[3][3]);*/

	//npTransform::getProjectionMatrix(WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f, 45.0f);
}