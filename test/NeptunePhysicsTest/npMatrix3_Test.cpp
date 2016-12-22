#include "gtest\gtest.h"

#include "neptunePhysics/math/npPrecision.hpp"
#include "neptunePhysics/math/npMatrix3.hpp"
#include "neptunePhysics/math/npQuaternion.h"

using namespace NeptunePhysics;

TEST(npMatrix3Test, SINGLE_VARIABLE_CONSTRUCTOR) {

	npMatrix3 a;

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);

	EXPECT_FLOAT_EQ(a.m[3], 0);
	EXPECT_FLOAT_EQ(a.m[4], 1);
	EXPECT_FLOAT_EQ(a.m[5], 0);

	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);
	EXPECT_FLOAT_EQ(a.m[8], 1);

	a = npMatrix3(5);

	EXPECT_FLOAT_EQ(a.m[0], 5);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);

	EXPECT_FLOAT_EQ(a.m[3], 0);
	EXPECT_FLOAT_EQ(a.m[4], 5);
	EXPECT_FLOAT_EQ(a.m[5], 0);

	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);
	EXPECT_FLOAT_EQ(a.m[8], 5);
}

TEST(npMatrix3Test, FULL_VALUES_CONSTRUCTOR) {

	npMatrix3 a(1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 2);
	EXPECT_FLOAT_EQ(a.m[2], 3);

	EXPECT_FLOAT_EQ(a.m[3], 4);
	EXPECT_FLOAT_EQ(a.m[4], 5);
	EXPECT_FLOAT_EQ(a.m[5], 6);

	EXPECT_FLOAT_EQ(a.m[6], 7);
	EXPECT_FLOAT_EQ(a.m[7], 8);
	EXPECT_FLOAT_EQ(a.m[8], 9);
}

TEST(npMatrix3Test, SCALAR_MULTIPLICATION) {

	npMatrix3 a(3), b(4);
	a = a * 5.0f;

	b *= 5.0f;

	EXPECT_FLOAT_EQ(a.m[0], 15);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);

	EXPECT_FLOAT_EQ(a.m[3], 0);
	EXPECT_FLOAT_EQ(a.m[4], 15);
	EXPECT_FLOAT_EQ(a.m[5], 0);

	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);
	EXPECT_FLOAT_EQ(a.m[8], 15);

	EXPECT_FLOAT_EQ(b.m[0], 20);
	EXPECT_FLOAT_EQ(b.m[1], 0);
	EXPECT_FLOAT_EQ(b.m[2], 0);

	EXPECT_FLOAT_EQ(b.m[3], 0);
	EXPECT_FLOAT_EQ(b.m[4], 20);
	EXPECT_FLOAT_EQ(b.m[5], 0);

	EXPECT_FLOAT_EQ(b.m[6], 0);
	EXPECT_FLOAT_EQ(b.m[7], 0);
	EXPECT_FLOAT_EQ(b.m[8], 20);
}

