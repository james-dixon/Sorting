#ifndef LOGLINEAR_HPP
#define LOGLINEAR_HPP

#include <vector>
#include <iterator>


namespace sort
{
	namespace loglin
	{

		template<class Iterator,
				 class dtype = typename std::iterator_traits<Iterator>::value_type>
		void merge(const Iterator start, const Iterator end)
		{
			//using dtype = typename std::iterator_traits<Iterator>::value_type;

			// only one element => must be sorted
			if(std::next(start)==end)
				return;

			Iterator midpoint = start + std::distance(start, end)/2;

			//	std::vector<dtype> left(start, midpoint);
			//	std::vector<dtype> right(midpoint, end);

			// recursively sort the two halves in place
			merge(start, midpoint);
			merge(midpoint, end);

			// then merge them back into start->end

			Iterator pleft = start;
			Iterator pright = midpoint;
		
			std::vector<dtype> result;
			result.resize( std::distance(start,end) );
			Iterator overall = result.begin();
			
			while(overall!=result.end())
			{

				if( pleft!=midpoint && (*(pleft) <= *(pright) || pright==end ) )
				{
					*overall = *pleft;
					pleft = std::next(pleft);
				}
				else
				{
					*overall = *pright;
					pright = std::next(pright);
				}

				overall = std::next(overall);
			}

			std::copy(result.begin(), result.end(), start);
			
			
		}

	}
}

#endif
