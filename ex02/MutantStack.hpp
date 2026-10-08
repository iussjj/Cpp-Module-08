#pragma once

#include <stack>

/*
	-std::stack doesn't manage its own memory. It has an internal *protected* container
	variable named c, which is an std::deque by default.
	-c has the iterators begin() and end(), which MutantStack can see when inheriting
	from std::stack, since c is protected not private

	MutantStack interface should be identical to std::list, so it must have:
	1. type: iterator
	2. function: begin() which returns an iterator
	3. function: end() which returns an iterator
*/

template <typename T>
class MutantStack : public std::stack<T> {
public:
	// OCF: constructors and operator= call stack class's constructor and copy logic
	MutantStack() : std::stack<T>() {}
	// MutantStack doesn't manage raw resources: memory cleanup happens in stack->deque
	~MutantStack() {}
	MutantStack(const MutantStack& source) : std::stack<T>(source) {}
	MutantStack& operator=(const MutantStack& source) {
		if (this != &source) {
			std::stack<T>::operator=(source);
		}
		return *this;
	}

	//typedef = alias: iterator becomes shorthand for std::stack<T>::container_type::iterator
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }

	const_iterator begin() const { return this->c.begin(); }
	const_iterator end()   const { return this->c.end(); }

	reverse_iterator rbegin() { return this->c.rbegin(); }
	reverse_iterator rend()   { return this->c.rend(); }

	const_reverse_iterator rbegin() const { return this->c.rbegin(); }
	const_reverse_iterator rend()   const { return this->c.rend(); }
};

/*
	ITERATOR NOTES:
	-An iterator is an object that provides a standardized way to access
	 and traverse elements in a range
	-can increment or decrement: ++it --it
	-can access stored value *it
	-recognizes end of collection: it == end

	Four kinds of iterator:
	iterator: default direction bottom->top read/write
	const_iterator: bottom->top read only
	reverse_iterator: default direction top->bottom read/write
	const_reverse_iterator: top->bottom read only

	NOTE: iterators and reverse iterators can both be incremented and decremented,
	but the direction is reversed: ++it increments one position -> top, while ++rit
	increments one position -> bottom
	-begin() and end() are also reversed:
	begin() = first item (bottom), end() = one position after last item (top)
	rbegin() = last item (top), rend() = one position before first item (bottom)

	Compiler automatically uses right iterator for const-ness
*/