TEST(npMatrix3Test, MULTIPLICATION) {

	npMatrix3 a(1), b(3, 3, 3, 3, 3, 3, 3, 3, 3), c(1, 1, 1, 1, 1, 1, 1, 1, 1);
	a = c * b;

	EXPECT_FLOAT_EQ(a.m[0], 9);
	EXPECT_FLOAT_EQ(a.m[1], 9);
	EXPECT_FLOAT_EQ(a.m[2], 9);

	EXPECT_FLOAT_EQ(a.m[3], 9);
	EXPECT_FLOAT_EQ(a.m[4], 9);
	EXPECT_FLOAT_EQ(a.m[5], 9);

	EXPECT_FLOAT_EQ(a.m[6], 9);
	EXPECT_FLOAT_EQ(a.m[7], 9);
	EXPECT_FLOAT_EQ(a.m[8], 9);

	EXPECT_FLOAT_EQ(b.m[0], 3);
	EXPECT_FLOAT_EQ(b.m[1], 3);
	EXPECT_FLOAT_EQ(b.m[2], 3);

	EXPECT_FLOAT_EQ(b.m[3], 3);
	EXPECT_FLOAT_EQ(b.m[4], 3);
	EXPECT_FLOAT_EQ(b.m[5], 3);

	EXPECT_FLOAT_EQ(b.m[6], 3);
	EXPECT_FLOAT_EQ(b.m[7], 3);
	EXPECT_FLOAT_EQ(b.m[8], 3);

	EXPECT_FLOAT_EQ(c.m[0], 1);
	EXPECT_FLOAT_EQ(c.m[1], 1);
	EXPECT_FLOAT_EQ(c.m[2], 1);

	EXPECT_FLOAT_EQ(c.m[3], 1);
	EXPECT_FLOAT_EQ(c.m[4], 1);
	EXPECT_FLOAT_EQ(c.m[5], 1);

	EXPECT_FLOAT_EQ(c.m[6], 1);
	EXPECT_FLOAT_EQ(c.m[7], 1);
	EXPECT_FLOAT_EQ(c.m[8], 1);

	c *= b;
	EXPECT_FLOAT_EQ(b.m[0], 3);
	EXPECT_FLOAT_EQ(b.m[1], 3);
	EXPECT_FLOAT_EQ(b.m[2], 3);

	EXPECT_FLOAT_EQ(b.m[3], 3);
	EXPECT_FLOAT_EQ(b.m[4], 3);
	EXPECT_FLOAT_EQ(b.m[5], 3);

	EXPECT_FLOAT_EQ(b.m[6], 3);
	EXPECT_FLOAT_EQ(b.m[7], 3);
	EXPECT_FLOAT_EQ(b.m[8], 3);

	EXPECT_FLOAT_EQ(c.m[0], 9);
	EXPECT_FLOAT_EQ(c.m[1], 9);
	EXPECT_FLOAT_EQ(c.m[2], 9);

	EXPECT_FLOAT_EQ(c.m[3], 9);
	EXPECT_FLOAT_EQ(c.m[4], 9);
	EXPECT_FLOAT_EQ(c.m[5], 9);

	EXPECT_FLOAT_EQ(c.m[6], 9);
	EXPECT_FLOAT_EQ(c.m[7], 9);
	EXPECT_FLOAT_EQ(c.m[8], 9);
}

