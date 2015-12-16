#include "gtest\gtest.h"

#include "neptunePhysics/math/npPrecision.hpp"
#include "neptunePhysics/math/npMatrix4.hpp"

using namespace NeptunePhysics;

TEST(npMatrxTest, NPMATRIX4_VARIABLE_CONSTRUCTOR) {

	npMatrix4 a(3);

	EXPECT_FLOAT_EQ(a.m[0][0], 3);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], 0);
	EXPECT_FLOAT_EQ(a.m[0][3], 0);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 3);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);
	EXPECT_FLOAT_EQ(a.m[1][3], 0);

	EXPECT_FLOAT_EQ(a.m[2][0], 0);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], 3);
	EXPECT_FLOAT_EQ(a.m[2][3], 0);

	EXPECT_FLOAT_EQ(a.m[3][0], 0);
	EXPECT_FLOAT_EQ(a.m[3][1], 0);
	EXPECT_FLOAT_EQ(a.m[3][2], 0);
	EXPECT_FLOAT_EQ(a.m[3][3], 1);
}

TEST(npMatrxTest, NPMATRIX4_INIT) {

	npMatrix4 a;
	a.Init(5);

	EXPECT_FLOAT_EQ(a.m[0][0], 5);
	EXPECT_FLOAT_EQ(a.m[0][1], 5);
	EXPECT_FLOAT_EQ(a.m[0][2], 5);
	EXPECT_FLOAT_EQ(a.m[0][3], 5);

	EXPECT_FLOAT_EQ(a.m[1][0], 5);
	EXPECT_FLOAT_EQ(a.m[1][1], 5);
	EXPECT_FLOAT_EQ(a.m[1][2], 5);
	EXPECT_FLOAT_EQ(a.m[1][3], 5);

	EXPECT_FLOAT_EQ(a.m[2][0], 5);
	EXPECT_FLOAT_EQ(a.m[2][1], 5);
	EXPECT_FLOAT_EQ(a.m[2][2], 5);
	EXPECT_FLOAT_EQ(a.m[2][3], 5);

	EXPECT_FLOAT_EQ(a.m[3][0], 5);
	EXPECT_FLOAT_EQ(a.m[3][1], 5);
	EXPECT_FLOAT_EQ(a.m[3][2], 5);
	EXPECT_FLOAT_EQ(a.m[3][3], 5);
}

TEST(npMatrxTest, NPMATRIX4_MULTIPLICATION) {

	npMatrix4 c(1), b(3), a(1);
	c.Init(1);
	b.Init(3);
	a = c * b;

	EXPECT_FLOAT_EQ(a.m[0][0], 12);
	EXPECT_FLOAT_EQ(a.m[0][1], 12);
	EXPECT_FLOAT_EQ(a.m[0][2], 12);
	EXPECT_FLOAT_EQ(a.m[0][3], 12);

	EXPECT_FLOAT_EQ(a.m[1][0], 12);
	EXPECT_FLOAT_EQ(a.m[1][1], 12);
	EXPECT_FLOAT_EQ(a.m[1][2], 12);
	EXPECT_FLOAT_EQ(a.m[1][3], 12);

	EXPECT_FLOAT_EQ(a.m[2][0], 12);
	EXPECT_FLOAT_EQ(a.m[2][1], 12);
	EXPECT_FLOAT_EQ(a.m[2][2], 12);
	EXPECT_FLOAT_EQ(a.m[2][3], 12);

	EXPECT_FLOAT_EQ(a.m[3][0], 12);
	EXPECT_FLOAT_EQ(a.m[3][1], 12);
	EXPECT_FLOAT_EQ(a.m[3][2], 12);
	EXPECT_FLOAT_EQ(a.m[3][3], 12);
}