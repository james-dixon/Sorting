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

			std::vector<dtype> left(start, midpoint);
			std::vector<dtype> right(midpoint, end);

			// recursively sort the two halves in place
			merge(left.begin(), left.end());
			merge(right.begin(), right.end());

			// then merge them back into start->end

			Iterator pleft = left.begin();
			Iterator pright = right.begin();
			Iterator overall = start;

			while(overall!=end)
			{

				if( pleft!=left.end() && (*(pleft) <= *(pright) || pright==right.end()) )
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