TEST(npMatrix3Test, SUM) {

	npMatrix3 c(1.0f, 2.0f, 3.0f,
		4.0f, 5.0f, 6.0f,
		7.0f, 8.0f, 9.0f);

	npMatrix3 b(2);

	npMatrix3 a = c + b;

	EXPECT_FLOAT_EQ(a.m[0], 3);
	EXPECT_FLOAT_EQ(a.m[1], 2);
	EXPECT_FLOAT_EQ(a.m[2], 3);

	EXPECT_FLOAT_EQ(a.m[3], 4);
	EXPECT_FLOAT_EQ(a.m[4], 7);
	EXPECT_FLOAT_EQ(a.m[5], 6);

	EXPECT_FLOAT_EQ(a.m[6], 7);
	EXPECT_FLOAT_EQ(a.m[7], 8);
	EXPECT_FLOAT_EQ(a.m[8], 11);

	EXPECT_FLOAT_EQ(b.m[0], 2);
	EXPECT_FLOAT_EQ(b.m[1], 0);
	EXPECT_FLOAT_EQ(b.m[2], 0);

	EXPECT_FLOAT_EQ(b.m[3], 0);
	EXPECT_FLOAT_EQ(b.m[4], 2);
	EXPECT_FLOAT_EQ(b.m[5], 0);

	EXPECT_FLOAT_EQ(b.m[6], 0);
	EXPECT_FLOAT_EQ(b.m[7], 0);
	EXPECT_FLOAT_EQ(b.m[8], 2);

	EXPECT_FLOAT_EQ(c.m[0], 1);
	EXPECT_FLOAT_EQ(c.m[1], 2);
	EXPECT_FLOAT_EQ(c.m[2], 3);

	EXPECT_FLOAT_EQ(c.m[3], 4);
	EXPECT_FLOAT_EQ(c.m[4], 5);
	EXPECT_FLOAT_EQ(c.m[5], 6);

	EXPECT_FLOAT_EQ(c.m[6], 7);
	EXPECT_FLOAT_EQ(c.m[7], 8);
	EXPECT_FLOAT_EQ(c.m[8], 9);
	a = b + c;

	EXPECT_FLOAT_EQ(a.m[0], 3);
	EXPECT_FLOAT_EQ(a.m[1], 2);
	EXPECT_FLOAT_EQ(a.m[2], 3);

	EXPECT_FLOAT_EQ(a.m[3], 4);
	EXPECT_FLOAT_EQ(a.m[4], 7);
	EXPECT_FLOAT_EQ(a.m[5], 6);

	EXPECT_FLOAT_EQ(a.m[6], 7);
	EXPECT_FLOAT_EQ(a.m[7], 8);
	EXPECT_FLOAT_EQ(a.m[8], 11);

	EXPECT_FLOAT_EQ(b.m[0], 2);
	EXPECT_FLOAT_EQ(b.m[1], 0);
	EXPECT_FLOAT_EQ(b.m[2], 0);

	EXPECT_FLOAT_EQ(b.m[3], 0);
	EXPECT_FLOAT_EQ(b.m[4], 2);
	EXPECT_FLOAT_EQ(b.m[5], 0);

	EXPECT_FLOAT_EQ(b.m[6], 0);
	EXPECT_FLOAT_EQ(b.m[7], 0);
	EXPECT_FLOAT_EQ(b.m[8], 2);

	EXPECT_FLOAT_EQ(c.m[0], 1);
	EXPECT_FLOAT_EQ(c.m[1], 2);
	EXPECT_FLOAT_EQ(c.m[2], 3);

	EXPECT_FLOAT_EQ(c.m[3], 4);
	EXPECT_FLOAT_EQ(c.m[4], 5);
	EXPECT_FLOAT_EQ(c.m[5], 6);

	EXPECT_FLOAT_EQ(c.m[6], 7);
	EXPECT_FLOAT_EQ(c.m[7], 8);
	EXPECT_FLOAT_EQ(c.m[8], 9);

	c += b;
	
	EXPECT_FLOAT_EQ(b.m[0], 2);
	EXPECT_FLOAT_EQ(b.m[1], 0);
	EXPECT_FLOAT_EQ(b.m[2], 0);

	EXPECT_FLOAT_EQ(b.m[3], 0);
	EXPECT_FLOAT_EQ(b.m[4], 2);
	EXPECT_FLOAT_EQ(b.m[5], 0);

	EXPECT_FLOAT_EQ(b.m[6], 0);
	EXPECT_FLOAT_EQ(b.m[7], 0);
	EXPECT_FLOAT_EQ(b.m[8], 2);

	EXPECT_FLOAT_EQ(c.m[0], 3);
	EXPECT_FLOAT_EQ(c.m[1], 2);
	EXPECT_FLOAT_EQ(c.m[2], 3);

	EXPECT_FLOAT_EQ(c.m[3], 4);
	EXPECT_FLOAT_EQ(c.m[4], 7);
	EXPECT_FLOAT_EQ(c.m[5], 6);

	EXPECT_FLOAT_EQ(c.m[6], 7);
	EXPECT_FLOAT_EQ(c.m[7], 8);
	EXPECT_FLOAT_EQ(c.m[8], 11);
}

TEST(npMatrix3Test, VECTOR_MULTIPLICATION) {

	npMatrix3 a(1, 1, 1, 1, 1, 1, 1, 1, 1);

	EXPECT_FLOAT_EQ(a.m[0], 1);
	EXPECT_FLOAT_EQ(a.m[1], 1);
	EXPECT_FLOAT_EQ(a.m[2], 1);

	EXPECT_FLOAT_EQ(a.m[3], 1);
	EXPECT_FLOAT_EQ(a.m[4], 1);
	EXPECT_FLOAT_EQ(a.m[5], 1);

	EXPECT_FLOAT_EQ(a.m[6], 1);
	EXPECT_FLOAT_EQ(a.m[7], 1);
	EXPECT_FLOAT_EQ(a.m[8], 1);

	npVector3r b(3.0f, 2.0f, 5.0f);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 5);

	auto c = a * b;

	EXPECT_FLOAT_EQ(c.x, 10);
	EXPECT_FLOAT_EQ(c.y, 10);
	EXPECT_FLOAT_EQ(c.z, 10);
}

