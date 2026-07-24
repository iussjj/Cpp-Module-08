#include "easyfind.hpp"
#include <vector>
#include <list>
#include <iostream>

int main () {
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	std::list<int> lst = { 42, 666, 9000 };

	try {

		// looking for an existing int in a vector
		auto it1 = easyfind(vec, 5);
		std::cout << "Found item: " << *it1 << std::endl;

		// looking for an existing int in a list
		auto it2 = easyfind(lst, 9000);
		std::cout << "Found item: " << *it2 << std::endl;

		//looking for a nonexistent item (this will trigger the exception)
		auto it3 = easyfind(vec, 42);
		(void) it3;

	} catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << "\n";
	}
}