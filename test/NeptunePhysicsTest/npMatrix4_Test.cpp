#include "gtest\gtest.h"

#include "neptunePhysics/math/npPrecision.hpp"
#include "neptunePhysics/math/npMatrix4.hpp"

using namespace NeptunePhysics;

TEST(npMatrix4Test, SINGLE_VARIABLE_CONSTRUCTOR) {

	npMatrix4 a(3);

	EXPECT_FLOAT_EQ(a.m[0], 3);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);
	EXPECT_FLOAT_EQ(a.m[3], 0);

	EXPECT_FLOAT_EQ(a.m[4], 0);
	EXPECT_FLOAT_EQ(a.m[5], 3);
	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);

	EXPECT_FLOAT_EQ(a.m[8], 0);
	EXPECT_FLOAT_EQ(a.m[9], 0);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], 0);

	EXPECT_FLOAT_EQ(a.m[12], 0);
	EXPECT_FLOAT_EQ(a.m[13], 0);
	EXPECT_FLOAT_EQ(a.m[14], 0);
	EXPECT_FLOAT_EQ(a.m[15], 1);
}

TEST(npMatrix4Test, FULL_VARIABLE_CONSTRUCTOR) {

	npMatrix4 a(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);

	EXPECT_FLOAT_EQ(a.m[0], 3);
	EXPECT_FLOAT_EQ(a.m[1], 3);
	EXPECT_FLOAT_EQ(a.m[2], 3);
	EXPECT_FLOAT_EQ(a.m[3], 3);

	EXPECT_FLOAT_EQ(a.m[4], 3);
	EXPECT_FLOAT_EQ(a.m[5], 3);
	EXPECT_FLOAT_EQ(a.m[6], 3);
	EXPECT_FLOAT_EQ(a.m[7], 3);

	EXPECT_FLOAT_EQ(a.m[8], 3);
	EXPECT_FLOAT_EQ(a.m[9], 3);
	EXPECT_FLOAT_EQ(a.m[10], 3);
	EXPECT_FLOAT_EQ(a.m[11], 3);

	EXPECT_FLOAT_EQ(a.m[12], 3);
	EXPECT_FLOAT_EQ(a.m[13], 3);
	EXPECT_FLOAT_EQ(a.m[14], 3);
	EXPECT_FLOAT_EQ(a.m[15], 3);
}

TEST(npMatrix4Test, MULTIPLICATION) {

	npMatrix4 a, d, c(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1),
		b(3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);
	a = c * b;

	EXPECT_FLOAT_EQ(a.m[0], 12);
	EXPECT_FLOAT_EQ(a.m[1], 12);
	EXPECT_FLOAT_EQ(a.m[2], 12);
	EXPECT_FLOAT_EQ(a.m[3], 12);

	EXPECT_FLOAT_EQ(a.m[4], 12);
	EXPECT_FLOAT_EQ(a.m[5], 12);
	EXPECT_FLOAT_EQ(a.m[6], 12);
	EXPECT_FLOAT_EQ(a.m[7], 12);

	EXPECT_FLOAT_EQ(a.m[8], 12);
	EXPECT_FLOAT_EQ(a.m[9], 12);
	EXPECT_FLOAT_EQ(a.m[10], 12);
	EXPECT_FLOAT_EQ(a.m[11], 12);

	EXPECT_FLOAT_EQ(a.m[12], 12);
	EXPECT_FLOAT_EQ(a.m[13], 12);
	EXPECT_FLOAT_EQ(a.m[14], 12);
	EXPECT_FLOAT_EQ(a.m[15], 12);
}

TEST(npMatrix4Test, ADDITION) {

	npMatrix3 c(1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);

	npMatrix4 d(c), b, a;
	a = d + b;

	EXPECT_FLOAT_EQ(a.m[0], 2);
	EXPECT_FLOAT_EQ(a.m[1], 2);
	EXPECT_FLOAT_EQ(a.m[2], 3);
	EXPECT_FLOAT_EQ(a.m[3], 0);

	EXPECT_FLOAT_EQ(a.m[4], 4);
	EXPECT_FLOAT_EQ(a.m[5], 6);
	EXPECT_FLOAT_EQ(a.m[6], 6);
	EXPECT_FLOAT_EQ(a.m[7], 0);

	EXPECT_FLOAT_EQ(a.m[8], 7);
	EXPECT_FLOAT_EQ(a.m[9], 8);
	EXPECT_FLOAT_EQ(a.m[10], 10);
	EXPECT_FLOAT_EQ(a.m[11], 0);

	EXPECT_FLOAT_EQ(a.m[12], 0);
	EXPECT_FLOAT_EQ(a.m[13], 0);
	EXPECT_FLOAT_EQ(a.m[14], 0);
	EXPECT_FLOAT_EQ(a.m[15], 2);
}

TEST(npMatrix4Test, TRANSPOSE) {

	npMatrix3 c(1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);

	npMatrix4 b(c), a;
	a = b.transpose();

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 4);
	EXPECT_FLOAT_EQ(a.m[2], 7);
	EXPECT_FLOAT_EQ(a.m[3], 0);

	EXPECT_FLOAT_EQ(a.m[4], 2);
	EXPECT_FLOAT_EQ(a.m[5], 5);
	EXPECT_FLOAT_EQ(a.m[6], 8);
	EXPECT_FLOAT_EQ(a.m[7], 0);

	EXPECT_FLOAT_EQ(a.m[8], 3);
	EXPECT_FLOAT_EQ(a.m[9], 6);
	EXPECT_FLOAT_EQ(a.m[10], 9);
	EXPECT_FLOAT_EQ(a.m[11], 0);

	EXPECT_FLOAT_EQ(a.m[12], 0);
	EXPECT_FLOAT_EQ(a.m[13], 0);
	EXPECT_FLOAT_EQ(a.m[14], 0);
	EXPECT_FLOAT_EQ(a.m[15], 1);
}