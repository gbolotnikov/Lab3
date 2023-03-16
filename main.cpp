#include <map>
#include <list>
#include "List.hpp"
#include <iostream>
#include "AllocatorMemReserve.hpp"

size_t factorial(size_t value) {
	size_t result = 1;
	for (size_t i = value; i > 0; --i) {
		result *= i;
	}
	return result;
}

template <typename TKey, typename TValue, typename Compare, typename Alloc>
void printMap(const std::map<TKey, TValue, Compare, Alloc>& map) {
    for (const auto& [key, value] : map) {
		std::cout << '[' << key << "] = " << value << "; " << '\n';
	}
}

template <typename Container>
void printContainer(const Container& container) {
	for (auto& node : container) {
		std::cout << node << '\n';
	}
}

int main(int, char *[]) {

	auto defMap = std::map<int,int,std::less<int>>{};
	auto reservMap = std::map<int,int,std::less<int>,AllocatorMemReserve<std::pair<const int, int>, 10>>{};
	auto customList = List<int>{};	
	auto reservList = List<int, AllocatorMemReserve<int, 10>>{};	

	for (int i = 0; i < 10; ++i) {
		auto value = factorial(i);		
		defMap[i] = value;
		reservMap[i] = value;
		customList.push_back(i);
		reservList.push_back(i);
	}
	std::cout << "==Map with a default allocator==" << '\n';
	printMap(defMap);
	std::cout << "==Map with a reservation allocator==" << '\n';
	printMap(reservMap);
	std::cout << "==Custom List with a default allocator==" << '\n';
	printContainer(customList);
	std::cout << "==Custom List with a reservation allocator==" << '\n';
	printContainer(reservList);

	return 0;
}