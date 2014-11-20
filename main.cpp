#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <chrono>
#include <cassert>
#include <cstdint>

#include "quadratic.hpp"
#include "loglinear.hpp"
#include "radix.hpp"

std::vector<uint32_t> random_ints(const uint32_t number,
								  const uint32_t min = std::numeric_limits<uint32_t>::lowest(),
								  const uint32_t max = std::numeric_limits<uint32_t>::max())
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint32_t> dis(min, max);
	std::vector<uint32_t> output;
	output.reserve(number);
	for(uint32_t i=0; i<number; ++i)
	{
		output.push_back( dis(gen) );
		}
	return output;
}


using namespace std;

int main()
{
	const vector<uint32_t> unsorted_vector = random_ints(10000000);
	vector<uint32_t> temp_vector = unsorted_vector;
	
	// declare chrono objects
	auto t1 = chrono::high_resolution_clock::now();
	auto t2 = chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();


	t1 = chrono::high_resolution_clock::now();
	std::sort(begin(temp_vector), end(temp_vector));
	t2 = chrono::high_resolution_clock::now();
	assert( std::is_sorted(begin(temp_vector), end(temp_vector)) );
	const vector<uint32_t> sorted_vector = temp_vector;
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
*/
	
	
	
	temp_vector = unsorted_vector;
	t1 = chrono::high_resolution_clock::now();
	sort::radix(temp_vector);
	t2 = chrono::high_resolution_clock::now();
	assert( temp_vector == sorted_vector );
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Radix-sort took: "<<dur<<"ms"<<endl;

}