TEST(npMatrix3Test, VECTOR_TRANSFORM) {
	npMatrix3 a(2);

	EXPECT_FLOAT_EQ(a.m[0], 2);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);

	EXPECT_FLOAT_EQ(a.m[3], 0);
	EXPECT_FLOAT_EQ(a.m[4], 2);
	EXPECT_FLOAT_EQ(a.m[5], 0);

	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);
	EXPECT_FLOAT_EQ(a.m[8], 2);

	npVector3r b(3.0f, 2.0f, 5.0f);

	EXPECT_FLOAT_EQ(b.x, 3);
	EXPECT_FLOAT_EQ(b.y, 2);
	EXPECT_FLOAT_EQ(b.z, 5);

	auto c = a.transform(b);

	EXPECT_FLOAT_EQ(c.x, 6);
	EXPECT_FLOAT_EQ(c.y, 4);
	EXPECT_FLOAT_EQ(c.z, 10);
}

TEST(npMatrix3Test, GET_DETERMINANT) {
	npMatrix3 a(2);

	npReal value = a.getDeterminant();

	EXPECT_FLOAT_EQ(a.m[0], 2);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);

	EXPECT_FLOAT_EQ(a.m[3], 0);
	EXPECT_FLOAT_EQ(a.m[4], 2);
	EXPECT_FLOAT_EQ(a.m[5], 0);

	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);
	EXPECT_FLOAT_EQ(a.m[8], 2);

	EXPECT_FLOAT_EQ(value, 8);

	npMatrix3 b(4, 3, 0, 2, 5, 1, 4, 2, 2);

	value = b.getDeterminant();

	EXPECT_FLOAT_EQ(b.m[0], 4);
	EXPECT_FLOAT_EQ(b.m[1], 3);
	EXPECT_FLOAT_EQ(b.m[2], 0);

	EXPECT_FLOAT_EQ(b.m[3], 2);
	EXPECT_FLOAT_EQ(b.m[4], 5);
	EXPECT_FLOAT_EQ(b.m[5], 1);

	EXPECT_FLOAT_EQ(b.m[6], 4);
	EXPECT_FLOAT_EQ(b.m[7], 2);
	EXPECT_FLOAT_EQ(b.m[8], 2);

	EXPECT_FLOAT_EQ(value, 32);
}

TEST(npMatrix3Test, TRANSPOSE) {
	npMatrix3 a(2);
	a.transpose();

	EXPECT_FLOAT_EQ(a.m[0], 2);
	EXPECT_FLOAT_EQ(a.m[1], 0);
	EXPECT_FLOAT_EQ(a.m[2], 0);

	EXPECT_FLOAT_EQ(a.m[3], 0);
	EXPECT_FLOAT_EQ(a.m[4], 2);
	EXPECT_FLOAT_EQ(a.m[5], 0);

	EXPECT_FLOAT_EQ(a.m[6], 0);
	EXPECT_FLOAT_EQ(a.m[7], 0);
	EXPECT_FLOAT_EQ(a.m[8], 2);

	npMatrix3 b, c(4, 3, 0, 2, 5, 1, 4, 2, 2);
	b = c.transpose();

	EXPECT_FLOAT_EQ(b.m[0], 4);
	EXPECT_FLOAT_EQ(b.m[1], 2);
	EXPECT_FLOAT_EQ(b.m[2], 4);

	EXPECT_FLOAT_EQ(b.m[3], 3);
	EXPECT_FLOAT_EQ(b.m[4], 5);
	EXPECT_FLOAT_EQ(b.m[5], 2);

	EXPECT_FLOAT_EQ(b.m[6], 0);
	EXPECT_FLOAT_EQ(b.m[7], 1);
	EXPECT_FLOAT_EQ(b.m[8], 2);
}

