#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <chrono>
#include <cassert>


#include "quadratic.hpp"
#include "loglinear.hpp"

std::vector<int> random_ints(const int number,
							 const int min = std::numeric_limits<int>::lowest(),
							 const int max = std::numeric_limits<int>::max())
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);

	std::vector<int> output;
	output.reserve(number);
	for(int i=0; i<number; ++i)
		output.push_back( dis(gen) );
	return output;
}


using namespace std;

int main()
{
	const vector<int> unsorted_vector = random_ints(10000000);
	vector<int> temp_vector = unsorted_vector;
	auto t1 = chrono::high_resolution_clock::now();
	auto t2 = chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
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
	assert( std::is_sorted(begin(temp_vector), end(temp_vector)) );
	t2 = chrono::high_resolution_clock::now();
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"Merge-sort took: "<<dur<<"ms"<<endl;

	temp_vector = unsorted_vector;
	t1 = chrono::high_resolution_clock::now();
	std::sort(begin(temp_vector), end(temp_vector));
	assert( std::is_sorted(begin(temp_vector), end(temp_vector)) );
	t2 = chrono::high_resolution_clock::now();
	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	cout<<"STL-sort took: "<<dur<<"ms"<<endl;
	
}
