#ifndef LOGLINEAR_HPP
#define LOGLINEAR_HPP

#include <vector>
#include <iterator>

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
		heap(const Iterator start, const Iterator end)
		{
			return;
		}

			
	
	}
}

#endif
