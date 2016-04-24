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

	EXPECT_FLOAT_EQ(a.m[0], 5);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);
	EXPECT_FLOAT_EQ(a.m[3], 0);

	EXPECT_FLOAT_EQ(a.m[4], 0);
	EXPECT_FLOAT_EQ(a.m[5], 1);
	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 0);
	EXPECT_FLOAT_EQ(a.m[10], 5);
	EXPECT_FLOAT_EQ(a.m[11], 0);

	EXPECT_FLOAT_EQ(a.m[12], 0);
	EXPECT_FLOAT_EQ(a.m[13], 0);
	EXPECT_FLOAT_EQ(a.m[14], 0);
	EXPECT_FLOAT_EQ(a.m[15], 1);
}

TEST(npTransformationPipelineTest, TRANSLATION) {

	npReal Scale = 5.0f;

	npTransform p;
	p.setScale(1.0f, 2.0f, 1.0f);
	p.setOrigin(5.0f, 3.0f, 0.0f);
	
	npMatrix4 a = p.getTransformMatrix();

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);
	EXPECT_FLOAT_EQ(a.m[3], 5);

	EXPECT_FLOAT_EQ(a.m[4], 0);
	EXPECT_FLOAT_EQ(a.m[5], 2);
	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 3);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 0);
	EXPECT_FLOAT_EQ(a.m[10], 1);
	EXPECT_FLOAT_EQ(a.m[11], 0);

	EXPECT_FLOAT_EQ(a.m[12], 0);
	EXPECT_FLOAT_EQ(a.m[13], 0);
	EXPECT_FLOAT_EQ(a.m[14], 0);
	EXPECT_FLOAT_EQ(a.m[15], 1);

}

TEST(npTransformationPipelineTest, ROTATION) {
	npTransform p;
	p.setRotation(0.0f, 90.0f, 0.0f);

	npMatrix4 a = p.getTransformMatrix();

	EXPECT_FLOAT_EQ(a.m[0], -0.448073626f);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], -0.893996656f);
	EXPECT_FLOAT_EQ(a.m[3], 0);

	EXPECT_FLOAT_EQ(a.m[4], 0);
	EXPECT_FLOAT_EQ(a.m[5], 1);
	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);

	EXPECT_FLOAT_EQ(a.m[8], 0.893996656f);
	EXPECT_FLOAT_EQ(a.m[9], 0);
	EXPECT_FLOAT_EQ(a.m[10], -0.448073626f);
	EXPECT_FLOAT_EQ(a.m[11], 0);

	EXPECT_FLOAT_EQ(a.m[12], 0);
	EXPECT_FLOAT_EQ(a.m[13], 0);
	EXPECT_FLOAT_EQ(a.m[14], 0);
	EXPECT_FLOAT_EQ(a.m[15], 1);

	p.setRotation(0.0f, 0.0f, 90.0f);
	npMatrix4 b = p.getTransformMatrix();

	EXPECT_FLOAT_EQ(b.m[0], -0.448073626f);
	EXPECT_FLOAT_EQ(b.m[1], -0.893996656f);
	EXPECT_FLOAT_EQ(b.m[2], 0);
	EXPECT_FLOAT_EQ(b.m[3], 0);

	EXPECT_FLOAT_EQ(b.m[4], 0.893996656f);
	EXPECT_FLOAT_EQ(b.m[5], -0.448073626f);
	EXPECT_FLOAT_EQ(b.m[6], 0);
	EXPECT_FLOAT_EQ(b.m[7], 0);

	EXPECT_FLOAT_EQ(b.m[8], 0);
	EXPECT_FLOAT_EQ(b.m[9], 0);
	EXPECT_FLOAT_EQ(b.m[10], 1);
	EXPECT_FLOAT_EQ(b.m[11], 0);

	EXPECT_FLOAT_EQ(b.m[12], 0);
	EXPECT_FLOAT_EQ(b.m[13], 0);
	EXPECT_FLOAT_EQ(b.m[14], 0);
	EXPECT_FLOAT_EQ(b.m[15], 1);
	//TODO: Add test for x axis
}