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

			Iterator midpoint = start + (std::distance(start, end))/2;

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

				if( pleft!=left_copy.end() && (*(pleft) <= *(pright) || pright==end ) )
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

			
			
		}

	}
}

#endif
