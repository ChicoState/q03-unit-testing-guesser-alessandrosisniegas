/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

/* Example test
TEST(GuesserTest, smoke_test)
{
    ASSERT_EQ( 1+1, 2 );
}
*/

TEST(GuesserTest, not_match) {
	Guesser test = Guesser("irve2vio");
	ASSERT_FALSE(test.match("erwi32oin"));
}

TEST(GuesserTest, empty) {
	Guesser test = Guesser("");
	ASSERT_TRUE(test.match(""));
}

TEST(GuesserTest, mixed_chars_case) {
	Guesser test = Guesser("ewWWieWE@$*@):>',;'`~=-");
	ASSERT_TRUE(test.match("ewWWieWE@$*@):>',;'`~=-"));
}

TEST(GuesserTest, maximum_distance_is_zero_but_incorrect_guess) {
	Guesser test = Guesser("");
	ASSERT_FALSE(test.match(" "));
}

TEST(GuesserTest, maximum_32_length) {
	Guesser test = Guesser("3io3gn34foiuh39bfbiuIUWBFIUB#FOiefon2F@#P$ON#VNui34fnuwiebnfwfeibu");
	ASSERT_FALSE(test.match("3io3gn34foiuh39bfbiuIUWBFIUB#FO"));
}

TEST(GuesserTest, check_distance_zero) {
	Guesser test = Guesser("wifwio4n");
	ASSERT_EQ(0, test.distance("wifwio4n"));
}

TEST(GuesserTest, check_distance_one) {
	Guesser test = Guesser("f3F@Ion");
	ASSERT_EQ(1, test.distance("f3F@Ionr"));
}

TEST(GuesserTest, check_distance_two) {
	Guesser test = Guesser("WeoicWQ");
	ASSERT_EQ(2, test.distance("WeoicWQ  "));
}

TEST(GuesserTest, max_distance) {
	Guesser test = Guesser("ewdiQDON");
	ASSERT_EQ(8, test.distance("ewdiQDONewdiQDONewdiQDONewdiQDONewdiQDONewdiQDON"));
}

TEST(GuesserTest, max_distance_reverse) {
	Guesser test = Guesser("CWEinWCEQ");
	ASSERT_EQ(6, test.distance("CWE"));
}

TEST(GuesserTest, distance_long) {
	Guesser test("WCEIONifn1iof");
  ASSERT_EQ(7, test.distance("WCEION"));
}

TEST(GuesserTest, same_length_different_chars) {
    Guesser test("WECionweCOIN");
    ASSERT_EQ(1, test.distance("WECionweC*IN"));
}

TEST(GuesserTest, initial_remaining) {
	Guesser test = Guesser("wifwjbs");
	ASSERT_EQ(3, test.remaining());
}

TEST(GuesserTest, two_remaining) {
	Guesser test = Guesser("IOWECbwc");
	test.match("IOWECbwci");
	ASSERT_EQ(2, test.remaining());
}

TEST(GuesserTest, one_remaining) {
	Guesser test = Guesser("wef;iowfe");
	test.match("wef;iowfee");
	test.match("wef;iowfek");
	ASSERT_EQ(1, test.remaining());
}

TEST(GuesserTest, zero_remaining) {
	Guesser test = Guesser("ICEWQBwekbjc");
	test.match("ICEWQBwekbjce");
	test.match("ICEWQBwekbjcr");
	test.match("ICEWQBwekbjcg");
	ASSERT_EQ(0, test.remaining());
}

TEST(GuesserTest, locked_out) {
	Guesser test = Guesser("WEKCBewck");
	test.match("WekcBewck");
	ASSERT_EQ(0, test.remaining());
}

TEST(GuesserTest, correct_guess_reset_remaining) {
	Guesser test = Guesser("WFOIEoiffwe");
	test.match("WFOIEoiffwei");
	test.match("WFOIEoiffwe");
	ASSERT_EQ(3, test.remaining());
}

TEST(GuesserTest, correct_guess_after_locked) {
	Guesser test = Guesser("EWQIDNwEQ");
	test.match("EWQIDNwEQEWQIDNwEQEWQIDNwEQ");
	ASSERT_FALSE(test.match("EWQIDNwEQ"));
}