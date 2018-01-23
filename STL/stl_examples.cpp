#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <thread>
#include <chrono>

// Compilation with C++14
// Linux: g++ -std=c++14 -pthread -Wall -Wpedantic stl_examples.cpp
// Windows: Use VS 2013 or newer

// Function for getting maximal value in a vector, defined by the relation getMax
template<typename T>
T maximalBy(const std::vector<T>& v, std::function<T(T,T)> getMax) {
	T maximal = *v.cbegin();
	std::for_each(v.cbegin() + 1, v.cend(), 
				  [&](const T& current) { maximal = getMax(maximal, current); } );
	return maximal;
}

void testMax(std::vector<int>& v) { 
	std::cout << "\nMaximal element:\n";
	std::cout << maximalBy<int>(v, 
								[](int a, int b) -> int { 
									return a > b ? a: b; 
								}) << std::endl; 
}

void print(std::vector<int>& v) {
	std::for_each(v.begin(), v.end(), [](int i) {std::cout << i << " ";});
	std::cout << std::endl;
}

// Mapping a vector with one type to another
template <typename T, typename G>
std::vector<G> map(const std::vector<T>& v, std::function<G(T)> f) {
	std::vector<G> newv(v.size());
	std::transform(v.cbegin(), v.cend(), newv.begin(), 
					[&f](const T& a) -> G { return f(a); });
	return newv;
}

void testTransform(const std::vector<char>& v) {
	std::vector<int> a = map<char, int>(v, [](char a) -> int { return a;});
	print(a);
}

// Returns vector with all elements that return true to the given function (filters the opposite)
template <typename T>
std::vector<T> filter(const std::vector<T>& v, std::function<bool(T)> take) {
	std::vector<T> filtered(v);
	filtered.erase(remove_if(filtered.begin(), filtered.end(), take), filtered.end());
	return filtered;
}

// Takes elements above 25
void testFilter(const std::vector<int>& v) {
	std::vector<int> a = filter<int>(v, [](int a) { return a > 25;});
	print(a);
}

// Sorting a part of vector using heap sort
void testPartialSort(std::vector<int>& v) {
	std::cout << "\nPartial sort: \n";
	std::partial_sort(v.begin(), v.begin() + 3, v.end());	
	print(v);
}

// Printing all permutations of a vector
void testPermutaion(std::vector<int>& v) {
	std::cout << "\nPermutations: \n";
	do {
		print(v);
	} while(std::next_permutation(v.begin(), v.end()));
}

void justWait(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	std::cout << ms << std::endl;
}

void printTo(int number) {
	for (int i = 0; i < number; ++i) 
		std::cout << i << " ";
}

// Showing how to work with smart pointers
void smartPointersTest() {
	std::shared_ptr<int> sInt = std::make_shared<int>(2);
	std::cout << "Stays the same: " << *sInt << std::endl;
	std::shared_ptr<int> sInt2 (sInt);
	std::cout << "Stays the same: " << *sInt << std::endl;


	std::unique_ptr<int> pInt = std::make_unique<int>(3);
	std::cout << "Unique: " << *pInt << std::endl;
	std::unique_ptr<int> pInt2 (std::move(pInt));
	std::cout << "Unique: " << *pInt << std::endl;
}

void primes(int to, std::vector<int>& v) {
	for (int i = 2; i < to; ++i) {
		bool isPrime = true;
		for (int j = 2; j < i; ++j) {
			if (i % j == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) 
			std::cout << i << " ";
	}
}

// Example with parallelizing work with 2 threads
void testThreads() {
	std::cout << "Thread test:\n";
	std::vector<int> a;
	std::thread first(primes, 200000, std::ref(a));
	std::thread second(printTo, 200000);
	second.join();
	std::cout << "\n\n PRINTING FINISHED! \n\n";
	first.join();

}	

// Showing how not waiting and joining threads breaks whe program ends
void testThreadsBreak() {
	std::thread first(printTo, 200000);
	std::thread second (justWait, 500);
	second.join();
}

int main() {
	std::vector<int> v {-1, 20, 30, 100, 50, -200};
	testMax(v);
	testTransform(std::vector<char> {'a', 'b', 'c', 'q'});	
	testFilter(v);
	testPartialSort(v);
	testPermutaion(v);
	smartPointersTest();
	testThreads();

//  Uncomment for segmentation fault :)
//	testThreadsBreak();
	return 0;
}
