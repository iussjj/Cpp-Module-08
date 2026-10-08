#pragma once

#include <cstddef> // std::size_t
#include <exception> // std::exception
#include <iterator> // std::forward_iterator, std::distance
#include <vector>

class Span {
private:
	unsigned int maxSize_; //maximum number of elements allowed
	std::vector<int> numbers_; //size() returns number of stored elements

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
	public:
		const char* what() const noexcept override;
	};

	class NotEnoughNumbersException : public std::exception {
	public:
		const char* what() const noexcept override;
	};

	template <std::forward_iterator It>
	void addNumbers(It begin, It end) {
		auto count = std::distance(begin, end);
		//check if the input range fits inside numbers_
		if (static_cast<std::size_t>(count) > maxSize_ - numbers_.size()) {
			throw SpanFullException();
		}
		// range-based insert
		numbers_.insert(numbers_.end(), begin, end);
	}
};