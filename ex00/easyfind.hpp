#pragma once

#include <stdexcept>
#include <algorithm>
#include <ranges>
#include <iterator>

class NotFoundException : public std::exception {
public:
	// noexcept: guarantee that this function will never throw an exception
	// override: makes explicit that we intend to override an existing function
	const char* what() const noexcept override {
		return "Value not found in container";
	}
};

template <typename T>
// keyword 'requires' forces compiler to only accept iterable types
requires std::ranges::range<T>
auto easyfind(T& container, int value) {
	// std::ranges::find returns pointer to value if found
	// or std::ranges::end(container) if not
	// end() is a memory space just past the last item
	auto it = std::ranges::find(container, value);

	if (it == std::ranges::end(container)) {
		throw NotFoundException();
	}

	return it;
}