#pragma once

#include <stdexcept>
#include <algorithm>
#include <ranges>

template <typename T>
// keyword 'requires' forces compiler to only accept iterable types
requires std::ranges::range<T>
auto easyfind(T& container, int value) {
	// std::ranges::find returns iterator to first matching element
	// or std::ranges::end(container) if no match found
	// end() is a past-the-end position; do not dereference!
	auto it = std::ranges::find(container, value);

	if (it == std::ranges::end(container)) {
		throw std::runtime_error("Value not found in container");
	}

	return it;
}