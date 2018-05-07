#pragma once

#include "Location.h"
#include <assert.h>
class TestLocation
{
public:
	static void test();
};

void TestLocation::test()
{
	Location a = { 0, 0 };
	Location b = { 0, 0 };

	Location c = { 1, 1 };

	Location d = { -1, 1 };

	assert(a == b);
	assert(c > a);
	assert(a < c);
	assert(c >= a);
	assert(a <= c);
	assert(d < a);
	assert(d <= a);
	assert(a < b == false);
}

