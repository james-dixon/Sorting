#ifndef LOGLINEAR_HPP
#define LOGLINEAR_HPP

#include <vector>
#include <iterator>
#include <iomanip>

#include "quadratic.hpp"

namespace sort
{
	namespace loglin
	{

		template<class Iterator,
				 class dtype = typename std::iterator_traits<Iterator>::value_type>
		void merge(const Iterator start, const Iterator end)
		{
			// only one element => must be sorted
				if(std::next(start)==end)
					return;
			// if we remove this, performance is worse! hmm...

			
			// for small lists, use insertion sort, is the fastest!
			if(std::distance(start,end)<40)
				return quad::insertion(start, end);
			
			
			Iterator midpoint = start + std::distance(start, end)/2;

			// recursively sort the two halves in place
			merge(start, midpoint);
			merge(midpoint, end);

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


		template<class Iterator>
		void quick(const Iterator start, const Iterator end)
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

			// recursively sort the two halves above / below
			// but check that they aren't empty...
			if(std::distance(start,below)>1)
				quick(start, below);
			if(std::distance(std::next(below),end)>1)
				quick(std::next(below), end);
		}
			
		template<class Iterator>
		typename std::enable_if< std::is_same< std::random_access_iterator_tag,
											   typename std::iterator_traits<Iterator>::iterator_category >::value,
								 void >::type
		// we restrict it to only work on random access iterators!
		heap(const Iterator start, const Iterator end)
		{
			// lambdas can't be templated (yet?), so we have to use auto
			auto parent = [start](const Iterator child){return start + (std::distance(start,child)-1)/2;};
			auto first_child = [start](const Iterator parent, const Iterator last){Iterator child = parent + std::distance(start,parent) + 1;
																				   return child<last ? child : parent ;};
			auto second_child = [start](const Iterator parent, const Iterator last){Iterator child = parent + std::distance(start,parent) + 2;
																					return child<last ? child : parent ;};

			// extracting from the heap seems to be very slow
			// :( maybe just due to lots of cache misses?
			
			//	auto t1 = std::chrono::high_resolution_clock::now();
			//	auto t2 = std::chrono::high_resolution_clock::now();
			//	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
			
			// build up the heap
			for(Iterator pos = start+1; pos!=end; ++pos)
			{
				Iterator tmp = pos;
					
				while( *(tmp) > *(parent(tmp)) )
				{
					std::swap( *(tmp), *(parent(tmp)) );
					tmp = parent(tmp);
				}
			}
			
			//	t2 = std::chrono::high_resolution_clock::now();
			//	dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
			//	std::cout<<"Building heap took: "<<dur<<"ms"<<std::endl;
			//	t1 = std::chrono::high_resolution_clock::now();
			
			// take down the heap
			for(Iterator pos = end-1; pos!=start; --pos)
			{
				std::swap( *pos, *start);
				Iterator tmp = start;

				while(  (*tmp < *(first_child(tmp,pos)))  ||  (*tmp < *(second_child(tmp,pos)))  )
				{
					if( *(second_child(tmp,pos)) > *(first_child(tmp,pos)) )
					{
						std::swap( *tmp, *(second_child(tmp,pos)) );
						tmp = second_child(tmp,pos);
					}
					else 
					{
						std::swap( *tmp, *(first_child(tmp,pos)) );
						tmp = first_child(tmp,pos);
					}
				}
				
			}
			//	t2 = std::chrono::high_resolution_clock::now();
			//  dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
			//	std::cout<<"Extracting the heap took: "<<dur<<"ms"<<std::endl;
		}

			
	
	}
}

#endif
