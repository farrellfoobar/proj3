// expmain.cpp
//
// ICS 46 Winter 2018
// Project #3: Black and White
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with the given classes in the darkmaze library, or with your own
// algorithm implementations, outside of the context of the GUI or
// Google Test.

#include <utility>
#include <iostream>

int main()
{
	std::pair<int, int> p1 = {1, 3};
	std::pair<int, int> p2 = {2, 4};

	std::pair<int, int> p3 = p1+p2;

	std::cout << p3.first << ", " << p3.second;

    return 0;
}

