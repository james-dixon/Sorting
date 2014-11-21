#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <chrono>
#include <cassert>
#include <cstdint>
#include <type_traits>


#include "quadratic.hpp"
#include "loglinear.hpp"
#include "radix.hpp"

// restrict by return type
template<typename T>
std::vector<typename std::enable_if<std::is_integral<T>::value,T>::type >
random_ints(const uint64_t number,
			const T min = std::numeric_limits<T>::lowest(),
			const T max = std::numeric_limits<T>::max())
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<T> dis(min, max);
	std::vector<T> output;
	output.reserve(number);
	for(uint64_t i=0; i<number; ++i)
	{
		output.push_back( dis(gen) );
		}
	return output;
}


using namespace std;

int main()
{
	using myint = uint32_t;
	
	const vector<myint> unsorted_vector = random_ints<myint>(1000000);
	vector<myint> temp_vector = unsorted_vector;
	
	// declare chrono objects
	auto t1 = chrono::high_resolution_clock::now();
	auto t2 = chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();


	t1 = chrono::high_resolution_clock::now();
	std::sort(begin(temp_vector), end(temp_vector));
	t2 = chrono::high_resolution_clock::now();
	assert( std::is_sorted(begin(temp_vector), end(temp_vector)) );
	const vector<myint> sorted_vector = temp_vector;
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"STL-sort took: "<<dur<<"ms"<<endl;

	
/*
	temp_vector = unsorted_vector;
	auto t1 = chrono::high_resolution_clock::now();
	sort::quad::bubble(begin(temp_vector), end(temp_vector));
	assert(std::is_sorted( begin(temp_vector), end(temp_vector)));
	auto t2 = chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Bubble-sort took:    "<<dur<<"ms"<<endl;

	
	temp_vector = unsorted_vector;
	t1 = chrono::high_resolution_clock::now();
	sort::quad::insertion(begin(temp_vector), end(temp_vector));
	assert( std::is_sorted(begin(temp_vector), end(temp_vector)) );
	t2 = chrono::high_resolution_clock::now();
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Insertion-sort took: "<<dur<<"ms"<<endl;

	
	temp_vector = unsorted_vector;
	t1 = chrono::high_resolution_clock::now();
	sort::quad::selection(begin(temp_vector), end(temp_vector));
	assert( std::is_sorted(begin(temp_vector), end(temp_vector)) );
	t2 = chrono::high_resolution_clock::now();
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Selection-sort took: "<<dur<<"ms"<<endl;
*/
	temp_vector = unsorted_vector;
	t1 = chrono::high_resolution_clock::now();
	sort::loglin::merge(begin(temp_vector), end(temp_vector));
	t2 = chrono::high_resolution_clock::now();
	assert( temp_vector == sorted_vector );
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Merge-sort took: "<<dur<<"ms"<<endl;


	temp_vector = unsorted_vector;
	t1 = chrono::high_resolution_clock::now();
	sort::loglin::quick(begin(temp_vector), end(temp_vector));
	t2 = chrono::high_resolution_clock::now();
	assert( temp_vector == sorted_vector );
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Quick-sort took: "<<dur<<"ms"<<endl;

	
	
	
	temp_vector = unsorted_vector;
	t1 = chrono::high_resolution_clock::now();
	sort::radix(temp_vector);
	t2 = chrono::high_resolution_clock::now();
	assert( temp_vector == sorted_vector );
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Radix-sort took: "<<dur<<"ms"<<endl;

}
