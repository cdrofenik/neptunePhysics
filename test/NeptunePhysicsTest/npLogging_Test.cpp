#include "gtest\gtest.h"

#include "neptunePhysics/logging/npLogging.hpp"

using namespace NeptunePhysics;

TEST(npLogging, LoggingTest) {

	//TODO fix me!

	//Log_DEBUG("LoggingTest", "char value", "test");

	//Log_DEBUG("LoggingTest", "integer value", 5);

	//Log_DEBUG("LoggingTest", "float value", 4.3f);

	npVector3r b(1, 2, 3);
	Log_DEBUG("LoggingTest", "npVector3 b", b);

	npMatrix3 a;
	Log_DEBUG("LoggingTest", "npMatrix3 a", a);

}