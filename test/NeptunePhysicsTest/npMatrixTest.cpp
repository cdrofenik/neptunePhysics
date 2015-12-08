#include "gtest\gtest.h"

#include "../NeptunePhysics/npPrecision.h"
#include "../NeptunePhysics/npMatrix.h"

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
	a.init(2);

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
	b.init(3);
	c.init(1);
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
	a.init(5);

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
	c.init(1);
	b.init(3);
	a =	c * b;

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