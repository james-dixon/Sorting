#ifndef PARALLEL_HPP
#define PARALLEL_HPP

#include <vector>
#include <iterator>
#include <thread>

#include "quadratic.hpp"
#include "loglinear.hpp"

namespace sort
{
	namespace parallel
	{

		template<class Iterator>
		void quick(const Iterator start, const Iterator end, const int depth=0)
		{
		
			if(std::distance(start,end)<=30)
				return quad::insertion(start,end);
			
			const Iterator midpoint = start + std::distance(start, end)/2;
			Iterator pivot = start;
			const Iterator last = std::prev(end);
			// select pivot
			if( ( *(start) >= *(midpoint) && *(midpoint) >= *(last) ) ||
				( *(start) <= *(midpoint) && *(midpoint) <= *(last) ) )
			{
				pivot = midpoint;
			}
			else if( ( *(last) >= *(midpoint) && *(start) >= *(last) ) ||
					 ( *(last) <= *(midpoint) && *(start) <= *(last) ) )
			{
				pivot = last;
			}

			// move the pivot to the end
			std::swap( *(pivot), *(last) );
			pivot = last;

			// fill up the array from the start with elements below the pivot
			// 'below' tracks the position of the first element NOT below the pivot
			Iterator below = start;
			for(auto pos=start; pos!=last; ++pos)
			{
				if( *(pos) < *(pivot) )
				{
					std::swap( *(pos), *(below) );
					++below;						
				}
			}
			// move pivot back into the middle of the array
			std::swap( *(below), *(last) );

			// creating threads is expensive, so only do it for a certain depth
			// otherwise call non-parallel version
			if(depth<4)
			{
				std::thread t1(sort::parallel::quick<Iterator>, start, below, depth+1);
				std::thread t2(sort::parallel::quick<Iterator>, std::next(below), end, depth+1);
				t1.join();
				t2.join();
			}
			else
			{
				sort::loglin::quick<Iterator>(start, below);
				sort::loglin::quick<Iterator>(std::next(below), end);
			}
		}
			

		template<class Iterator,
				 class dtype = typename std::iterator_traits<Iterator>::value_type>
		void merge(const Iterator start, const Iterator end, const int depth=0)
		{
			// only one element => must be sorted
			if(std::next(start)==end)
				return;
			// if we remove this, performance is worse! hmm...

			
			// for small lists, use insertion sort, is the fastest!
			// optimal value for this seems to be different for non-parallel version
			if(std::distance(start,end)<80)
				return quad::insertion(start, end);
			
			
			Iterator midpoint = start + std::distance(start, end)/2;

			// recursively sort the two halves in place
			if(depth<3)
			{
				std::thread t1(sort::parallel::merge<Iterator>, start, midpoint,depth+1);
				std::thread t2(sort::parallel::merge<Iterator>, midpoint, end, depth+1);
				t1.join();
				t2.join();
			}
			else
			{
				sort::loglin::merge(start, midpoint);
				sort::loglin::merge(midpoint, end);
			}
			// then merge them back into start -> end
	
		
			// copy the first half out
			// then merge 'sort of' in-palce
			std::vector<dtype> left_copy(start, midpoint);

			Iterator pleft = left_copy.begin();
			Iterator pright = midpoint;
			Iterator overall = start;
			
			while(overall!=end)
			{
				// safety check! not at end of 'left'
				// IF  next object in left is lower than right  OR if no right items left
				// add left item and move along left
				if( pleft!=left_copy.end() && (*(pleft) <= *(pright) || pright==end ) )
				{
					*(overall) = *(pleft);
					pleft = std::next(pleft);
				}
				else
				{
					// ELSE add right item and move along right
					*(overall) = *(pright);
					pright = std::next(pright);
				}

				overall = std::next(overall);
			}
		}


			
	
	}
}

#endif
