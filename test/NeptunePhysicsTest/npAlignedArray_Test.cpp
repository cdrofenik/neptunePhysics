#include "gtest\gtest.h"

#include "neptunePhysics/core/npAlignedArray.hpp"

#include <iostream>

using namespace NeptunePhysics;

TEST(npAlignedArray, BASIC_INIT_TEST) {

	npAlignedArray<int> a;

	EXPECT_EQ(a.size(), 0);
	EXPECT_EQ(a.capacity(), 0);

	a.reserve(20);

	EXPECT_EQ(a.size(), 0);
	EXPECT_EQ(a.capacity(), 20);
}

TEST(npAlignedArray, FILL_AND_FETCH_DATA) {

	npAlignedArray<int> a;
	a.reserve(20);

	for (size_t i = 0; i < 20; i++)
	{
		a.push_back(i);
	}


	for (size_t i = 0; i < 20; i++)
	{
		EXPECT_EQ(a[i], i);
		EXPECT_EQ(a.at(i), i);
	}
}

bool compare(int a, int b)
{
	if (a < b)
		return true;
	else
		return false;
}

TEST(npAlignedArray, FILL_AND_SORT) {

	npAlignedArray<int> a;
	a.reserve(20);

	for (size_t i = 0; i < 20; i++)
	{
		int value = i % 3 ? i * (-1) : i * 2;
		a.push_back(value);
	}

	a.bubbleSort(compare);
	for (size_t i = 1; i < 19; i++)
	{
		EXPECT_GT(a[i], a[i - 1]);
	}
}

TEST(npAlignedArray, CHANGE_VALUES_WITH_POINTER) {

	struct testStruct
	{
		testStruct(int val) : value(val) {}
		int value;
	};

	npAlignedArray<testStruct> a;
	a.reserve(20);

	for (size_t i = 0; i < 20; i++)
	{
		int value = i;
		testStruct ts = testStruct(value);
		a.push_back(ts);
	}

	testStruct* ref = &a.at(19);
	ref->value = 21;

	for (size_t i = 1; i < 18; i++)
	{
		EXPECT_EQ(a[i].value, i);
	}
	EXPECT_EQ(a[19].value, 21);
}