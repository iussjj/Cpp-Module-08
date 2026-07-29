#pragma once

#include <vector>
#include <stdexcept>
#include <iterator> // required for std::input_iterator and std::distance

class Span {
private:
	unsigned int maxSize_; //max capacity (get with numbers_.capacity())
	std::vector<int> numbers_; //numbers_.size() gets *current capacity in use*

public:
	Span();
	~Span();
	Span(unsigned int N);
	Span(const Span& source);
	Span& operator=(const Span& source);

	void addNumber(int N);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

	class SpanFullException : public std::exception {
		const char* what() const noexcept override {
			return "Not enough room in span";
		}
	};

	class NotEnoughNumbersException : public std::exception {
		const char* what() const noexcept override {
			return "Not enough numbers in span: need at least 2";
		}
	};

	template <std::forward_iterator It>
	void addNumbers(It begin, It end) {
		//check if the input range fits inside numbers_
		//range is highly optimized
		if (numbers_.size() + std::distance(begin, end) > maxSize_) {
			throw SpanFullException();
		}
		// range-based insert
		numbers_.insert(numbers_.end(), begin, end);
	}
};