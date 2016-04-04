#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "A.hpp"

TEST_CASE( "testing permutations 1 element")
{
    std::vector<char> input;
	input.push_back('A');

	std::vector< std::vector<char> > out = permutation(input);
	std::vector< std::vector<char> > test;
  
	std::vector<char> a;
	a.push_back('A');
	test.push_back(a);
    REQUIRE( out == test);

}
TEST_CASE( "testing permutations 2 elements no  repetition")
{
    std::vector<char> input;
	input.push_back('A');
	input.push_back('B');

	std::vector< std::vector<char> > out = permutation(input);
	std::vector< std::vector<char> > test;

	std::vector<char> a;
	a.push_back('A');
	a.push_back('B');

	std::vector<char> b;
	b.push_back('B');
	b.push_back('A');

	test.push_back(a);
	test.push_back(b);
    REQUIRE( out == test);
}

TEST_CASE( "testing permutations 3 elements repetition")
{
    std::vector<char> input;
	input.push_back('A');
	input.push_back('B');
	input.push_back('C');

	std::vector< std::vector<char> > out = permutation(input);
	std::vector< std::vector<char> > test;
	std::vector<char> a;
	a.push_back('A');
	a.push_back('B');
	a.push_back('C');
	std::vector<char> b;
	b.push_back('A');
	b.push_back('C');
	b.push_back('B');
	std::vector<char> c;
	c.push_back('B');
	c.push_back('A');
	c.push_back('C');
	std::vector<char> d;
	d.push_back('B');
	d.push_back('C');
	d.push_back('A');
	std::vector<char> e;
	e.push_back('C');
	e.push_back('A');
	e.push_back('B');
	std::vector<char> f;
	f.push_back('C');
	f.push_back('B');
	f.push_back('A');
	test.push_back(a);
	test.push_back(b);
	test.push_back(c);
	test.push_back(d);
	test.push_back(e);
	test.push_back(f);

    REQUIRE( out == test);
}

TEST_CASE( "testing combination 1 element")
{
    std::vector<char> input;
	input.push_back('A');

	std::vector< std::vector<char> > out = combination(input, 1, false);
	std::vector< std::vector<char> > test;
  
	std::vector<char> a;
	a.push_back('A');
	test.push_back(a);
    REQUIRE( out == test);

}

TEST_CASE( "testing combination 1 of 3 element")
{
    std::vector<char> input;
	input.push_back('A');
	input.push_back('B');
	input.push_back('C');

	std::vector< std::vector<char> > out = combination(input, 1, false);
	std::vector< std::vector<char> > test;
  
	std::vector<char> a;
	a.push_back('A');
	std::vector<char> b;
	b.push_back('B');
	std::vector<char> c;
	c.push_back('C');
	test.push_back(a);
	test.push_back(b);
	test.push_back(c);
    REQUIRE( out == test);

}
TEST_CASE( "testing combination 2 of 3 elements no  repetition")
{
    std::vector<char> input;
	input.push_back('A');
	input.push_back('B');
	input.push_back('C');

	std::vector< std::vector<char> > out = combination(input, 2, false);
	std::vector< std::vector<char> > test;

	std::vector<char> a;
	a.push_back('A');
	a.push_back('B');

	std::vector<char> b;
	b.push_back('A');
	b.push_back('C');

	std::vector<char> c;
	c.push_back('B');
	c.push_back('C');

	test.push_back(a);
	test.push_back(b);
	test.push_back(c);
    REQUIRE( out == test);
}



TEST_CASE( "testing variation 2 of 3 elements no  repetition")
{
    std::vector<char> input;
	input.push_back('A');
	input.push_back('B');
	input.push_back('C');

	std::vector< std::vector<char> > out =  variation(input, 2, false);
	std::vector< std::vector<char> > test;

	std::vector<char> a;
	a.push_back('A');
	a.push_back('B');

	std::vector<char> b;
	b.push_back('B');
	b.push_back('A');

	std::vector<char> c;
	c.push_back('A');
	c.push_back('C');

	std::vector<char> d;
	d.push_back('C');
	d.push_back('A');
	std::vector<char> e;
	e.push_back('B');
	e.push_back('C');

	std::vector<char> f;
	f.push_back('C');
	f.push_back('B');

	test.push_back(a);
	test.push_back(b);
	test.push_back(c);
	test.push_back(d);
	test.push_back(e);
	test.push_back(f);
    REQUIRE( out == test);
}

TEST_CASE( "testing variation 1 element")
{
    std::vector<char> input;
	input.push_back('A');

	std::vector< std::vector<char> > out = variation(input, 1, false);
	std::vector< std::vector<char> > test;
  
	std::vector<char> a;
	a.push_back('A');
	test.push_back(a);
    REQUIRE( out == test);

}