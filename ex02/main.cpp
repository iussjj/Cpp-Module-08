#include <iostream>
#include <list>
#include <stack>
#include "MutantStack.hpp"

int main() {
		{
			std::cout << "Given subject tests: " << std::endl;
			MutantStack<int> mstack;
			mstack.push(5);
			mstack.push(17);
			std::cout << mstack.top() << std::endl; // 17
			mstack.pop(); // mstack value: 5
			std::cout << mstack.size() << std::endl; // 1
			mstack.push(3);
			mstack.push(5);
			mstack.push(737);
			//[...]
			mstack.push(0); // mstack values: 5, 3, 5, 737, 0
			MutantStack<int>::iterator it = mstack.begin();
			MutantStack<int>::iterator ite = mstack.end();
			++it;
			--it;
			while (it != ite) {
				std::cout << *it << std::endl;
				++it;
			}
			std::cout << "\nTesting generic stack copy-constructed from mutant stack (outputs should match):" << std::endl;
			
			// copy construct generic stack with mutant stack source
			std::stack<int> s(mstack);
			std::cout << "Stack output (top to bottom):" << std::endl;
			// output top of stack and pop it
			while (!s.empty()) {
				std::cout << s.top() << std::endl;
				s.pop();
			}
			// stack now empty - successfully outputting mstack proves deep copy
			std::cout << "\nMutant stack output (top to bottom):" << std::endl;
			// define reverse iterators to traverse mstack from top to bottom
			MutantStack<int>::reverse_iterator rit = mstack.rbegin();
			MutantStack<int>::reverse_iterator rite = mstack.rend();
			while (rit != rite) {
				std::cout << *rit << std::endl;
				++rit;
			}
		}
		{
			std::cout << "\nSubject recommended test to verify matching functionality with list:" << std::endl;
			// output should match subject test code output
			std::list<int> list;
			list.push_back(5);
			list.push_back(17);
			std::cout << list.back() << std::endl; // 17
			list.pop_back(); // list value: 5
			std::cout << list.size() << std::endl; // 1
			list.push_back(3);
			list.push_back(5);
			list.push_back(737);
			//[...]
			list.push_back(0); // list values: 5, 3, 5, 737, 0
			std::list<int>::iterator it = list.begin();
			std::list<int>::iterator ite = list.end();
			++it;
			--it;
			while (it != ite) {
				std::cout << *it << std::endl;
				++it;
			}
		}
	return 0;
}