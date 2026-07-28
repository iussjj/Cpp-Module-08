#include "Span.hpp"
#include <algorithm>
#include <limits>

// numbers_ is default constructed
Span::Span() : maxSize_(0) {}

Span::~Span() {}

Span::Span(unsigned int N) : maxSize_(N) {
	/*
		reserved initialization: numbers_ is initialized to size 0,
		but with enough memory set aside to hold N elements
	*/
	numbers_.reserve(N);
}
Span::Span(const Span& source) : maxSize_(source.maxSize_), numbers_(source.numbers_) {}

/*
	overkill memory safety: vector is copied to a temp variable, and only if the
	copy succeeds, the target Span object's membe variables are updated
*/
Span& Span::operator=(const Span& source) {

	if (this != &source) {
		std::vector<int> tmp = source.numbers_;
		maxSize_ = source.maxSize_;
		numbers_ = tmp;
	}
	return *this;
}

void Span::addNumber(int N) {
	if (numbers_.size() >= maxSize_) {
		throw SpanFullException();
	}
	numbers_.push_back(N);
}

unsigned int Span::shortestSpan() const {
	if (numbers_.size() < 2) {
		throw NotEnoughNumbersException();
	}

	std::vector<int> sortedNumbers_ = numbers_;
	std::sort(sortedNumbers_.begin(), sortedNumbers_.end());

	unsigned int minDiff = std::numeric_limits<unsigned int>::max();
	for (size_t i = 0 ; i < (numbers_.size() - 1) ; i++) {
		long diff = static_cast<long>(sortedNumbers_[i + 1]) - sortedNumbers_[i];
		if (static_cast<unsigned int>(diff) < minDiff) {
			minDiff = static_cast<unsigned int>(diff);
		}
	}
	return minDiff;
}

unsigned int Span::longestSpan() const {
	if (numbers_.size() < 2) {
		throw NotEnoughNumbersException();
	}

	//minmax_element finds min and max values in a single pass through vector
	auto result = std::minmax_element(numbers_.begin(), numbers_.end());

	/*
		-handles edge case if trying to subtract INT_MAX - INT_MIN
		-implicit conversion ok, because no data can be lost when smaller -> larger
	*/
	long min = *result.first;
	long max = *result.second;

	return static_cast<unsigned int>(max - min);
}