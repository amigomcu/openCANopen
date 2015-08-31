#include <string.h>
#include "string-utils.h"
#include "tst.h"

static char* string(const char* str)
{
	static char buffer[256];
	strncpy(buffer, str, sizeof(buffer));
	return buffer;
}

static int test_trim_left()
{
	ASSERT_STR_EQ("foo bar", string_trim_left(string("foo bar")));
	ASSERT_STR_EQ("foo bar", string_trim_left(string("\t foo bar")));
	ASSERT_STR_EQ("foo bar ", string_trim_left(string("\t foo bar ")));
	return 0;
}

static int test_trim_right()
{
	ASSERT_STR_EQ("foo bar", string_trim_right(string("foo bar")));
	ASSERT_STR_EQ("foo bar", string_trim_right(string("foo bar \t")));
	ASSERT_STR_EQ(" foo bar", string_trim_right(string(" foo bar \t")));
	return 0;
}

static int test_trim()
{
	ASSERT_STR_EQ("foo bar", string_trim(string("foo bar")));
	ASSERT_STR_EQ("foo bar", string_trim(string("foo bar \t")));
	ASSERT_STR_EQ("foo bar", string_trim(string(" \tfoo bar \t")));
	return 0;
}

static int test_is_empty()
{
	ASSERT_TRUE(string_is_empty(""));
	ASSERT_FALSE(string_is_empty("asdf"));
	return 0;
}

int main()
{
	int r = 0;
	RUN_TEST(test_trim_left);
	RUN_TEST(test_trim_right);
	RUN_TEST(test_trim);
	RUN_TEST(test_is_empty);
	return r;
}