#include "gtest\gtest.h"

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "neptunePhysics/math/npPrecision.hpp"
#include "neptunePhysics/math/npTransform.hpp"

#include <iostream>

using namespace NeptunePhysics;

TEST(npTransformTest, SCALE) {

	npReal Scale = 5.0f;

	npTransform p;
	p.setScale(5.0f, 1.0f, 5.0f);

	npMatrix4 a = p.getTransformMatrix();

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
	p.setOrigin(5.0f, 3.0f, 0.0f);
	
	npMatrix4 a = p.getTransformMatrix();

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

	npMatrix4 a = p.getTransformMatrix();

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
	npMatrix4 b = p.getTransformMatrix();

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