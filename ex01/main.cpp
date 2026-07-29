#include "Span.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <numeric> // for std::iota

int main()
{
	{
		std::cout << "Subject test with manually filled span:" << std::endl;
		Span sp = Span(5); // in C++17 and later, this is equivalent to Span sp(5)
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	{
		std::cout << "\n\nTest with 10000 values (0-9999)" << std::endl;
		// empty span
		Span sp(10000);

		// empty source vector
		std::vector<int> v(10000);

		/*
			-fill vector with values, starting with value 0
			in position v.begin() (index 0), sequentially
			increasing the value in each position,
			and stopping at v.end() (location just past end of vector)
			-end result: vector with values 0-9999
		*/
		std::iota(v.begin(), v.end(), 0);
		
		// copy vector contents into span
		sp.addNumbers(v.begin(), v.end());
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	{
		std::cout << "\nError tests:" << std::endl;
		std::cout << "Too few numbers to compare:" << std::endl;
		Span sp(1);
		sp.addNumber(42);
		try {
			std::cout << sp.shortestSpan() << std::endl;
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
		std::cout << "Trying to add to full span:" << std::endl;
		try {
			sp.addNumber(9000);
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	{
		std::cout << "Trying to add too many numbers with addNumbers(), from list object:" << std::endl;
		Span sp(3);
		std::list<int> list;
		list.push_back(41);
		list.push_back(666);
		list.push_back(9000);
		list.push_back(40000);
		try {
			sp.addNumbers(list.begin(), list.end());
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return 0;
}