TEST(npMatrix3Test, INVERSE) {
	npMatrix3 a(2, 3, 4, 7, 8, 9, 11, 5, 1);
	npReal value = a.getDeterminant();
	a.invert();

	EXPECT_FLOAT_EQ(value, -10);

	EXPECT_FLOAT_EQ(a.m[0], 3.7f);
	EXPECT_FLOAT_EQ(a.m[1], -1.7f);
	EXPECT_FLOAT_EQ(a.m[2], 0.5f);

	EXPECT_FLOAT_EQ(a.m[3], -9.2f);
	EXPECT_FLOAT_EQ(a.m[4], 4.2f);
	EXPECT_FLOAT_EQ(a.m[5], -1.0f);

	EXPECT_FLOAT_EQ(a.m[6], 5.3f);
	EXPECT_FLOAT_EQ(a.m[7], -2.3f);
	EXPECT_FLOAT_EQ(a.m[8], 0.5f);

	npMatrix3 b, c(1, 2, 2, 3, 4, 5, 11, 5, 1);
	npReal value2 = c.getDeterminant();
	b = c.inverse();

	EXPECT_FLOAT_EQ(value2, 25);

	EXPECT_FLOAT_EQ(b.m[0], -21 / value2);
	EXPECT_FLOAT_EQ(b.m[1], 8 / value2);
	EXPECT_FLOAT_EQ(b.m[2], 2 / value2);

	EXPECT_FLOAT_EQ(b.m[3], 52 / value2);
	EXPECT_FLOAT_EQ(b.m[4], -21 / value2);
	EXPECT_FLOAT_EQ(b.m[5], 1 / value2);

	EXPECT_FLOAT_EQ(b.m[6], -29 / value2);
	EXPECT_FLOAT_EQ(b.m[7], 17 / value2);
	EXPECT_FLOAT_EQ(b.m[8], -2 / value2);
}

TEST(npMatrix3Test, SET_ORIENTATION) {
	npMatrix3 a(2, 3, 4, 7, 8, 9, 11, 5, 1);
	npQuarternion q(4, 0.5f, 1, 0.7f);

	EXPECT_FLOAT_EQ(a.m[0], 2);
	EXPECT_FLOAT_EQ(a.m[1], 3);
	EXPECT_FLOAT_EQ(a.m[2], 4);

	EXPECT_FLOAT_EQ(a.m[3], 7);
	EXPECT_FLOAT_EQ(a.m[4], 8);
	EXPECT_FLOAT_EQ(a.m[5], 9);

	EXPECT_FLOAT_EQ(a.m[6], 11);
	EXPECT_FLOAT_EQ(a.m[7], 5);
	EXPECT_FLOAT_EQ(a.m[8], 1);

	EXPECT_FLOAT_EQ(q.r, 4);
	EXPECT_FLOAT_EQ(q.i, 0.5);
	EXPECT_FLOAT_EQ(q.j, 1);
	EXPECT_FLOAT_EQ(q.k, 0.7f);

	a.setOrientation(q);

	EXPECT_FLOAT_EQ(a.m[0], -1.98f);
	EXPECT_FLOAT_EQ(a.m[1], 6.5999999f);
	EXPECT_FLOAT_EQ(a.m[2], -7.3000002f);

	EXPECT_FLOAT_EQ(a.m[3], -4.5999999f);
	EXPECT_FLOAT_EQ(a.m[4], -0.48000002f);
	EXPECT_FLOAT_EQ(a.m[5], 5.4000001f);

	EXPECT_FLOAT_EQ(a.m[6], 8.6999998f);
	EXPECT_FLOAT_EQ(a.m[7], -2.5999999f);
	EXPECT_FLOAT_EQ(a.m[8], -1.5f);
}