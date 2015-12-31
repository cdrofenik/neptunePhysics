#include "gtest\gtest.h"

#include "neptunePhysics/math/npPrecision.hpp"
#include "neptunePhysics/math/npMatrix3.hpp"

using namespace NeptunePhysics;

TEST(npMatrxTest, NPMATRIX3_VARIABLE_CONSTRUCTOR) {

	npMatrix3 a(1);

	EXPECT_FLOAT_EQ(a.m[0][0], 1);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], 0);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 1);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);

	EXPECT_FLOAT_EQ(a.m[2][0], 0);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], 1);

	a = npMatrix3(5);

	EXPECT_FLOAT_EQ(a.m[0][0], 5);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], 0);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 5);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);

	EXPECT_FLOAT_EQ(a.m[2][0], 0);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], 5);
}

TEST(npMatrxTest, NPMATRIX3_VALUES_CONSTRUCTOR) {

	npMatrix3 a(1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);

	EXPECT_FLOAT_EQ(a.m[0][0], 1);
	EXPECT_FLOAT_EQ(a.m[0][1], 2);
	EXPECT_FLOAT_EQ(a.m[0][2], 3);

	EXPECT_FLOAT_EQ(a.m[1][0], 4);
	EXPECT_FLOAT_EQ(a.m[1][1], 5);
	EXPECT_FLOAT_EQ(a.m[1][2], 6);

	EXPECT_FLOAT_EQ(a.m[2][0], 7);
	EXPECT_FLOAT_EQ(a.m[2][1], 8);
	EXPECT_FLOAT_EQ(a.m[2][2], 9);
}

TEST(npMatrxTest, NPMATRIX3_SUM) {

	npMatrix3 c(1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);

	npMatrix3 b(2);

	npMatrix3 a = c + b;

	EXPECT_FLOAT_EQ(a.m[0][0], 3);
	EXPECT_FLOAT_EQ(a.m[0][1], 2);
	EXPECT_FLOAT_EQ(a.m[0][2], 3);

	EXPECT_FLOAT_EQ(a.m[1][0], 4);
	EXPECT_FLOAT_EQ(a.m[1][1], 7);
	EXPECT_FLOAT_EQ(a.m[1][2], 6);

	EXPECT_FLOAT_EQ(a.m[2][0], 7);
	EXPECT_FLOAT_EQ(a.m[2][1], 8);
	EXPECT_FLOAT_EQ(a.m[2][2], 11);

	a = b + c;

	EXPECT_FLOAT_EQ(a.m[0][0], 3);
	EXPECT_FLOAT_EQ(a.m[0][1], 2);
	EXPECT_FLOAT_EQ(a.m[0][2], 3);

	EXPECT_FLOAT_EQ(a.m[1][0], 4);
	EXPECT_FLOAT_EQ(a.m[1][1], 7);
	EXPECT_FLOAT_EQ(a.m[1][2], 6);

	EXPECT_FLOAT_EQ(a.m[2][0], 7);
	EXPECT_FLOAT_EQ(a.m[2][1], 8);
	EXPECT_FLOAT_EQ(a.m[2][2], 11);
}

TEST(npMatrixText, NPMATRIX3_INIT) {
	npMatrix3 a(1);
	a.Init(2);

	EXPECT_FLOAT_EQ(a.m[0][0], 2);
	EXPECT_FLOAT_EQ(a.m[0][1], 2);
	EXPECT_FLOAT_EQ(a.m[0][2], 2);

	EXPECT_FLOAT_EQ(a.m[1][0], 2);
	EXPECT_FLOAT_EQ(a.m[1][1], 2);
	EXPECT_FLOAT_EQ(a.m[1][2], 2);

	EXPECT_FLOAT_EQ(a.m[2][0], 2);
	EXPECT_FLOAT_EQ(a.m[2][1], 2);
	EXPECT_FLOAT_EQ(a.m[2][2], 2);
}

TEST(npMatrxTest, NPMATRIX3_MULTIPLICATION) {

	npMatrix3 a(1), b, c;
	b.Init(3);
	c.Init(1);
	a = c * b;

	EXPECT_FLOAT_EQ(a.m[0][0], 9);
	EXPECT_FLOAT_EQ(a.m[0][1], 9);
	EXPECT_FLOAT_EQ(a.m[0][2], 9);

	EXPECT_FLOAT_EQ(a.m[1][0], 9);
	EXPECT_FLOAT_EQ(a.m[1][1], 9);
	EXPECT_FLOAT_EQ(a.m[1][2], 9);

	EXPECT_FLOAT_EQ(a.m[2][0], 9);
	EXPECT_FLOAT_EQ(a.m[2][1], 9);
	EXPECT_FLOAT_EQ(a.m[2][2], 9);
}

TEST(npMatrxTest, NPMATRIX3_SCALAR_MULTIPLICATION) {

	npMatrix3 a(3);
	a = a * 5.0F;

	EXPECT_FLOAT_EQ(a.m[0][0], 15);
	EXPECT_FLOAT_EQ(a.m[0][1], 0);
	EXPECT_FLOAT_EQ(a.m[0][2], 0);

	EXPECT_FLOAT_EQ(a.m[1][0], 0);
	EXPECT_FLOAT_EQ(a.m[1][1], 15);
	EXPECT_FLOAT_EQ(a.m[1][2], 0);

	EXPECT_FLOAT_EQ(a.m[2][0], 0);
	EXPECT_FLOAT_EQ(a.m[2][1], 0);
	EXPECT_FLOAT_EQ(a.m[2][2], 15);
}

TEST(npMatrixTest, MATRIX_VECTOR_MULTIPLICATION) {

	npMatrix3 a(1);
	a.Init(1);

	EXPECT_FLOAT_EQ(a.m[0][0], 1);
	EXPECT_FLOAT_EQ(a.m[0][1], 1);
	EXPECT_FLOAT_EQ(a.m[0][2], 1);

	EXPECT_FLOAT_EQ(a.m[1][0], 1);
	EXPECT_FLOAT_EQ(a.m[1][1], 1);
	EXPECT_FLOAT_EQ(a.m[1][2], 1);

	EXPECT_FLOAT_EQ(a.m[2][0], 1);
	EXPECT_FLOAT_EQ(a.m[2][1], 1);
	EXPECT_FLOAT_EQ(a.m[2][2], 1);

	npVector3 b(3.0f, 2.0f, 5.0f);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 5);

	auto c = a * b;

	EXPECT_FLOAT_EQ(c.x, 10);
	EXPECT_FLOAT_EQ(c.y, 10);
	EXPECT_FLOAT_EQ(c.z, 10);
}