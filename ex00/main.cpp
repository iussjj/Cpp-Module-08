#include "easyfind.hpp"

#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

int main () {
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	std::list<int> lst = { 42, 666, 9000 };
	const std::vector<int> cvec = { 42, 42, 42};
	std::list<int> dlist = { 42, 43, 43 };

	// looking for an existing int in a vector
	auto it1 = easyfind(vec, 5);
	std::cout << "Found item: " << *it1 << std::endl;

	// looking for an existing int in a list
	auto it2 = easyfind(lst, 9000);
	std::cout << "Found item: " << *it2 << std::endl;

	try {
		// looking for a nonexistent item (this will trigger the exception)
		auto it3 = easyfind(vec, 42);
		(void) it3;

	} catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << "\n";
	}

	// return const_iterator
	auto it4 = easyfind(cvec, 42);
	// compilation fails if easyfind did not return a const_iterator
	static_assert(std::is_same_v<decltype(it4), std::vector<int>::const_iterator>);
	std::cout << "Found item: " << *it4 << std::endl;

	// return iterator to first occurrence of duplicate value
	auto it5 = easyfind(dlist, 43);
	std::cout << "dlist contents before modification: ";
	for (const auto& number : dlist) {
		std::cout << number << " ";
	}
	*it5 = -43;
	// first occurrence should be changed to -43
	std:: cout << "\ndlist contents after modification: ";
	for (const auto& number : dlist) {
		std::cout << number << " ";
	}
	std::cout << std::endl;

	dlist.clear();
	try {
		auto it6 = easyfind(dlist, 40000);
		(void) it6;
	} catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}